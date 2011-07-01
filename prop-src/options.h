///////////////////////////////////////////////////////////////////////////////
//
//  This file describes the options selected during translation.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef prop_options_h
#define prop_options_h

#include <iostream>
#include <AD/generic/generic.h>



///////////////////////////////////////////////////////////////////////////////
//
//  Include file dependency
//
///////////////////////////////////////////////////////////////////////////////

struct IncludeDependency
{
  const char *        file_name;
  IncludeDependency * next;
  inline IncludeDependency(const char * f, IncludeDependency * n)
      : file_name(f), next(n)
  {}
  static IncludeDependency * dependences;
  static void add_dependency (const char *);
  static void print_dependences ();
};

///////////////////////////////////////////////////////////////////////////////
//
//  Options are described by the following structure.
//
///////////////////////////////////////////////////////////////////////////////

class PropOptions
{
  PropOptions(const PropOptions&);
  void operator = (const PropOptions&);
public:
  Bool debug,                  // Turn on debugging
       emit_code,              // Emit code
       strict_checking,        // Be strict in semantic checking
       line_directives,        // Generate line directives in output
       trace,                  // Generate tracing code in output
       nonlinear_patterns,     // Allow nonlinear patterns
       merge_match,            // Use merging in patterns
       generate_report,        // Generate report
       burs,                   // Use the BURS algorithm
       fast_string_match,      // Use fast string matching algorithm
       adaptive_matching,      // Use adaptive pattern matching
       inline_casts,           // Generate inline casts
       save_space,             // Use space saving scheme
       tagged_pointer,         // Use tagged pointer scheme
       GNU_style_message,      // Use GNU style error messages
       new_type_format,        // Use new type format
       gen_dependences,        // Generate #include file dependences
       new_list_format,        // Generate new list code
       visualization,          // Generate VCG output
       generate_html,          // Generate html output
       optimize_rewrite;       // Optimize rewriting
  int  max_vector_len,         // The maximum length of vector literals
       verbosity;              // Verbosity level
  int optimization_level;        // Optimization level
  int max_embedded_tags;         // Maximum number of embedded pointer tags
  const char * prog_name;        // name of prop
  char output_file_name[256];    // name of output file
  char search_paths[1024];       // search paths
  const char * input_file_name;  // name of input file
  int file_count;                // number of input files
  const char * input_files[512]; // name of input files
  int option_count;              // number of options
  const char * input_options[64];// options
  char file_prefix[256];         // prefix of file name
  char mangled_file_prefix[256]; // encoded for program use
  char mangled_file_name[256];   // encoded for program use
  char current_file_path[1024];  // file path of current input file
  Bool to_stdout;                // send output to stdout
  Bool automake;                 // automatically recompile changed files

  PropOptions();
  ~PropOptions();
  void process_command_line_arguments(int argc, const char * argv[]);
  void compute_output_file_name();
  std::istream * open_input_file(const char file_name[]);
};

extern PropOptions options;

///////////////////////////////////////////////////////////////////////////////
//
//  Features used are described by the following structure.  We generate
//  code so that only the features actually used are emitted.  We'll keep
//  track of which features are actually used in this structure.
//
///////////////////////////////////////////////////////////////////////////////

struct Used
{
  static Bool rewriting,         // Rewriting feature is used
              infer,             // Inference feature is used
              gc,                // Garbage collection is used
              regexp,            // Regular expressions are used
              string_match,      // String matching is used
              printer,           // Pretty printer is used
              refcount,          // Reference counting is used
              persistence,       // Persistence is used
              objc,              // Objective-C is used
              equality,          // Equality is used
              unification,       // Unification is used
              vector,            // Vector is used
              parser,            // Parser is generated
              quark,             // Quark literals are used
              bigint,            // Big integer literals are used
              graph_type,        // graph types are used
              * tuple;           // Tuples are used
};

#endif
