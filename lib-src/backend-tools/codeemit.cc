//////////////////////////////////////////////////////////////////////////////
// NOTICE:
//
// ADLib, Prop and their related set of tools and documentation are in the
// public domain.   The author(s) of this software reserve no copyrights on
// the source code and any code generated using the tools.  You are encouraged
// to use ADLib and Prop to develop software, in both academic and commercial
// settings, and are welcomed to incorporate any part of ADLib and Prop into
// your programs.
//
// Although you are under no obligation to do so, we strongly recommend that
// you give away all software developed using our tools.
//
// We also ask that credit be given to us when ADLib and/or Prop are used in
// your programs, and that this notice be preserved intact in all the source
// code.
//
// This software is still under development and we welcome(read crave for)
// any suggestions and help from the users.
//
// Allen Leung (leunga@valis.cs.nyu.edu)
// 1994-1995
//////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <string.h>
#include <iostream.h>
#include <AD/backend-tools/codeemit.h>
#include <AD/hash/lhash.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Constructors and destructor
//
//////////////////////////////////////////////////////////////////////////////

CodeEmitter::CodeEmitter() : out(&std::cerr)
{
  init_emitter();
}
CodeEmitter::CodeEmitter(std::ostream& f) : out(&f)
{
  init_emitter();
}
CodeEmitter::~CodeEmitter()
{
  cleanup_emitter();
}

//////////////////////////////////////////////////////////////////////////////
//
//  The internal table
//
//////////////////////////////////////////////////////////////////////////////

class CodeEmitterIntern
{
  CodeEmitterIntern(const CodeEmitter&);
  void operator = (const CodeEmitter&);
public:
  LHashTable<const char *,CodeEmitter::Action> action_map;
  CodeEmitterIntern() : action_map(257)
  {}
  ~CodeEmitterIntern()
  {}
}
;

//////////////////////////////////////////////////////////////////////////////
//
//  Initialization
//
//////////////////////////////////////////////////////////////////////////////

void CodeEmitter::init_emitter()
{
  intern = new CodeEmitterIntern;

  for (size_t i = 0; i < sizeof(abbrev_table)/sizeof(abbrev_table[0]); i++)
    abbrev_table[i] = 0;
  memset(char_table,0,sizeof(char_table));

  line_number = 0;
  tabbing     = 0;
  anchored    = true;

  register_default_actions();
}

//////////////////////////////////////////////////////////////////////////////
//
//  Register the default actions.
//
//////////////////////////////////////////////////////////////////////////////

void CodeEmitter::register_default_actions()
{
  register_char('\n',do_newline);
  register_char('%',do_meta);
  static struct
  {
    const char * name;
    char         abbrev;
    Action       action;
  }
  actions[] = {
                { "char",   'c', do_char },
                { "uchar",  ' ', do_uchar },
                { "short",  ' ', do_short },
                { "ushort", ' ', do_ushort },
                { "int",    'i', do_int },
                { "uint",   'u', do_uint },
                { "long",   ' ', do_long },
                { "ulong",  ' ', do_ulong },
                { "float",  ' ', do_float },
                { "double", 'r', do_double },
                { "char*",  's', do_string }
              };
  for (size_t i = 0; i < sizeof(actions)/sizeof(actions[0]); i++)
  {
    register_action(actions[i].name,actions[i].abbrev,actions[i].action);
  }
}

//////////////////////////////////////////////////////////////////////////////
//
//  Cleanup
//
//////////////////////////////////////////////////////////////////////////////

void CodeEmitter::cleanup_emitter()
{
  delete intern;
}

//////////////////////////////////////////////////////////////////////////////
//
//  Cleanup
//
//////////////////////////////////////////////////////////////////////////////

void CodeEmitter::error(const char * message, ...)
{
  va_list A;
  va_start(A,message);
  CodeEmitter msg(std::cerr);
  msg.emit_driver(message, A);
  va_end(A);
  exit(1);
}

//////////////////////////////////////////////////////////////////////////////
//
//  Open/close a stream
//
//////////////////////////////////////////////////////////////////////////////

CodeEmitter& CodeEmitter::open(std::ostream& f)
{
  out = &f;
  return *this;
}
CodeEmitter& CodeEmitter::close()
{
  return *this;
}

//////////////////////////////////////////////////////////////////////////////
//
//  Method to register a pretty printing action
//
//////////////////////////////////////////////////////////////////////////////

void CodeEmitter::register_action
(ActionName name, ActionAbbrev abbrev, Action action)
{
  // Register abbreviation
  if (abbrev != ' ')
    abbrev_table[abbrev] = action;

  // Register full name
  intern->action_map.insert(name, action);
}

//////////////////////////////////////////////////////////////////////////////
//
//  Method to register a character action
//
//////////////////////////////////////////////////////////////////////////////

void CodeEmitter::register_char(unsigned char name, CharAction action)
{
  char_table[name] = action;
}

//////////////////////////////////////////////////////////////////////////////
//
//  Default pretty printers
//
//////////////////////////////////////////////////////////////////////////////

CodeEmitter& CodeEmitter::operator << (char c)
{
  return emit("%{char}",c);
}

CodeEmitter& CodeEmitter::operator << (unsigned char c)
{
  return emit("%{uchar}",c);
}

CodeEmitter& CodeEmitter::operator << (short s)
{
  return emit("%{short}",s);
}

CodeEmitter& CodeEmitter::operator << (unsigned short s)
{
  return emit("%{ushort}",s);
}

CodeEmitter& CodeEmitter::operator << (int l)
{
  return emit("%{int}",l);
}

CodeEmitter& CodeEmitter::operator << (unsigned int l)
{
  return emit("%{uint}",l);
}

CodeEmitter& CodeEmitter::operator << (long l)
{
  return emit("%{long}",l);
}

CodeEmitter& CodeEmitter::operator << (unsigned long l)
{
  return emit("%{ulong}",l);
}

CodeEmitter& CodeEmitter::operator << (const char * s)
{
  return emit("%{char*}",s);
}

CodeEmitter& CodeEmitter::operator << (double d)
{
  return emit("%{double}",d);
}

CodeEmitter& CodeEmitter::operator << (float f)
{
  return emit("%{float}",f);
}

//////////////////////////////////////////////////////////////////////////////
//
//  The pretty printing driver
//
//////////////////////////////////////////////////////////////////////////////

va_list CodeEmitter::emit_driver( const char * format, va_list args)
{
  for (;;)
  {
    unsigned char c = *format++;
    if (c == '\0')
      break;
    else if (char_table[c])
    {
      format_ptr = format;
      args = (*char_table[c])(*this,c,args);
      format = format_ptr;
    }
    else
    {
      out->put(c);
      anchored = false;
    }
  }
  return args;
}

//////////////////////////////////////////////////////////////////////////////
//
//  The default newline handler
//
//////////////////////////////////////////////////////////////////////////////

va_list CodeEmitter::do_newline( CodeEmitter& C, unsigned char, va_list args)
{
  C.line_number++;
  C.anchored = true;
  C.out->put('\n');
  return args;
}

//////////////////////////////////////////////////////////////////////////////
//
//  The default meta character handler
//
//////////////////////////////////////////////////////////////////////////////

va_list CodeEmitter::do_meta( CodeEmitter& C, unsigned char, va_list args)
{
  char format_name[1024];
  unsigned char c = *C.format_ptr++;
  if (c == '{')
  {
    char * p = format_name;
    const char * q = C.format_ptr;
    for (;;)
    {
      c = *q++;
      if (c == '}')  // found name
      {  C.format_ptr = q;
        *p = '\0';
        Ix ix = C.intern->action_map.lookup(format_name);
        if (ix)
        {
          return (*C.intern->action_map.value(ix))(C,args);
        }
        else
        {
          C.error("[CodeEmitter: undefined action '%s']\n", format_name);
        }
      } else if (c == '\0')
      {
        C.error("[CodeEmitter: missing closing brace in '%s']\n",
                C.format_ptr);
      }
      else
      {
        *p++ = c;
      }
    }
  }
  else if (C.abbrev_table[c])
  {
    return (*C.abbrev_table[c])(C,args);
  }
  else
  {
    C.error("[CodeEmitter: undefined format character: '%c']\n", c);
  }
  return args;
}

//////////////////////////////////////////////////////////////////////////////
//
//  The default meta character handlers
//
//////////////////////////////////////////////////////////////////////////////

va_list CodeEmitter::do_char( CodeEmitter& C, va_list args)
{
  char c = va_arg(args,char);
  C.out->put(c);
  if (c == '\n')
  {
    C.line_number++;
    C.anchored = true;
  }
  else
  {
    C.anchored = false;
  }
  return args;
}

va_list CodeEmitter::do_uchar( CodeEmitter& C, va_list args)
{
  unsigned char c = va_arg(args,unsigned char);
  C.out->put(c);
  if (c == '\n')
  {
    C.line_number++;
    C.anchored = true;
  }
  else
  {
    C.anchored = false;
  }
  return args;
}

va_list CodeEmitter::do_short( CodeEmitter& C, va_list args)
{
  short i = va_arg(args,short);
  *C.out << i;
  C.anchored = false;
  return args;
}

va_list CodeEmitter::do_ushort( CodeEmitter& C, va_list args)
{
  unsigned short i = va_arg(args,unsigned short);
  *C.out << i;
  C.anchored = false;
  return args;
}

va_list CodeEmitter::do_int( CodeEmitter& C, va_list args)
{
  int i = va_arg(args,int);
  *C.out << i;
  C.anchored = false;
  return args;
}

va_list CodeEmitter::do_uint( CodeEmitter& C, va_list args)
{
  unsigned int i = va_arg(args,unsigned int);
  *C.out << i;
  C.anchored = false;
  return args;
}

va_list CodeEmitter::do_long( CodeEmitter& C, va_list args)
{
  long i = va_arg(args,long);
  *C.out << i;
  C.anchored = false;
  return args;
}

va_list CodeEmitter::do_ulong( CodeEmitter& C, va_list args)
{
  unsigned long i = va_arg(args,unsigned long);
  *C.out << i;
  C.anchored = false;
  return args;
}

va_list CodeEmitter::do_float( CodeEmitter& C, va_list args)
{
  float r = va_arg(args,float);
  *C.out << r;
  C.anchored = false;
  return args;
}

va_list CodeEmitter::do_double( CodeEmitter& C, va_list args)
{
  double r = va_arg(args,double);
  *C.out << r;
  C.anchored = false;
  return args;
}

va_list CodeEmitter::do_string( CodeEmitter& C, va_list args)
{
  const char * s = va_arg(args,const char *);
  *C.out << s;
  C.anchored = false;
  return args;
}
