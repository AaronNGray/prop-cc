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

#include <stddef.h>
#include <stdlib.h>
#include <string>
#include <ctype.h>
#include <AD/generic/generic.h>  // Generic definitions
#include <AD/contain/charset.h>  // Character set
#include <AD/strings/regexp.h>   // Regular expression search

// Local variables
static CharSet alpha;    // set of alpha characters
static CharSet numeric;  // set of numeric characters
static CharSet space;    // set of space characters
static CharSet word;     // set of word characters

static void init()
{
  for (register int c = 0; c < 256; c++)
  {
    if (isalpha(c))
      alpha += c;
    if (isdigit(c))
      numeric += c;
    if (isspace(c))
      space += c;
    if (isalnum(c))
      word += c;
  }
  word += '_';
}

//
//   The set of opcodes used by the NFA matching machine
//

enum { SUCCESS = 0,            // accept state
       BEGIN_OF_LINE = 1,      // match the beginning of a line
       END_OF_LINE = 2,        // match the end of a line
       WILD_CARD = 3,          // matches anything besides '\n'
       MATCH_LITERAL = 4,      // matches a literal string
       MATCH_SET = 5,          // matches any character in a set
       MATCH_CHAR_STAR = 6,    // matches a character zero or more times
       MATCH_CHAR_PLUS = 7,    // matches a character one or more times
       MATCH_SET_STAR = 8,     // matches a set zero or more times
       MATCH_SET_PLUS = 9,     // matches a set one or more times
       OR = 10,                // disjunction, branch unlikely
       PLUS = 11,              // disjunction, branch likely
       JUMP = 12,              // unconditional jump
       TIMES = 13,             // match a subexpression m to n times.
       MATCH_BOUND = 14,       // match word boundary
       MATCH_NON_BOUND = 15,   // match non-word boundary
       MATCH_WORD_BEGIN = 16,  // match beginning of a word
       MATCH_WORD_END = 17,    // match end of a word
       REF = 20,               // matches a backward reference
       OPEN = 30,              // beginning of a reference
       CLOSE = 40              // end of a reference
     };

RegExp::RegExp( const RegExp& re) : nfa(0)
{
  *this = re;
}

RegExp& RegExp::operator = (const RegExp& re)
{
  if (this != &re)
  {
    delete [] nfa;
    nfa = NULL;
    if (re.nfa)
    {
      nfa = new Opcode [size = re.size];
      memcpy(nfa,re.nfa,sizeof(Opcode) * size);
      minMatchLen = re.minMatchLen;
    }
  }
  return *this;
}

//
//  The main pattern matcher, returns the character following
// the entire matched text if successful; otherwise, returns NULL
//

const char * RegExp::grep( register const Opcode * PC,    // current opcode
                           register const char * text,    // current character
                           register const char * textEnd  // end of text string
                         )
{
  register char c = *text++;  // cache the first character
  int n, len, minTimes, times;

  for (;;)
  {
    switch (*PC++)
    {
    case SUCCESS:
      return text-1;
    case BEGIN_OF_LINE:
      if (text - 1 != myText)
        return NULL;
      break;
    case END_OF_LINE:
      if (text > textEnd)
        break;
      if (c == '\n')
      {
        c = *text++;
        break;
      }
      return NULL;
    case WILD_CARD:
      if (text > textEnd || c == '\n')
        return NULL;
      c = *text++;
      break;
    case OPEN+0:
    case OPEN+1:
    case OPEN+2:
    case OPEN+3:
    case OPEN+4:
    case OPEN+5:
    case OPEN+6:
    case OPEN+7:
    case OPEN+8:
    case OPEN+9:
      left[PC[-1] - OPEN] = text - myText - 1;
      break;
    case CLOSE+0:
    case CLOSE+1:
    case CLOSE+2:
    case CLOSE+3:
    case CLOSE+4:
    case CLOSE+5:
    case CLOSE+6:
    case CLOSE+7:
    case CLOSE+8:
    case CLOSE+9:
      right[PC[-1] - CLOSE] = text - myText - 2;
      break;
    case REF+0:
    case REF+1:
    case REF+2:
    case REF+3:
    case REF+4:
    case REF+5:
    case REF+6:
    case REF+7:
    case REF+8:
    case REF+9:
      n = PC[-1] - REF;
      len = right[n] - left[n];
      if (text+len >= textEnd || len < 0 ||
          memcmp(myText+left[n],text-1,len))
        return NULL;
      text += len - 1;
      c = *text++;
      break;

    case MATCH_LITERAL:
      len = *PC++ - 1;
      if (c != *PC++ || text + len > textEnd || memcmp(text,PC,len))
        return NULL;
      PC += len;
      text += len;
      c = *text++;
      break;

    case MATCH_SET:
      if (text > textEnd ||
          bitOf((Byte *)PC,(unsigned char)c) == 0)
        return NULL;
      PC += 32;
      c = *text++;
      break;

    case MATCH_CHAR_PLUS:
      minTimes = 1;
      goto Match_char;
    case MATCH_CHAR_STAR:
      minTimes = 0;
Match_char:
      {
        c = PC[1];
        PC += 2;
        for (times = 0, text--; text < textEnd; text++, times++)
          if (*text != c)
            break;
        for ( ;times >= minTimes; times--, text--)
        {
          const char * matchEnd = this->grep(PC,text,textEnd);
          if (matchEnd)
            return matchEnd;
        }
        return NULL;
      }
    case MATCH_SET_PLUS:
      minTimes = 1;
      goto Match_set;
    case MATCH_SET_STAR:
      minTimes = 0;
Match_set:
      {
        for (times = 0, text--; text < textEnd; text++, times++)
          if (bitOf((Byte *)PC,(unsigned char)*text) == 0)
            break;
        for ( PC += 32; times >= minTimes; times--, text--)
        {
          const char * matchEnd = this->grep(PC,text,textEnd);
          if (matchEnd)
            return matchEnd;
        }
        return NULL;
      }

    case TIMES:  // Try subpattern m to n times
      return this->times(PC[0], PC[1], text-1, textEnd, PC+2);
    case MATCH_WORD_BEGIN:  // Beginning of a word??
      if ( text > textEnd || ! word[c] ||
           text - 1 > myText && word[text[-2]])
        return NULL;
      break;
    case MATCH_WORD_END:  // End of a word??
      if ( text <= textEnd && ! word[c] ||
           text < textEnd && word[c])
        return NULL;
      break;
    case MATCH_BOUND:  // A word boundary??
      if ( (text > textEnd || ! word[c]) &&
           (text - 2 < myText || ! word[text[-2]]) ||
           text <= textEnd && word[c] &&
           text - 2 >= myText && word[text[-2]] )
        return NULL;
      break;
    case MATCH_NON_BOUND: // Not a word boundary??
      if ( text <= textEnd && word[c] &&
           (text - 2 < myText || ! word[text[-2]]) ||
           (text > textEnd || ! word[c]) &&
           text - 2 >= myText && word[text[-2]] )
        return NULL;
      break;
    case OR:  // Try one alternate, then another
      {  const char * success = this->grep(PC+2,text-1,textEnd);
        if (success)
          return success;
        else
          PC += PC[0] * 256 + PC[1];
      }  break;
    case PLUS:  // Try one alternate, then another
      {  const char * good =
          this->grep(PC+PC[0] * 256 + PC[1],text-1,textEnd);
        if (good)
          return good;
        else
          PC += 2;
      }  break;
    case JUMP: // Unconditional jump
      PC += PC[0] * 256 + PC[1];
      break;
    default:
      return NULL;
    }
  }
  return NULL;
}

//
// Call and matches a subpattern |minTimes| to |maxTimes| times.
// Notice that |maxTimes < 0| means that the maximum times is infinite.
//

const char * RegExp::times( int minTimes,
                            int maxTimes,
                            const Opcode * PC,
                            const char * text,
                            const char * textEnd
                          )
{
  const char * matched;
  while (minTimes >= 0 && maxTimes >= 0)
  {
    if (maxTimes == 1)
      return this->grep(PC,text,textEnd);
    else if (maxTimes < 0)
      matched = this->times(minTimes-1,-1,PC,text,textEnd);
    else
      matched = this->times(minTimes-1,maxTimes-1,PC,text,textEnd);
    if (matched == NULL)
      return NULL;
    if (minTimes < 0)
      return matched;
    text = matched;
  }
  return NULL;
}

//
// Main entry point of the pattern matcher
//

int RegExp::Match( register const char * text, int length)
{
  if (nfa == NULL)
    return -1;
  if (length < 0)
    length = strlen(text);
  register int c;

  myText = text;
  const char * textEnd = text + length;
  register const char * limit;
  if (minMatchLen > 0)
    limit = textEnd - minMatchLen + 1;
  else
    limit = textEnd;

  switch (*nfa)
  {
  case BEGIN_OF_LINE:  // Anchored match
    if ((matchedTextEnd = this->grep(nfa+1,text,textEnd)))
    {
      matchedText = text;
      return matchedText - myText;
    }
    return -1;
  case MATCH_LITERAL:  // Starts with a literal
    {  int len = nfa[1];
      for ( c = nfa[2]; text < limit; text++)
        if (c == *text && text + len <= textEnd &&
            memcmp(text,nfa+2,len) == 0)
          if ((matchedTextEnd = this->grep(nfa+len+2,text+len,textEnd)))
          {
            matchedText = text;
            return matchedText - myText;
          }
      return -1;
    }
  case MATCH_CHAR_PLUS: // Starts with a character
    for ( c = nfa[2]; text < limit; text++)
      if (c == *text)
        if ((matchedTextEnd = this->grep(nfa,text,textEnd)))
        {
          matchedText = text;
          return matchedText - myText;
        }
    return -1;
  case MATCH_SET:
  case MATCH_SET_PLUS: // Starts with a set
    {  register Byte * set
        = (Byte*)(nfa+1);
      for ( ; text < limit; text++)
        if (bitOf(set
                  ,(unsigned char)*text))
          if ((matchedTextEnd = this->grep(nfa,text,textEnd)))
          {
            matchedText = text;
            return matchedText - myText;
          }
      return -1;
    }
  default:   // Can start with anything
    for ( ;text < limit; text++)
      if ((matchedTextEnd = this->grep(nfa,text,textEnd)))
      {
        matchedText = text;
        return matchedText - myText;
      }
    return -1;
  }
}

//
// Compile a new pattern
//

RegExp& RegExp::compile( const char* pattern, const char* meta)
{
  delete [] nfa;               // delete last compiled pattern, if any
  nfa = NULL;
  if (meta == NULL)            // set default meta characters
    meta = "*+()[]?^$-.|\\\0";

  MetaChar M[256];             // meta character assignment

  if (! space[' '])
    init();    // initialize, if necessary

  //
  // Compute the meta character assignment
  //
  for (int i = 0; i < 256; i++)
    M[i] = META_NONE;
  for (int j = META_STAR; j <= META_EOP; j++)
    M[ meta[j] ] = (MetaChar)j;

  size = this->comp(pattern, M, false);  // compile it once to get the size

  if (size > 0)
  {
    nfa = new Opcode [size];            // allocate new storage
    this->comp(pattern, M, true);       // compile it again to emit opcodes
    minMatchLen = this->minMatch(nfa);  // compute the minimal matching len
  }

  return *this;
}

inline void shift(register RegExp::Opcode * start,
                  register RegExp::Opcode * end,
                  register int size)
{
  while (end > start)
  {
    end--;
    end[size] = end[0];
  }
}

//
// ``Parse'' pattern and compile the NFA
//

int RegExp::comp(const char* pattern, const MetaChar M[], Bool emit)
{
  register const char * p;        // pointer to pattern
  register char c;                // cached pattern character
  register int size = 0;          // size of the nfa
  register Opcode * PC = nfa;     // nfa opcodes
  Opcode * last;                  // last opcode
  CharSet set
    ;                    // a character set
  int level = 0;                  // nesting level
  Opcode * start[10];             // starting point for subpattern
  int parenCount = 0;             // parenthesis count
  int paren[10];                  // closing parenthesis number
  Bool complement = false;        // set complement??

  start[0] = PC;   // starting point of first pattern

  for (last = NULL, p = pattern; M[c = *p++] != META_EOP; )
  {
    switch (M[c])
    {
    case META_STAR:
      if (emit)
      {
        if (last)
        {
          switch (last[0])
          {
          case MATCH_LITERAL:
            if (last[1] == 1)
              last[0] = MATCH_CHAR_STAR;
            else
              goto Emit_star;
            break;
          case MATCH_CHAR_PLUS:
            last[0] = MATCH_CHAR_STAR;
            break;
          case MATCH_CHAR_STAR:
            break;
          case MATCH_SET:
          case MATCH_SET_PLUS:
            last[0] = MATCH_SET_STAR;
            break;
          case MATCH_SET_STAR:
            break;
          default:
Emit_star:
            *PC++ = JUMP;
            *PC++ = (last - PC - 2) / 256;
            *PC++ = (last - PC - 2) % 256;
            shift(last,PC,3);
            last[0] = OR;
            last[1] = (PC - last + 2) / 256;
            last[2] = (PC - last + 2) % 256;
            PC += 3;
            break;
          }
        }
        else
          goto Syntax_Error;
      }
      else
        size += 6;
      break;
    case META_PLUS:
      if (emit)
      {
        if (last)
        {
          switch (last[0])
          {
          case MATCH_LITERAL:
            if (last[1] == 1)
              last[0] = MATCH_CHAR_PLUS;
            else
              goto Emit_plus;
            break;
          case MATCH_CHAR_PLUS:
          case MATCH_CHAR_STAR:
          case MATCH_SET_PLUS:
          case MATCH_SET_STAR:
            break;
          case MATCH_SET:
            last[0] = MATCH_SET_PLUS;
            break;
          default:
Emit_plus:
            *PC++ = PLUS;
            *PC++ = (last - PC + 1) / 256;
            *PC++ = (last - PC + 1) % 256;
            break;
          }
        }
        else
          goto Syntax_Error;
      }
      else
        size += 3;
      break;
    case META_OPTIONAL:
      if (emit)
      {
        if (last == NULL)
          goto Syntax_Error;
        shift(last,PC,3);
        last[0] = OR;
        last[1] = (PC - last + 2) / 256;
        last[2] = (PC - last + 2) % 256;
        PC += 3;
      }
      else
        size += 3;
      break;
    case META_OR:
      if (emit)
      {
        *PC++ = SUCCESS;
        shift(start[level],PC,3);
        start[level][0] = OR;
        start[level][1] = (PC - start[level] + 2) / 256;
        start[level][2] = (PC - start[level] + 2) % 256;
        PC += 3;
      }
      else
        size += 4;
      break;
    case META_OPEN:
      if (emit)
      {
        last = PC;
        *PC = OPEN + parenCount;
      }
      else
        size++;
      paren[level] = parenCount;
      if (++parenCount >= 10)
        goto Syntax_Error;
      if (++level >= 10)
        goto Syntax_Error;
      start[level] = PC++;
      break;
    case META_CLOSE:
      last = start[level];
      if (--level < 0)
        goto Syntax_Error;
      if (emit)
      {
        *PC++ = CLOSE + paren[level];
      }
      else
        size++;
      break;
    case META_BEGIN:
      last = PC;
      if (emit)
        *PC++ = BEGIN_OF_LINE;
      else
        size++;
      break;
    case META_END:
      last = PC;
      if (emit)
        *PC++ = END_OF_LINE;
      else
        size++;
      break;
    case META_WILD:
      last = PC;
      if (emit)
        *PC++ = WILD_CARD;
      else
        size++;
      break;
    case META_SET_OPEN:
      {
        set.clear();
        const char * start = p;
        int lastChar = -1;
        while (M[c = *p++] != META_SET_CLOSE)
        {
          if (c == '^' && p-1 == start)
          {
            complement = true;
            continue;
          }
          switch (M[c])
          {
          case META_EOP:
            goto Syntax_Error;
          case META_RANGE:
            lastChar = p[-2];
            break;
          case META_ESCAPE:
            switch (c = *p++)
            {
            case 'n':
              set
                += '\n';
              break;
            case 't':
              set
                += '\t';
              break;
            case '0':
            case '1':
              const char * q;
              for (q = p, c -= 0;
                   *p >= '0' && *p <= '7' && p - q <= 2; p++)
                c = c * 8 + *p - '0';
              set
                += c;
              break;
            case 'd':
              set
                += numeric;
              break;
            case 'D':
              set
                += ! numeric;
              break;
            case 's':
              set
                += space;
              break;
            case 'S':
              set
                += ! space;
              break;
            case 'w':
              set
                += word;
              break;
            case 'W':
              set
                += ! word;
              break;
            default:
              goto Emit_set_char;
            }
            break;
          default:
Emit_set_char:
            if (lastChar >= 0)
              for ( ;lastChar <= c; lastChar++)
                set
                  += lastChar;
            else
              set
                += c;
            lastChar = -1;
            break;
          }
        }
      }
Emit_match_set:
      {
        if (emit)
        {
          if (complement)
            set
              = ! set
                  ;
          last = PC;
          *PC++ = MATCH_SET;
          memcpy(PC,(const Byte *)set
                 ,32);
          PC += 32;
          complement = false;
        }
        else
          size += 33;
      }
      break;
    case META_ESCAPE:
      switch (c = *p++)
      {
      case 'n':
        c = '\n';
        goto Emit_match_char;  // new line
      case 't':
        c = '\t';
        goto Emit_match_char;  // tab
      case '0':
      case '1':
        {
          const char * q;
          for (q = p, c -= '0'; *p >= '0' && *p <= '7' &&
               p - q <= 2; p++)
            c = c * 8 + *p - '0';
          goto Emit_match_char;
        }
      case 'd':
        set
          = numeric;
        goto Emit_match_set;
      case 'D':
        set
          = ! numeric;
        goto Emit_match_set;
      case 'w':
        set
          = word;
        goto Emit_match_set;
      case 'W':
        set
          = ! word;
        goto Emit_match_set;
      case 's':
        set
          = space;
        goto Emit_match_set;
      case 'S':
        set
          = ! space;
        goto Emit_match_set;
      case 'b':
        if (emit)
          *PC++ = MATCH_BOUND;
        else
          size++;
        break;
      case 'B':
        if (emit)
          *PC++ = MATCH_NON_BOUND;
        else
          size++;
        break;
      case '<':
        if (emit)
          *PC++ = MATCH_WORD_BEGIN;
        else
          size++;
        break;
      case '>':
        if (emit)
          *PC++ = MATCH_WORD_END;
        else
          size++;
        break;
      default:
        goto Emit_match_char;
      }
      break;
    case META_NONE:
Emit_match_char:
      if (emit)
      {
        if (last && *last == MATCH_LITERAL &&
            M[*p] != META_STAR && M[*p] != META_PLUS &&
            M[*p] != META_OPTIONAL)
        {
          last[1]++;
          *PC++ = c;
        }
        else
        {
          last = PC;
          *PC++ = MATCH_LITERAL;
          *PC++ = 1;
          *PC++ = c;
        }
      }
      else
        size += 3;
      break;
    default:
      break;
    }
  }

  if (emit)
    *PC++ = SUCCESS;

  return size+1;

Syntax_Error:

  return -1;
}

//
// Traverse the opcode and compute the minimal length of the matched text
//

int RegExp::minMatch( register const Opcode * PC)
{
  register int len = 0;
  for (;;)
  {
    switch (*PC++)
    {
    case SUCCESS:
      return len;
    case WILD_CARD:
      len++;
      break;
    case MATCH_CHAR_STAR:
      PC += 2;
      break;
    case MATCH_CHAR_PLUS:
      len++;
      PC += 2;
      break;
    case MATCH_SET_STAR:
      PC += 32;
      break;
    case MATCH_SET_PLUS:
    case MATCH_SET:
      len++;
      PC += 32;
      break;
    case MATCH_LITERAL:
      len += *PC;
      PC += *PC + 1;
      break;
    case OR:
      {
        int len1 = this->minMatch(PC + PC[0] * 256 + PC[1]);
        int len2 = this->minMatch(PC + 2);
        return len + (len1 < len2 ? len1 : len2);
      }
    case TIMES:
      PC += 2;
      break;
    case MATCH_BOUND:
    case MATCH_NON_BOUND:
    case MATCH_WORD_BEGIN:
    case MATCH_WORD_END:
    case BEGIN_OF_LINE:
    case END_OF_LINE:
    case REF+0:
    case REF+1:
    case REF+2:
    case REF+3:
    case REF+4:
    case REF+5:
    case REF+6:
    case REF+7:
    case REF+8:
    case REF+9:
      break;
    default:
      return len;
    }
  }
}
