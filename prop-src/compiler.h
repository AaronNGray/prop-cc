///////////////////////////////////////////////////////////////////////////////
//
//  This file describes the interface to the Prop compiler.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef prop_compiler_h
#define prop_compiler_h

#include "matchcom.h"   // pattern matching compiler
#include "rwgen.h"      // rewriting compiler
#include "datagen.h"    // data structure compiler
#include "infgen.h"     // inference compiler
#include "parsegen.h"   // parser generator
#include "setlgen.h"    // set language compiler
// #include "bitfield.h"   // bit fields/pattern compiler
// #include "dataflow.h"   // dataflow compiler
// #include "constraint.h" // constraint compiler
#include "metasyntax.h" // metasyntax compiler
#include "grsgen.h"     // graph rewriting compiler
#include "aggen.h"      // attribute grammar compiler
#include "rwmix.h"      // TRS partial evaluator
#include "textbuf.h"

///////////////////////////////////////////////////////////////////////////////
//  The compiler is constructed by combining various modules together.
///////////////////////////////////////////////////////////////////////////////
class Compiler 
  : virtual public CodeGen,            // code generator
    virtual public DatatypeCompiler,   // datatype compiler
    virtual public MatchCompiler,      // pattern matching compiler
    virtual public RewritingCompiler,  // rewriting compiler
    virtual public RewriteMix,         // rewriting system partial evaluator
    virtual public InferenceCompiler,  // inference compiler
    virtual public ParserCompiler,     // parser compiler
    virtual public SETLCompiler,       // setl compiler
//    virtual public BitfieldCompiler,   // bit field compiler
//    virtual public DataflowCompiler,   // dataflow compiler
//    virtual public ConstraintCompiler, // constraint compiler
    virtual public MetaSyntaxCompiler,       // meta syntax compiler
    virtual public AttributeGrammarCompiler, // AG compiler
    virtual public GraphRewritingCompiler    // grs compiler
{
   Compiler (const Compiler&);        // no copy constructor
   void operator = (const Compiler&); // no assignment

   TextBuffer header; // header information

public:
   ////////////////////////////////////////////////////////////////////////////
   //  Constructor and destructor
   ////////////////////////////////////////////////////////////////////////////
            Compiler(TyOpt opt, int embedded_tags);
   virtual ~Compiler();

public:

   ////////////////////////////////////////////////////////////////////////////
   //  Methods to generate a Prop declaration.
   ////////////////////////////////////////////////////////////////////////////
   void     generate     (Decls);     // generate code
   void     emit_header  (const char *, int);
   void     emit_header_text ();
   std::ostream& print_report (std::ostream&);      // print report
   void     print_definitions_as_GDL ();  // print definitions as GDL

protected:
   ////////////////////////////////////////////////////////////////////////////
   //  Miscellaneous methods
   ////////////////////////////////////////////////////////////////////////////
   void            gen     (Decl, Bool = true, Bool = true);
   void            gen     (Decls);
   virtual va_list printer (char, va_list);
};

#endif
