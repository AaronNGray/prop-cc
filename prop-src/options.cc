///////////////////////////////////////////////////////////////////////////////
//
//  This file implements the options selected during translation.
//
///////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include <iostream>
#include "basics.h"
#include "config.h"
#include "options.h"


///////////////////////////////////////////////////////////////////////////////
//
//  Default setting of the prop options
//
///////////////////////////////////////////////////////////////////////////////

PropOptions::PropOptions()
{
  debug               = false;
  emit_code           = true;
  strict_checking     = false;
  line_directives     = true;
  trace               = false;
  nonlinear_patterns  = false;
  merge_match         = true;
  generate_report     = false;
  burs                = false;
  fast_string_match   = false;
  adaptive_matching   = false;
  inline_casts        = false;
  save_space          = false;
  tagged_pointer      = false;
  GNU_style_message   = false;
  new_type_format     = true;
  gen_dependences     = false;
  new_list_format     = false;
  max_vector_len      = MAX_VECTOR_LEN;
  verbosity           = 0;
  optimization_level  = 0;
  max_embedded_tags   = 4;
  input_file_name     = 0;
  to_stdout           = false;
  file_count          = 0;
  automake            = false;
  option_count        = 0;
  visualization       = false;
  generate_html       = false;
  optimize_rewrite    = false;
  strcpy(search_paths,DEFAULT_SEARCH_PATH);
}
PropOptions::~PropOptions()
{}

///////////////////////////////////////////////////////////////////////////////
//
//  Features used are described by the following structure.  We generate
//  code so that only the features actually used are emitted.  We'll keep
//  track of which features are actually used in this structure.
//
///////////////////////////////////////////////////////////////////////////////

Bool Used::rewriting    = false;
Bool Used::infer        = false;
Bool Used::gc           = false;
Bool Used::regexp       = false;
Bool Used::string_match = false;
Bool Used::printer      = false;
Bool Used::refcount     = false;
Bool Used::persistence  = false;
Bool Used::objc         = false;
Bool Used::equality     = false;
Bool Used::unification  = false;
Bool Used::vector       = false;
Bool Used::parser       = false;
Bool Used::quark        = false;
Bool Used::bigint       = false;
Bool Used::graph_type   = false;
static Bool tuple_used[MAX_TUPLE_ARITY];
Bool * Used::tuple = tuple_used;

IncludeDependency * IncludeDependency::dependences = 0;

///////////////////////////////////////////////////////////////////////////////
//
//  Add a file to the dependency list
//
///////////////////////////////////////////////////////////////////////////////

void IncludeDependency::add_dependency( const char * file)
{
  dependences = new IncludeDependency( file, dependences);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Print the dependences
//
///////////////////////////////////////////////////////////////////////////////

void IncludeDependency::print_dependences ()
{
  std::cout << options.output_file_name << ":\t" << options.input_file_name << ' ';
  int len = strlen(options.output_file_name) + 10 + strlen(options.input_file_name);
  IncludeDependency * d;
  for (d = dependences; d; d = d->next)
  {
    const char * file_name = d->file_name;
    if (file_name[0] == '.' && file_name[1] == PATH_SEPARATOR)
      file_name += 2;
    int this_len = strlen(file_name);
    if (this_len + len >= 79)
    {
      len = 8;
      std::cout << "\\\n\t";
    }
    std::cout << file_name << ' ';
    len += this_len + 1;
  }
  std::cout << '\n';
}
