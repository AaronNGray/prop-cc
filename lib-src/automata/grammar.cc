//////////////////////////////////////////////////////////////////////////////
// NOTICE:
//
// ADLib, Prop and their related set of tools and documentation are in the
// public domain.   The author(s) of this software reserve no copyrights on
// the source code and any code generated using the tools.  You are encouraged
// to use ADLib and Prop to develop software, in both academic and commercial
// settings, and are free to incorporate any part of ADLib and Prop into
// your programs.
//
// Although you are under no obligation to do so, we strongly recommend that
// you give away all software developed using our tools.
//
// We also ask that credit be given to us when ADLib and/or Prop are used in
// your programs, and that this notice be preserved intact in all the source
// code.
//
// This software is still under development and we welcome any suggestions
// and help from the users.
//
// Allen Leung
// 1994
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <strstream>
#include <iomanip>
#include <ctype.h>
#include <string.h>
#include <AD/automata/grammar.h>
#include <AD/strings/charesc.h>


//////////////////////////////////////////////////////////////////////////////
//  Make hidden types visible
//////////////////////////////////////////////////////////////////////////////

typedef Grammar::Symbol      Symbol;
typedef Grammar::Terminal    Terminal;
typedef Grammar::NonTerminal NonTerminal;
typedef Grammar::Production  Production;
typedef Grammar::EquivMap    EquivMap;

//////////////////////////////////////////////////////////////////////////////
//  Constructors
//////////////////////////////////////////////////////////////////////////////

Grammar::Grammar()
    : persistent(true), equiv_classes(0), action_map(0), action_map_size(0)
{}

Grammar::Grammar( const Grammar& G )
    : persistent(true), equiv_classes(0),
    action_map(0), action_map_size(0)
{
  *this = G;
}

Grammar::Grammar( Production P[], int n, Symbol min, Symbol max,
                  NonTerminal start,
                  const char * names[],
                  int map_size, EquivMap m[], EquivMap mm[],
                  Rule action[], int action_size,
                  NonTerminal maxNormal,
                  Bool persist)
    : productions(P),
    persistent(persist),
    number_of_productions(n),
    minTerminal(min), maxTerminal(max),
    startSymbol(start), symbol_names(names),
    equiv_classes(m), equiv_map(mm), action_map(action),
    action_map_size(action_size)
{
  minNonTerminal     = 32767;
  maxNonTerminal     = -32768;
  startProduction    = 0;
  equiv_classes_size = map_size;

  for (int i = 0; i < n; i++)
  {
    Symbol A = P[i][0];
    if ( A < minNonTerminal )
      minNonTerminal = A;
    if ( A > maxNonTerminal )
      maxNonTerminal = A;
    if ( A == startSymbol )
      startProduction  = P[i];
  }

  if (minNonTerminal > maxNonTerminal)
    minNonTerminal = maxNonTerminal = maxTerminal + 1;
  maxNormalNonTerminal = maxNormal >= 0 ? maxNormal : maxNonTerminal;
}

//////////////////////////////////////////////////////////////////////////////
//  Destructor
//////////////////////////////////////////////////////////////////////////////

Grammar::~Grammar()
{
  clean_up();
}

//////////////////////////////////////////////////////////////////////////
// Assignment
//////////////////////////////////////////////////////////////////////////

Grammar& Grammar::operator = (const Grammar& G)
{
  clean_up();
  persistent            = false;
  productions           = new Production [ G.size() ];
  startSymbol           = G.startSymbol;
  startProduction       = 0;
  for (int i = 0; i < G.size(); i++)
  {
    Production P = G[i];
    int len = G.size(P) + 1;
    Production Q = productions[i] = new Symbol [ len ];
    for (int j = 0; j < len; j++)
      Q[j] = P[j];
    if (Q[0] == startSymbol)
      startProduction = Q;
  }
  if (G.equiv_classes)
  {
    equiv_classes = new EquivMap [ equiv_classes_size = G.map_size() ];
    for (int k = 0; k < G.map_size(); k++)
      equiv_classes[k] = G.equiv_classes[k];
    equiv_map = equiv_classes + (G.equiv_map - G.equiv_classes);
  }
  else
    equiv_classes = 0;
  number_of_productions = G.number_of_productions;
  minTerminal           = G.minTerminal;
  maxTerminal           = G.maxTerminal;
  minNonTerminal        = G.minNonTerminal;
  maxNonTerminal        = G.maxNonTerminal;
  maxNormalNonTerminal  = G.maxNormalNonTerminal;
  {
    symbol_names = new const char * [ G.max_non_terminal() + 1 ];
    for (int c = G.max_non_terminal(); c >= 0; c--)
      symbol_names[c] = G.symbol_names[c];
  }
  if (G.action_map)
  {
    action_map = new Rule [ G.action_map_size ];
    memcpy (action_map, G.action_map, G.action_map_size * sizeof(Rule));
    action_map_size = G.action_map_size;
  }
  else
  {
    action_map = 0;
    action_map_size = 0;
  }
  return *this;
}

//////////////////////////////////////////////////////////////////////////
//  Cleaning up
//////////////////////////////////////////////////////////////////////////

void Grammar::clean_up()
{
  if (! persistent)
  {
    for (int i = 0; i < number_of_productions; i++)
      delete [] productions[i];
    delete [] productions;
    delete [] equiv_classes;
    delete [] symbol_names;
    delete [] action_map;
  }
}

//////////////////////////////////////////////////////////////////////////
//  Returning the size of a production: i.e. length
//////////////////////////////////////////////////////////////////////////

int Grammar::size(Production P) const
{
  int n;
  for (n = 0; *P != Grammar::END_PRODUCTION; P++, n++)
    ;
  return n;
}

//////////////////////////////////////////////////////////////////////////
//  Returning the length of a production: i.e. length sans action symbols
//////////////////////////////////////////////////////////////////////////

int Grammar::length(Production P) const
{
  int n;
  for (n = 0; *P != Grammar::END_PRODUCTION; P++)
    if (! isAction(*P))
      n++;
  return n;
}

//////////////////////////////////////////////////////////////////////////////
//  Make a grammar canonical, i.e. all action symbols has to be
//  on the rightmost end.  Embedded action symbols are hoisted by
//  introducing new null productions.
//////////////////////////////////////////////////////////////////////////////

Grammar Grammar::makeCanonical() const
{
  int extra_productions = 0;

  ///////////////////////////////////////////////////////////////////////////
  //  Count the number of extra productions needed
  ///////////////////////////////////////////////////////////////////////////
  Symbol min_action = First_action;
  {
    for (int i = 0; i < size(); i++)
    {
      Symbol X;
      for (Production P = rhs(i); (X = *P) != END_PRODUCTION; P++)
        if (isAction(X))
        {
          if (P[1] != END_PRODUCTION)
            extra_productions++;
          if (X < min_action)
            min_action = X;
        }
    }
  }
  int    act_map_size = First_action - min_action + 1;
  Rule * act_map      = new Rule [act_map_size];
  {
    for (int i = 0; i < act_map_size; i++)
      act_map[i] = -1;
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Compute the new production array by introducing new
  //  null productions whenever we find an embedded action symbol
  ///////////////////////////////////////////////////////////////////////////
  Production * pr = new Production [ extra_productions + size() + 1];
  int k = size();
  NonTerminal A = max_non_terminal();
  NonTerminal maxNormalNT = max_non_terminal();
  for (int i = 0; i < size(); i++)
  {
    Production P = (*this)[i];
    int leng = size(P) + 1;
    Production Q = pr[i] = new Symbol [ leng ];
    Symbol X;
    Q[0] = P[0];
    for ( ; (X = *P) != Grammar::END_PRODUCTION; P++)
    {
      if (isAction(X))
      {
        if (P[1] != Grammar::END_PRODUCTION)
        {
          pr[k] = new Symbol [ 3 ];
          pr[k][0] = ++A;
          pr[k][1] = X;
          pr[k][2] = Grammar::END_PRODUCTION;
          act_map[First_action - X] = k;
          k++;
          *Q++ = A;
        }
        else
        {
          act_map[First_action - X] = i;
        }
      }
      else
      {
        *Q++ = X;
      }
    }
    *Q = Grammar::END_PRODUCTION;
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Create a new start production
  ///////////////////////////////////////////////////////////////////////////
  NonTerminal new_start;
  {
    pr[k]    = new Symbol [ 4 ];
    pr[k][0] = new_start = ++A;
    pr[k][1] = startSymbol;
    pr[k][2] = EOF;
    pr[k][3] = END_PRODUCTION;
    k++;
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Compute the equiv class map
  ///////////////////////////////////////////////////////////////////////////
  int map_size     = A - EOF + 1;
  EquivMap * equiv = new EquivMap [ map_size ];
  EquivMap * map   = equiv - EOF;
  int num = 1;
  int max_term;
  {
    int i;
    for (i = 0; i < map_size; i++)
      equiv[i] = 0;
    //
    // Map terminals first.
    //
    for (i = 0; i < k; i++)
    {
      Symbol X;
      for (Production P = pr[i] + 1; (X = *P) != END_PRODUCTION; P++)
        if (isTerminal(X) && map[X] == 0)
          map[X] = num++;
    }
    map [ EOF ] = max_term = num++;
    //
    // Now map simple non-terminals
    //
    for (i = 0; i < size(); i++)
      if (map[ pr[i][0] ] == 0)
        map[ pr[i][0] ] = num++;
    //
    // Now map non-terminals generated by our transformation
    //
    for (i = size(); i < k; i++)
      if (map[ pr[i][0] ] == 0)
        map[ pr[i][0] ] = num++;
    //
    //
    // Now remap all productions
    //
    for (i = 0; i < k; i++)
    {
      Symbol X;
      for (Production P = pr[i]; (X = *P) != END_PRODUCTION; P++)
        if (isTerminal(X) || isNonTerminal(X))
          *P = map[ X ];
    }
  }

  ///////////////////////////////////////////////////////////////////////////
  // Create a new symbols mapping
  ///////////////////////////////////////////////////////////////////////////
  const char ** sym_names = new const char * [ num ];
  memset(sym_names, 0, sizeof(const char *) * num);
  for (int c = min_terminal(); c <= max_non_terminal(); c++)
    sym_names[ map [ c ] ] = symbol_names[ c ];
  sym_names[ max_term ] = "$";

  return Grammar( pr, k, 0, max_term, map[ new_start ],
                  sym_names, map_size, equiv, map, act_map, act_map_size,
                  map[ maxNormalNT ], false );
}

//////////////////////////////////////////////////////////////////////////////
//  Printing methods
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// Print a symbol using the translation table given
//////////////////////////////////////////////////////////////////////////////

std::ostream& Grammar::print( std::ostream& out, Symbol c) const
{
  if (c > Grammar::END_PRODUCTION)
  {
    if (c == EOF)
      return out << "$";  // eof symbol
    if (c == max_non_terminal())
      return out << "<start>";
    if (symbol_names && symbol_names[c])
      return out << symbol_names[c];
    if (isNonTerminal(c))
    {
      char buf[16];
      std::ostrstream F(buf,sizeof(buf));
      F << '<' << (int)c << '>' << std::ends;
      return out << F.str();
    }
    if (c >= 0 && c <= 255)
    {
      char buf [16];
      print_char(buf+1,c);
      return out << '\'' << buf << '\'';
    }
  }
  return out;
}

//////////////////////////////////////////////////////////////////////////////
// Print a production
//////////////////////////////////////////////////////////////////////////////

std::ostream& Grammar::print( std::ostream& out, Production P, Bool lhs) const
{
  int i;
  if (P == 0)
    return out << "[production ???]";
  if (lhs)
  {
    print(out,P[0]) << "\t->\t";
    i = 1;
  }
  else
    i = 0;
  for ( ; P[i] != END_PRODUCTION; i++)
    print(out,P[i]) << ' ';
  return out;
}

//////////////////////////////////////////////////////////////////////////////
// Print an item
//////////////////////////////////////////////////////////////////////////////

std::ostream& Grammar::print( std::ostream& out, int pos, Production P) const
{
  if (P == 0)
    return out << "[production ???]";
  print(out,P[0]) << "\t->\t";
  for (int i = 1; ; i++)
  {
    if (pos == i - 1)
      out << ". ";
    if (P[i] == END_PRODUCTION)
      break;
    if (isAction(P[i]))
    {
      if (P[i+1] != END_PRODUCTION)
      {
        out << '@' << (- P[i] + END_PRODUCTION) << ' ';
      }
    }
    else
    {
      print(out,P[i]) << ' ';
    }
  }
  return out;
}

//////////////////////////////////////////////////////////////////////////////
// Print the grammar: one on each line and omit printing the same
// lhs non-terminal on subsequent lines.
//////////////////////////////////////////////////////////////////////////////

std::ostream& operator << (std::ostream& out, const Grammar& G)
{
  NonTerminal A = 0;
  for (int i = 0; i < G.size(); i++)
  {
    Production P = G[i];
    if (P == 0)
    {
      out << "???\n";
    }
    else
    {
      out << '{' << i << "}\t";
      if (A == P[0])
        G.print(out << "\t| \t", P + 1, false);
      else
        G.print(out, P);
      out << '\n';
      A = P[0];
    }
  }
  return out;
}
