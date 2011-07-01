///////////////////////////////////////////////////////////////////////////////
//
//      ////////
//     //     //   //////   /////   ///////
//    ////////   //       //   //  //    //
//   //         //       //   //  ///////
//  //         //        /////   //
//                              //      Version 2.3.x
//
//                                      Allen Leung (leunga@cs.nyu.edu)
///////////////////////////////////////////////////////////////////////////////
//
//  This is the driver routine for the translator
//
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "config.h"
#include "compiler.h"
#include "type.h"
#include "author.h"
#include "options.h"


///////////////////////////////////////////////////////////////////////////////
//
//  Various global data.
//
///////////////////////////////////////////////////////////////////////////////
int          errors                = 0;
int          warnings              = 0;
std::istream *    input_stream          = 0;
std::ostream *    output_stream         = 0;
std::ostream *    log_stream            = 0;
Compiler *   error_log             = 0;
Decls        program               = 0;

///////////////////////////////////////////////////////////////////////////////
//
//  Memory pool and string pool
//
///////////////////////////////////////////////////////////////////////////////
MemPool    mem_pool(4096);     // 4K page size
MemPool    global_pool(4096);  // 4K page size
MemPool *  current_pool = &mem_pool;
StringPool str_pool(4096);     // 4K page size
static int globals = 0;

void   MEM::use_global_pools()
{
  current_pool = &global_pool;
  globals++;
}

void   MEM::use_local_pools()
{
  if (--globals == 0)
    current_pool = &mem_pool;
}

void * MEM::operator new( size_t n)
{
  return (*current_pool)[n];
}

///////////////////////////////////////////////////////////////////////////////
//
//  Current source location variables.
//
///////////////////////////////////////////////////////////////////////////////

int          line, first_line;
const char * file;

///////////////////////////////////////////////////////////////////////////////
//
//  Source location methods
//
///////////////////////////////////////////////////////////////////////////////

Loc::Loc()
{
  begin_line = first_line;
  end_line = line;
  file_name = file;
  first_line = line;
}

Loc::Loc( int a, int b)
{
  begin_line = a;
  end_line = b;
  file_name = file;
  first_line = line;
}

void Loc::set_loc() const
{
  line = begin_line;
  file = file_name;
}

const char * my_strrchr( const char * s, char c)
{
  register const char * p;
  for (p = s + strlen(s) - 1; p != s; p--)
    if (*p == c)
      return p;
  return 0;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Compute the output file name from the input file name
//
///////////////////////////////////////////////////////////////////////////////

void PropOptions::compute_output_file_name()
{  // Locate the . in the file name and
  // Cut out the directory prefix.
  const char * dot   = my_strrchr(input_file_name,'.');
  const char * slash = my_strrchr(input_file_name,PATH_SEPARATOR);
  if (dot == 0 || ! (dot[1] == 'p' || dot[1] == 'P'))
  {
    std::cerr << '"' << input_file_name
    << "\" is not a valid source file name.  "
    "It must be of the form \"*.p*\".\n";
    exit(1);
  }
  if (slash == 0)
    slash = input_file_name-1;
  memcpy(file_prefix, slash+1, dot - slash);
  file_prefix[dot - slash] = '\0';
  if (output_file_name[0] == '\0')
  {
    strcpy(output_file_name,file_prefix);
    strcat(output_file_name, dot+2);
  }
  encode_string(mangled_file_prefix,file_prefix);
  encode_string(mangled_file_name,output_file_name);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Function to emit the proper headers
//
///////////////////////////////////////////////////////////////////////////////

static void emit_headers( Compiler& C)
{
  C.pr
  ("%^%/"
   "%^//  This file is generated automatically using Prop (version %s.%s),"
   "%^//  last updated on %s."
   "%^//  The original source file is \"%s\"."
   "%^%/\n",
   VERSION, PATCH_LEVEL, LAST_UPDATED, options.input_file_name
  );

  C.emit_header_text();

  /////////////////////////////////////////////////////////////////////////
  //  Emit headers
  /////////////////////////////////////////////////////////////////////////
  Bool inc = false;
  if (Used::rewriting)
  {
    C.pr ("#define PROP_REWRITING_USED\n");
    inc = true;
  }
  if (Used::infer)
  {
    C.pr ("#define PROP_INFERENCE_USED\n");
    inc = true;
  }
  if (Used::gc)
  {
    C.pr ("#define PROP_GARBAGE_COLLECTION_USED\n");
    inc = true;
  }
  if (Used::refcount)
  {
    C.pr ("#define PROP_REFCOUNT_USED\n");
    inc = true;
  }
  if (Used::printer)
  {
    C.pr ("#define PROP_PRINTER_USED\n");
    inc = true;
  }
  if (Used::persistence)
  {
    C.pr ("#define PROP_PERSISTENCE_USED\n");
    inc = true;
  }
  if (Used::objc)
  {
    C.pr ("#define PROP_OBJC_USED\n");
    inc = true;
  }
  if (Used::regexp)
  {
    C.pr ("#define PROP_REGEXP_MATCHING_USED\n");
    inc = true;
  }
  if (Used::string_match)
  {
    C.pr ("#define PROP_STRCMP_USED\n");
    inc = true;
  }
  if (Used::equality)
  {
    C.pr ("#define PROP_EQUALITY_USED\n");
    inc = true;
  }
  if (Used::unification)
  {
    C.pr ("#define PROP_UNIFICATION_USED\n");
    inc = true;
  }
  if (Used::vector)
  {
    C.pr ("#define PROP_VECTOR_USED\n");
    inc = true;
  }
  if (Used::parser)
  {
    C.pr ("#define PROP_PARSER_USED\n");
    inc = true;
  }
  if (Used::quark)
  {
    C.pr ("#define PROP_QUARK_USED\n");
    inc = true;
  }
  if (Used::bigint)
  {
    C.pr ("#define PROP_BIGINT_USED\n");
    inc = true;
  }
  if (Used::graph_type)
  {
    C.pr ("#define PROP_GRAPHTYPE_USED\n");
    inc = true;
  }
  if (options.trace)
  {
    C.pr ("#define PROP_TRACE_ON\n");
    inc = true;
  }
  for (int i = 2; i < MAX_TUPLE_ARITY; i++)
  {
    if (Used::tuple[i])
    {
      C.pr("#define PROP_TUPLE%i_USED\n", i);
      inc = true;
    }
  }
  if (inc)
    C.pr ("#include <propdefs.h>\n");
}

///////////////////////////////////////////////////////////////////////////////
//
//  The main program.
//
///////////////////////////////////////////////////////////////////////////////

int process_input( PropOptions& options)
{
  ////////////////////////////////////////////////////////////////////////////
  //  Open input file
  ////////////////////////////////////////////////////////////////////////////
  {  input_stream = new std::ifstream(options.input_file_name);
    if (! *input_stream)
    {
      perror(options.input_file_name);
      return 1;
    }
  }

  ////////////////////////////////////////////////////////////////////////////
  //  The compiler
  ////////////////////////////////////////////////////////////////////////////
  Compiler C(options.tagged_pointer ? OPTtaggedpointer : OPTnone,
             options.max_embedded_tags);

  ////////////////////////////////////////////////////////////////////////////
  //  Parse input
  ////////////////////////////////////////////////////////////////////////////
  initialize_types();
  {
    extern void front_end(const char *, Compiler&);
    front_end(options.input_file_name,C);
  }

  ////////////////////////////////////////////////////////////////////////////
  //  Open output file
  ////////////////////////////////////////////////////////////////////////////
  if (errors > 0)
    options.emit_code = false;

  ////////////////////////////////////////////////////////////////////////////
  //  Setup output file
  ////////////////////////////////////////////////////////////////////////////
  Bool clean_up_file = false;
  if (! options.gen_dependences)
  {
    if (options.to_stdout)
    {
      output_stream = &std::cout;
    }
    else
    {
      output_stream = options.emit_code ?
                      (new std::ofstream(options.output_file_name)) : (new std::ofstream);
      if (! (*output_stream))
      {
        perror(options.output_file_name);
        return 1;
      }
      clean_up_file = true;
    }
    C.set_stream(*output_stream);

    /////////////////////////////////////////////////////////////////////////
    //  Emit the headers.
    /////////////////////////////////////////////////////////////////////////
    emit_headers(C);

    /////////////////////////////////////////////////////////////////////////
    //  Compile.
    /////////////////////////////////////////////////////////////////////////
    C.generate(program);
    C.pr("/*\n");
    C.print_report(*output_stream);
    C.pr("*/\n");

    /////////////////////////////////////////////////////////////////////////
    //  Cleanup
    /////////////////////////////////////////////////////////////////////////
    if (clean_up_file)
      delete output_stream;
    if (errors > 0 && options.emit_code && options.output_file_name[0])
      remove
        (options.output_file_name);
  }

  ////////////////////////////////////////////////////////////////////////////
  //  Postprocessing
  ////////////////////////////////////////////////////////////////////////////
  if (errors > 0)
    return 1;
  if (options.gen_dependences)
    IncludeDependency::print_dependences();
  else
    std::cerr << options.output_file_name << '\n';
  return 0;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Print messages on the console
//
///////////////////////////////////////////////////////////////////////////////

std::ostream& pr_msg( const char * fmt, va_list arg)
{
  if (error_log == 0)
    error_log = new Compiler(0,0);
  return error_log->outv(fmt,arg).flush();
}

///////////////////////////////////////////////////////////////////////////////
//
//  Print messages
//
///////////////////////////////////////////////////////////////////////////////

std::ostream& msg( const char * fmt, ...)
{
  va_list arg;
  va_start(arg,fmt);
  std::ostream& f = pr_msg(fmt,arg);
  va_end(arg);
  return f;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Print debugging messages
//
///////////////////////////////////////////////////////////////////////////////

std::ostream& debug_msg( const char * fmt, ...)
{
  va_list arg;
  va_start(arg,fmt);
  if (options.debug)
    pr_msg(fmt,arg);
  va_end(arg);
  return std::cerr;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Print error message
//
///////////////////////////////////////////////////////////////////////////////

std::ostream& error( const char * fmt, ...)
{
  va_list arg;
  va_start(arg,fmt);
  std::ostream& f = pr_msg(fmt,arg);
  errors++;
  va_end(arg);
  return f;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Print bug message
//
///////////////////////////////////////////////////////////////////////////////

void bug( const char * fmt, ...)
{
  va_list arg;
  va_start(arg,fmt);
  msg("%Lbug: ");
  pr_msg(fmt,arg);
  va_end(arg);
  std::cerr << "\nPlease send bug report to " << EMAIL << '\n';
  exit (1);
}

//////////////////////////////////////////////////////////////////////////////
//
//  Routine to open a file for reading, using the search path as
//  starting point.  Returns NIL if none can be found.
//
//////////////////////////////////////////////////////////////////////////////

std::istream * PropOptions::open_input_file( const char file_name[])
{
  register const char * p;
  register char * q;

  for (p = search_paths; *p != '\0' && *p != FILE_SEPARATOR; p++)
  {
    for (q = current_file_path; *p != '\0' && *p != FILE_SEPARATOR; )
      *q++ = *p++;
    *q++ = PATH_SEPARATOR;
    *q = '\0';
    strcat(current_file_path,file_name);
    debug_msg("[Opening file %s]\n",current_file_path);
    std::ifstream * f = new std::ifstream(current_file_path);
    if (*f)
      return f;
    delete f;
  }
  return 0;
}

//////////////////////////////////////////////////////////////////////////////
//
//  Routine to open a file for write and returns the handle
//
//////////////////////////////////////////////////////////////////////////////

std::ostream * open_output_file( const char file_name[])
{
  std::ofstream * F = new std::ofstream(file_name);
  if (! *F)
  {
    perror(file_name);
    exit(1);
  }
  return F;
}

//////////////////////////////////////////////////////////////////////////////
//
//  Routine to open a log file and returns the handle.
//
//////////////////////////////////////////////////////////////////////////////

std::ostream& open_logfile()
{
  if (log_stream)
    return *log_stream;
  if (! options.generate_report)
  {
    log_stream = new std::ofstream;
    return *log_stream;
  }
  else
  {
    char log_file_name[256];
    strcpy(log_file_name,options.file_prefix);
    strcat(log_file_name,"report");
    log_stream = open_output_file(log_file_name);
    return *log_stream;
  }
}
