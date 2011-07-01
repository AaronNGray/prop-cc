///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.6),
//  last updated on Nov 2, 1999.
//  The original source file is "treegram.pcc".
///////////////////////////////////////////////////////////////////////////////

#line 1 "treegram.pcc"
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

#include <string.h>
#include <assert.h>
#include <AD/automata/treegram.h>
#include <AD/contain/bitset.h>

//////////////////////////////////////////////////////////////////////////////
//  Make hidden types visible
//////////////////////////////////////////////////////////////////////////////
typedef TreeGrammar::TreeProduction TreeProduction;
typedef TreeGrammar::Functor        Functor;
typedef TreeGrammar::Arity          Arity;

//////////////////////////////////////////////////////////////////////////////
//  Function to allocate a new term
//////////////////////////////////////////////////////////////////////////////
TreeTerm new_term(Mem& mem, short int f, unsigned char n, TreeTerm * subterms)
{  TreeTerm * S = n > 0 ? (TreeTerm*)mem.c_alloc(sizeof(TreeTerm) * n) : 0;
   if (subterms) for (int i = n - 1; i >= 0; i--) S[i] = subterms[i];
   return 
#line 43 "treegram.pcc"
#line 43 "treegram.pcc"
new (mem) TreeTerm_tree_term(f,n,S)
#line 43 "treegram.pcc"
#line 43 "treegram.pcc"
;
}

//////////////////////////////////////////////////////////////////////////////
//  Method to initialize an instance
//////////////////////////////////////////////////////////////////////////////
void TreeGrammar::init()
   {  productions           = 0; 
      arities               = 0;
      minimum_functor       = maximum_functor = 
      minimum_variable      = maximum_variable = 0;
      maximum_arity         = 0;
      number_of_productions = 0;
      number_of_variables   = 0;
      number_of_functors    = 0;
      functor_names         = 0;
      variable_names        = 0;
   }

//////////////////////////////////////////////////////////////////////////////
//  Constructors and destructor
//////////////////////////////////////////////////////////////////////////////
TreeGrammar::TreeGrammar() { init(); }
TreeGrammar::TreeGrammar(int n, TreeProduction P[], const char * f[], const char * v[]) 
   { init(); compile(n,P,f,v); }
TreeGrammar::~TreeGrammar()
{  delete [] productions;
   delete [] arities;
}

//////////////////////////////////////////////////////////////////////////////
// Method to compile a set of tree productions
//////////////////////////////////////////////////////////////////////////////
void TreeGrammar::compile
   ( int                  n,       // number of productions
     TreeProduction       P[],     // an array of tree productions
     const char *         f_names[], // names of functors
     const char *         v_names[], // names of variables(non-terminals)
     Functor              min_f,   // user supplied minimal functor encoding
     Functor              max_f,   // user supplied maximal functor encoding
     Variable             min_v,   // user supplied minimal variable encoding
     Variable             max_v    // user supplied maximal variable encoding
   )
{  
   ///////////////////////////////////////////////////////////////////////////
   //  (1)  Allocate the productions array and initialize various members.
   ///////////////////////////////////////////////////////////////////////////
   productions           = new TreeProduction [n];
   minimum_functor       = min_f;
   maximum_functor       = max_f;
   minimum_variable      = min_v;
   maximum_variable      = max_v;
   maximum_arity         = 0;
   number_of_productions = n;
   functor_names         = f_names;
   variable_names        = v_names;
   memcpy(productions,P,n * sizeof(TreeProduction));

   ///////////////////////////////////////////////////////////////////////////
   //  (2) Compute the ranges of non-terminals and functors.
   ///////////////////////////////////////////////////////////////////////////
   int i;
   for (i = 0; i < n; i++) {
      Variable v = P[i].var;
      if (v < minimum_variable) minimum_variable = v;
      if (v > maximum_variable) maximum_variable = v;
      tabulate(P[i].term);
   }
   if (minimum_functor  > maximum_functor ) minimum_functor  = maximum_functor = 0;
   if (minimum_variable > maximum_variable) minimum_variable = maximum_variable = 0;
   number_of_variables = maximum_variable - minimum_variable + 1;
   number_of_functors  = maximum_functor - minimum_functor + 1;

   ///////////////////////////////////////////////////////////////////////////
   //  (3) Compute the mapping from functors to their rank.
   ///////////////////////////////////////////////////////////////////////////
   arities = new Arity [number_of_functors];
   memset(arities, 0, number_of_functors * sizeof(Arity));
   for (i = 0; i < n; i++) tabulate_arity(P[i].term);

   assert(minimum_variable >= 0);
   assert(minimum_functor >= 0);
}

//////////////////////////////////////////////////////////////////////////////
//  Auxiliary method to compute the ranges of non-terminals and functors.
//////////////////////////////////////////////////////////////////////////////
void TreeGrammar::tabulate(const TreeTerm t)
{  
#line 131 "treegram.pcc"
#line 143 "treegram.pcc"
{
   if (t) {
      switch (t->tag__) {
         case a_TreeTerm::tag_tree_term: {
#line 138 "treegram.pcc"
            
            if (_tree_term(t)->_1 < minimum_functor) minimum_functor = _tree_term(t)->_1;
            if (_tree_term(t)->_1 > maximum_functor) maximum_functor = _tree_term(t)->_1;
            for (int i = _tree_term(t)->_2 - 1; i >= 0; i--) tabulate(_tree_term(t)->_3[i]);
            
#line 142 "treegram.pcc"
            } break;
         case a_TreeTerm::tag_var_term: {
#line 133 "treegram.pcc"
           if (_var_term(t)->var_term < minimum_variable) minimum_variable = _var_term(t)->var_term;
            if (_var_term(t)->var_term > maximum_variable) maximum_variable = _var_term(t)->var_term;
            
#line 135 "treegram.pcc"
            } break;
         case a_TreeTerm::tag_and_term: {
#line 135 "treegram.pcc"
           tabulate(_and_term(t)->_1); tabulate(_and_term(t)->_2);
            
#line 136 "treegram.pcc"
            } break;
         case a_TreeTerm::tag_or_term: {
#line 136 "treegram.pcc"
          tabulate(_or_term(t)->_1); tabulate(_or_term(t)->_2);
            
#line 137 "treegram.pcc"
            } break;
         case a_TreeTerm::tag_not_term: {
#line 137 "treegram.pcc"
         tabulate(_not_term(t)->not_term); 
            
#line 138 "treegram.pcc"
            } break;
         default: {
#line 142 "treegram.pcc"
          // do nothing
            
#line 143 "treegram.pcc"
            } break;
      }
   } else {
#line 132 "treegram.pcc"
   // do nothing 
      
#line 133 "treegram.pcc"
   }
}
#line 143 "treegram.pcc"
#line 143 "treegram.pcc"

}

//////////////////////////////////////////////////////////////////////////////
//  Auxiliary method to compute the arity of functors.
//////////////////////////////////////////////////////////////////////////////
void TreeGrammar::tabulate_arity(const TreeTerm t)
{  
#line 150 "treegram.pcc"
#line 160 "treegram.pcc"
{
   if (t) {
      switch (t->tag__) {
         case a_TreeTerm::tag_tree_term: {
#line 154 "treegram.pcc"
            
            arities[_tree_term(t)->_1] = _tree_term(t)->_2;
            for (int i = _tree_term(t)->_2 - 1; i >= 0; i--)
               tabulate_arity(_tree_term(t)->_3[i]);
            if (_tree_term(t)->_2 > maximum_arity) maximum_arity = _tree_term(t)->_2;
            
#line 159 "treegram.pcc"
            } break;
         case a_TreeTerm::tag_and_term: {
#line 151 "treegram.pcc"
           tabulate_arity(_and_term(t)->_1); tabulate_arity(_and_term(t)->_2);
            
#line 152 "treegram.pcc"
            } break;
         case a_TreeTerm::tag_or_term: {
#line 152 "treegram.pcc"
          tabulate_arity(_or_term(t)->_1); tabulate_arity(_or_term(t)->_2); 
            
#line 153 "treegram.pcc"
            } break;
         case a_TreeTerm::tag_not_term: {
#line 153 "treegram.pcc"
         tabulate_arity(_not_term(t)->not_term);
            
#line 154 "treegram.pcc"
            } break;
         default: {
            L1:; 
#line 159 "treegram.pcc"
  // do nothing
            
#line 160 "treegram.pcc"
            } break;
      }
   } else { goto L1; }
}
#line 160 "treegram.pcc"
#line 160 "treegram.pcc"
        
}

///////////////////////////////////////////////////////////////////////////
//  Equality for terms.   Shallow comparison only
///////////////////////////////////////////////////////////////////////////
Bool equal(const TreeTerm a, const TreeTerm b)
{  
#line 167 "treegram.pcc"
#line 179 "treegram.pcc"
{
   if (a) {
      switch (a->tag__) {
         case a_TreeTerm::tag_tree_term: {
            if (b) {
               switch (b->tag__) {
                  case a_TreeTerm::tag_tree_term: {
#line 173 "treegram.pcc"
                     
                     if (_tree_term(a)->_1 != _tree_term(b)->_1 || _tree_term(a)->_2 != _tree_term(b)->_2) return false;
                     for (int i = _tree_term(a)->_2 - 1; i >= 0; i--) 
                        if (_tree_term(a)->_3[i] != _tree_term(b)->_3[i]) return false;
                     return true;
                     
#line 178 "treegram.pcc"
                     } break;
                  default: {
                     L2:; 
#line 178 "treegram.pcc"
               return false;
                     
#line 179 "treegram.pcc"
                     } break;
               }
            } else { goto L2; }
            } break;
         case a_TreeTerm::tag_var_term: {
            if (b) {
               switch (b->tag__) {
                  case a_TreeTerm::tag_var_term: {
#line 169 "treegram.pcc"
              return _var_term(a)->var_term == _var_term(b)->var_term;
                     
#line 170 "treegram.pcc"
                     } break;
                  default: { goto L2; } break;
               }
            } else { goto L2; }
            } break;
         case a_TreeTerm::tag_and_term: {
            if (b) {
               switch (b->tag__) {
                  case a_TreeTerm::tag_and_term: {
#line 171 "treegram.pcc"
                 return _and_term(a)->_1 == _and_term(b)->_1 && _and_term(a)->_2 == _and_term(b)->_2; 
                     
#line 172 "treegram.pcc"
                     } break;
                  default: { goto L2; } break;
               }
            } else { goto L2; }
            } break;
         case a_TreeTerm::tag_or_term: {
            if (b) {
               switch (b->tag__) {
                  case a_TreeTerm::tag_or_term: {
#line 170 "treegram.pcc"
                return _or_term(a)->_1 == _or_term(b)->_1 && _or_term(a)->_2 == _or_term(b)->_2; 
                     
#line 171 "treegram.pcc"
                     } break;
                  default: { goto L2; } break;
               }
            } else { goto L2; }
            } break;
         case a_TreeTerm::tag_not_term: { goto L2; } break;
         default: {
            if (b) {
               switch (b->tag__) {
                  case a_TreeTerm::tag_set_term: {
#line 172 "treegram.pcc"
              return _set_term(a)->set_term == _set_term(b)->set_term;
                     
#line 173 "treegram.pcc"
                     } break;
                  default: { goto L2; } break;
               }
            } else { goto L2; }
            } break;
      }
   } else {
      if (b) { goto L2; } else {
#line 168 "treegram.pcc"
 return true;
         
#line 169 "treegram.pcc"
      }
   }
}
#line 179 "treegram.pcc"
#line 179 "treegram.pcc"

}

///////////////////////////////////////////////////////////////////////////
//  Hash function for terms
///////////////////////////////////////////////////////////////////////////
unsigned int hash(const TreeTerm a)
{  
#line 186 "treegram.pcc"
#line 197 "treegram.pcc"
{
   if (a) {
      switch (a->tag__) {
         case a_TreeTerm::tag_tree_term: {
#line 192 "treegram.pcc"
            
            unsigned int h = _tree_term(a)->_1;
            for (int i = _tree_term(a)->_2 - 1; i >= 0; i--) h += h + (unsigned int)_tree_term(a)->_3[i];
            return h;
            
#line 196 "treegram.pcc"
            } break;
         case a_TreeTerm::tag_var_term: {
#line 188 "treegram.pcc"
       return _var_term(a)->var_term;
            
#line 189 "treegram.pcc"
            } break;
         case a_TreeTerm::tag_and_term: {
#line 190 "treegram.pcc"
          return 245 + (unsigned int)_and_term(a)->_1 + (unsigned int)_and_term(a)->_2; 
            
#line 191 "treegram.pcc"
            } break;
         case a_TreeTerm::tag_or_term: {
#line 189 "treegram.pcc"
         return 493 + (unsigned int)_or_term(a)->_1 + (unsigned int)_or_term(a)->_2;
            
#line 190 "treegram.pcc"
            } break;
         case a_TreeTerm::tag_not_term: {
#line 191 "treegram.pcc"
        return 127 + (unsigned int)_not_term(a)->not_term;
            
#line 192 "treegram.pcc"
            } break;
         default: {
#line 196 "treegram.pcc"
       return (unsigned int)_set_term(a)->set_term;
            
#line 197 "treegram.pcc"
            } break;
      }
   } else {
#line 187 "treegram.pcc"
return 73;
      
#line 188 "treegram.pcc"
   }
}
#line 197 "treegram.pcc"
#line 197 "treegram.pcc"

}

///////////////////////////////////////////////////////////////////////////
//  Printing methods.
///////////////////////////////////////////////////////////////////////////

const char * TreeGrammar::functor_name(Functor f) const
{  if (functor_names && f >= min_functor() && f <= max_functor()) 
      return functor_names[f];
   else
      return "F";
}

const char * TreeGrammar::variable_name(Variable v) const
{  if (variable_names && v >= min_variable() && v <= max_variable() &&
       variable_names[v] != 0) 
      return variable_names[v];
   else
      return "V";
}

///////////////////////////////////////////////////////////////////////////
//  Method to print a functor name.
///////////////////////////////////////////////////////////////////////////
std::ostream& TreeGrammar::print_functor(std::ostream& out, Functor f) const
{  if (functor_names && f >= min_functor() && f <= max_functor()) 
      return out << functor_names[f];
   else
      return out << 'F' << f;
}

///////////////////////////////////////////////////////////////////////////
//  Method to print a variable name.
///////////////////////////////////////////////////////////////////////////
std::ostream& TreeGrammar::print_variable(std::ostream& out, Variable v) const
{  if (variable_names && v >= min_variable() && v <= max_variable() &&
       variable_names[v] != 0) 
      return out << '<' << variable_names[v] << '>';
   else
      return out << v;
}

///////////////////////////////////////////////////////////////////////////
//  Method to print a tree term.
///////////////////////////////////////////////////////////////////////////
std::ostream& TreeGrammar::print(std::ostream& S, const TreeTerm term) const
{  
#line 244 "treegram.pcc"
#line 286 "treegram.pcc"
{
   if (term) {
      switch (term->tag__) {
         case a_TreeTerm::tag_tree_term: {
#line 251 "treegram.pcc"
           
            {  const char * f_name = functor_name(_tree_term(term)->_1);
               Bool first = true;
               TreeTerm t = term;
               if (f_name[0] == '#')
               {  char begin_ch = f_name[1];
                  char end_ch   = f_name[strlen(f_name)-1];
                  S << '#' << begin_ch;
                  
#line 259 "treegram.pcc"
#line 267 "treegram.pcc"
            {
               for (;;) {
                  if (t) {
                     switch (t->tag__) {
                        case a_TreeTerm::tag_tree_term: {
                           switch (_tree_term(t)->_2) {
                              case 0: {
                                 if (
#line 264 "treegram.pcc"
                                 (functor_name(_tree_term(t)->_1)[0] == '#')
#line 264 "treegram.pcc"
) {
                                    
#line 265 "treegram.pcc"
                                  return S << end_ch; 
#line 265 "treegram.pcc"
                                 } else {
                                    
                                    L4:; 
#line 267 "treegram.pcc"
                                  if (! first) S << " ... "; print(S,t); return S << end_ch; 
#line 267 "treegram.pcc"
                                 }
                              } break;
                              case 2: {
#line 261 "treegram.pcc"
                               if (! first) S << ", "; print(S,_tree_term(t)->_3[0]); first = false;
                                 t = _tree_term(t)->_3[1];
                                 
#line 263 "treegram.pcc"
                              } break;
                              default: { goto L4; }
                           }
                           } break;
                        default: { goto L4; } break;
                     }
                  } else { goto L4; }
               }
            }
#line 268 "treegram.pcc"
#line 268 "treegram.pcc"
            
            } else if (f_name[0] != '\0' && f_name[1] == '|')
            {  S << f_name[0] << "| ";
               for (int i = 0; i < _tree_term(term)->_2; i++) {
                   print(S,_tree_term(term)->_3[i]); if (i < _tree_term(term)->_2 - 1) S << ", ";
               }
               S << ' ' << (f_name + 5);
            } else
            {  print_functor(S,_tree_term(term)->_1);
               if (_tree_term(term)->_2 > 0) {
                  S << '(';
                  for (int i = 0; i < _tree_term(term)->_2; i++) {
                      print(S,_tree_term(term)->_3[i]); if (i < _tree_term(term)->_2 - 1) S << ", ";
                  }
                  S << ')';
               }
            }
            }
            
#line 286 "treegram.pcc"
            } break;
         case a_TreeTerm::tag_var_term: {
#line 246 "treegram.pcc"
        print_variable(S, _var_term(term)->var_term);
            
#line 247 "treegram.pcc"
            } break;
         case a_TreeTerm::tag_and_term: {
#line 248 "treegram.pcc"
           S << '('; print(S,_and_term(term)->_1); S << " and: "; print(S,_and_term(term)->_2); S << ')';
            
#line 249 "treegram.pcc"
            } break;
         case a_TreeTerm::tag_or_term: {
#line 247 "treegram.pcc"
          S << '('; print(S,_or_term(term)->_1); S << " or: "; print(S,_or_term(term)->_2); S << ')';
            
#line 248 "treegram.pcc"
            } break;
         case a_TreeTerm::tag_not_term: {
#line 249 "treegram.pcc"
        S << "not: "; print(S,_not_term(term)->not_term);
            
#line 250 "treegram.pcc"
            } break;
         default: {
#line 250 "treegram.pcc"
        S << *_set_term(term)->set_term;
            
#line 251 "treegram.pcc"
            } break;
      }
   } else {
#line 245 "treegram.pcc"
 S << '_';
      
#line 246 "treegram.pcc"
   }
}
#line 286 "treegram.pcc"
#line 286 "treegram.pcc"

   return S;
}

///////////////////////////////////////////////////////////////////////////
//  Method to print a tree production.
///////////////////////////////////////////////////////////////////////////
std::ostream& TreeGrammar::print(std::ostream& out, const TreeProduction& P) const
{   print_variable(out, P.var); 
    out << " : ";
    print(out, P.term);
    return out;
}

///////////////////////////////////////////////////////////////////////////
//  Method to print a tree grammar.
///////////////////////////////////////////////////////////////////////////
std::ostream& operator << (std::ostream& out, const TreeGrammar& G) 
{   for (int i = 0; i < G.size(); i++) {
       out << '[' << i << ']' << '\t';
       G.print(out,G[i]) << '\n';
    }
    return out;
}
#line 310 "treegram.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 55
Number of ifs generated      = 13
Number of switches generated = 12
Number of labels             = 3
Number of gotos              = 15
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
