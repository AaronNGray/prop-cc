///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.8),
//  last updated on Sep 16, 2005.
//  The original source file is "..\..\prop-src\compiler.pcc".
///////////////////////////////////////////////////////////////////////////////

#line 1 "../../prop-src/compiler.pcc"
///////////////////////////////////////////////////////////////////////////////
//
//  The file implements the class Compiler and this is the main entry
//  point of the Prop -> C++ translator.
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "ir.h"
#include "ast.h"
#include "type.h"
#include "compiler.h"
#include "options.h"


///////////////////////////////////////////////////////////////////////////////
//
//  Constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

Compiler:: Compiler( TyOpt opt, int embedded_tags)
    : DatatypeCompiler( opt, embedded_tags) {}
Compiler::~Compiler() {}

///////////////////////////////////////////////////////////////////////////////
//
//  Emit header info
//
///////////////////////////////////////////////////////////////////////////////

void Compiler::emit_header( const char * text, int n)
{
  header.emit( text, n);
}

void Compiler::emit_header_text()
{
  const char * header_text = header.text();
  if (header_text)
    pr( "%s", header_text);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Additional printing method
//
///////////////////////////////////////////////////////////////////////////////

va_list Compiler::printer( char fmt, va_list arg)
{
  
#line 52 "../../prop-src/compiler.pcc"
#line 57 "../../prop-src/compiler.pcc"
{
  switch (fmt) {
    case '&': {
#line 55 "../../prop-src/compiler.pcc"
     gen( va_arg( arg, Decls)); 
#line 55 "../../prop-src/compiler.pcc"
    } break;
    case 'D': {
#line 56 "../../prop-src/compiler.pcc"
     gen( va_arg( arg, Decl)); 
#line 56 "../../prop-src/compiler.pcc"
    } break;
    case 'm': {
#line 54 "../../prop-src/compiler.pcc"
     MatchCompiler::gen( va_arg( arg, Match)); 
#line 54 "../../prop-src/compiler.pcc"
    } break;
    default: {
#line 57 "../../prop-src/compiler.pcc"
     bug( "undefined print format '%%%c'\n", (int)fmt); 
#line 57 "../../prop-src/compiler.pcc"
    }
  }
}
#line 58 "../../prop-src/compiler.pcc"
#line 58 "../../prop-src/compiler.pcc"

  return arg;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Top level code generation method
//
///////////////////////////////////////////////////////////////////////////////

void Compiler::generate(Decls ds)
{
  // generate the quark literals
  if ( quark_map.size() > 0)
  {
    pr(
        "%^%/"
        "%^//  Quark literals"
        "%^%/"
      );

    foreach_entry (e, quark_map)
    {
      Id name  = (Id) quark_map.key( e);
      Id quark = (Id) quark_map.value( e);
      pr ("%^static const Quark %s(%s);\n", quark, name);
    }
  }

  // now generate the main program.
  gen( ds);

  // finally, generate any outstanding rewriters
  gen_rewriters();

  // if the visualization is on then print GDL
  if (options.visualization)
    print_definitions_as_GDL();
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to generate a list of declarations.
//
///////////////////////////////////////////////////////////////////////////////

void Compiler::gen( Decls ds)
{
  Bool line_prefix = true;
  Bool line_suffix = true;
  
#line 108 "../../prop-src/compiler.pcc"
#line 120 "../../prop-src/compiler.pcc"
{
  for (;;) {
    if (ds) {
#line 111 "../../prop-src/compiler.pcc"
      
      
#line 112 "../../prop-src/compiler.pcc"
#line 115 "../../prop-src/compiler.pcc"
      {
        Decl _V1 = ds->_1;
        if (_V1) {
          switch (_V1->tag__) {
            case a_Decl::tag_TYPEEXPdecl: {
#line 114 "../../prop-src/compiler.pcc"
             line_suffix = line_prefix; line_prefix = false; 
#line 114 "../../prop-src/compiler.pcc"
              } break;
            default: {
              L2:; 
#line 115 "../../prop-src/compiler.pcc"
             line_suffix = line_prefix; line_prefix = true; 
#line 115 "../../prop-src/compiler.pcc"
              } break;
          }
        } else { goto L2; }
      }
#line 116 "../../prop-src/compiler.pcc"
#line 116 "../../prop-src/compiler.pcc"
      
      
            gen( ds->_1, line_prefix, line_suffix);
            ds = ds->_2;
          
#line 120 "../../prop-src/compiler.pcc"
    } else { goto L1; }
  }
  L1:;
}
#line 121 "../../prop-src/compiler.pcc"
#line 121 "../../prop-src/compiler.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to generate one declaration.
//
///////////////////////////////////////////////////////////////////////////////

void Compiler::gen( Decl d, Bool line_prefix, Bool line_suffix)
{
  
#line 132 "../../prop-src/compiler.pcc"
#line 212 "../../prop-src/compiler.pcc"
{
  if (d) {
    switch (d->tag__) {
      case a_Decl::tag_OPAQUEdecl: {
#line 134 "../../prop-src/compiler.pcc"
       pr ("%C",_OPAQUEdecl(d)->OPAQUEdecl); 
#line 134 "../../prop-src/compiler.pcc"
        } break;
      case a_Decl::tag_DATATYPEdecl: {
#line 135 "../../prop-src/compiler.pcc"
       gen_datatype(_DATATYPEdecl(d)->_1,_DATATYPEdecl(d)->_2,_DATATYPEdecl(d)->_3,_DATATYPEdecl(d)->_4); 
#line 135 "../../prop-src/compiler.pcc"
        } break;
      case a_Decl::tag_INSTANTIATEdecl: {
#line 136 "../../prop-src/compiler.pcc"
       instantiate_datatypes(_INSTANTIATEdecl(d)->_1,_INSTANTIATEdecl(d)->_2);
#line 136 "../../prop-src/compiler.pcc"
        } break;
      case a_Decl::tag_CLASSDEFdecl: {
#line 150 "../../prop-src/compiler.pcc"
       _CLASSDEFdecl(d)->CLASSDEFdecl->gen_class_definition(*this); 
#line 150 "../../prop-src/compiler.pcc"
        } break;
      case a_Decl::tag_INFERENCEdecl: {
#line 143 "../../prop-src/compiler.pcc"
       gen_inference_rules(_INFERENCEdecl(d)->_1, _INFERENCEdecl(d)->_2); 
#line 143 "../../prop-src/compiler.pcc"
        } break;
      case a_Decl::tag_REWRITEdecl: {
#line 137 "../../prop-src/compiler.pcc"
       gen_rewrite(_REWRITEdecl(d)->_1, _REWRITEdecl(d)->_2, _REWRITEdecl(d)->_3); 
#line 137 "../../prop-src/compiler.pcc"
        } break;
      case a_Decl::tag_REWRITINGdecl: {
#line 138 "../../prop-src/compiler.pcc"
       gen_rewriting(_REWRITINGdecl(d)->_1,_REWRITINGdecl(d)->_2,_REWRITINGdecl(d)->_3,_REWRITINGdecl(d)->_4,_REWRITINGdecl(d)->_5,_REWRITINGdecl(d)->_6); 
#line 138 "../../prop-src/compiler.pcc"
        } break;
      case a_Decl::tag_REPLACEMENTdecl: {
#line 147 "../../prop-src/compiler.pcc"
       gen_replacement(_REPLACEMENTdecl(d)->_1,_REPLACEMENTdecl(d)->_2); 
#line 147 "../../prop-src/compiler.pcc"
        } break;
      case a_Decl::tag_CUTREWRITEdecl: {
#line 148 "../../prop-src/compiler.pcc"
       gen_cutreplacement(_CUTREWRITEdecl(d)->_1,_CUTREWRITEdecl(d)->_2); 
#line 148 "../../prop-src/compiler.pcc"
        } break;
      case a_Decl::tag_FAILREWRITEdecl: {
#line 149 "../../prop-src/compiler.pcc"
       gen_failrewrite(_FAILREWRITEdecl(d)->FAILREWRITEdecl); 
#line 149 "../../prop-src/compiler.pcc"
        } break;
      case a_Decl::tag_INJECTdecl: {
        if (_INJECTdecl(d)->direction) {
          
#line 184 "../../prop-src/compiler.pcc"
          
          pr( " if (i__) insert_alpha(%i,fact__); else remove_alpha(%i,fact__); ",
              _INJECTdecl(d)->node_number, _INJECTdecl(d)->node_number);
          
#line 187 "../../prop-src/compiler.pcc"
        } else {
          
#line 189 "../../prop-src/compiler.pcc"
          
          pr( " if (i__) insert_beta(%i,f__); else remove_beta(%i,f__); ",
              _INJECTdecl(d)->node_number, _INJECTdecl(d)->node_number);
          
#line 192 "../../prop-src/compiler.pcc"
        }
        } break;
      case a_Decl::tag_GOTOdecl: {
#line 181 "../../prop-src/compiler.pcc"
       pr ("%^goto %s;\n", _GOTOdecl(d)->GOTOdecl); 
#line 181 "../../prop-src/compiler.pcc"
        } break;
      case a_Decl::tag_SETSTATEdecl: {
#line 182 "../../prop-src/compiler.pcc"
       pr ("s__ = %i;", _SETSTATEdecl(d)->SETSTATEdecl); 
#line 182 "../../prop-src/compiler.pcc"
        } break;
      case a_Decl::tag_SYNTAXdecl: {
#line 141 "../../prop-src/compiler.pcc"
       gen_parser(_SYNTAXdecl(d)->_1,_SYNTAXdecl(d)->_2); 
#line 141 "../../prop-src/compiler.pcc"
        } break;
      case a_Decl::tag_ATTRIBUTEGRAMMARdecl: {
#line 142 "../../prop-src/compiler.pcc"
       gen_attribute_grammar(_ATTRIBUTEGRAMMARdecl(d)->_1,_ATTRIBUTEGRAMMARdecl(d)->_2); 
#line 142 "../../prop-src/compiler.pcc"
        } break;
      case a_Decl::tag_FUNdecl: {
#line 139 "../../prop-src/compiler.pcc"
       gen_fun_def(_FUNdecl(d)->FUNdecl); 
#line 139 "../../prop-src/compiler.pcc"
        } break;
      case a_Decl::tag_MATCHdecl: {
#line 140 "../../prop-src/compiler.pcc"
       gen_match_stmt(_MATCHdecl(d)->_1,_MATCHdecl(d)->_2,_MATCHdecl(d)->_3,_MATCHdecl(d)->_4); 
#line 140 "../../prop-src/compiler.pcc"
        } break;
      case a_Decl::tag_SETLSTMTdecl: {
#line 144 "../../prop-src/compiler.pcc"
       gen_setl(_SETLSTMTdecl(d)->SETLSTMTdecl); 
#line 144 "../../prop-src/compiler.pcc"
        } break;
      case a_Decl::tag_SETLDEFdecl: {
#line 145 "../../prop-src/compiler.pcc"
       gen_setl(_SETLDEFdecl(d)->SETLDEFdecl); 
#line 145 "../../prop-src/compiler.pcc"
        } break;
      case a_Decl::tag_CLASSOFdecl: {
#line 152 "../../prop-src/compiler.pcc"
        
        
#line 153 "../../prop-src/compiler.pcc"
#line 177 "../../prop-src/compiler.pcc"
        {
          Ty _V2 = lookup_ty(_CLASSOFdecl(d)->CLASSOFdecl);
          if (_V2) {
            switch (_V2->tag__) {
              case a_Ty::tag_TYCONty: {
                if (boxed(_TYCONty(_V2)->_1)) {
                  switch (_TYCONty(_V2)->_1->tag__) {
                    case a_TyCon::tag_DATATYPEtycon: {
#line 156 "../../prop-src/compiler.pcc"
                     pr( "a_%s", _DATATYPEtycon(_TYCONty(_V2)->_1)->id); 
#line 156 "../../prop-src/compiler.pcc"
                      } break;
                    default: {
                      L3:; 
#line 177 "../../prop-src/compiler.pcc"
                    error ("%Ltype %s has unknown class: %T\n",_CLASSOFdecl(d)->CLASSOFdecl, _V2); 
#line 177 "../../prop-src/compiler.pcc"
                      } break;
                  }
                } else { goto L3; }
                } break;
              default: { goto L3; } break;
            }
          } else {
#line 158 "../../prop-src/compiler.pcc"
            
            
#line 159 "../../prop-src/compiler.pcc"
#line 173 "../../prop-src/compiler.pcc"
            {
              Cons _V3 = find_cons(_CLASSOFdecl(d)->CLASSOFdecl);
              if (_V3) {
                if (
#line 163 "../../prop-src/compiler.pcc"
                (_V3->opt & OPTunboxed)
#line 163 "../../prop-src/compiler.pcc"
) {
                  
                  if (_V3->ty) {
#line 164 "../../prop-src/compiler.pcc"
                  error ("%Lthe class representation of constructor %s has been elided\n", _CLASSOFdecl(d)->CLASSOFdecl); 
#line 164 "../../prop-src/compiler.pcc"
                  } else {
                    L4:; 
#line 162 "../../prop-src/compiler.pcc"
                  error ("%Lconstructor %s is not a class\n", _CLASSOFdecl(d)->CLASSOFdecl); 
#line 162 "../../prop-src/compiler.pcc"
                  }
                } else {
                  
                  if (_V3->alg_ty) {
                    switch (_V3->alg_ty->tag__) {
                      case a_Ty::tag_TYCONty: {
                        if (_V3->ty) {
                          if (boxed(_TYCONty(_V3->alg_ty)->_1)) {
                            switch (_TYCONty(_V3->alg_ty)->_1->tag__) {
                              case a_TyCon::tag_DATATYPEtycon: {
                                L5:; 
#line 166 "../../prop-src/compiler.pcc"
                                
                                if (_DATATYPEtycon(_TYCONty(_V3->alg_ty)->_1)->opt & OPTsubclassless)
                                  pr ("a_%s", _DATATYPEtycon(_TYCONty(_V3->alg_ty)->_1)->id);
                                else
                                  pr ("%s_%S", _DATATYPEtycon(_TYCONty(_V3->alg_ty)->_1)->id, _V3->name);
                                
#line 171 "../../prop-src/compiler.pcc"
                                } break;
                              default: {
                                L6:; 
#line 173 "../../prop-src/compiler.pcc"
                              error ("%Ltype or constructor %s is undefined\n", _CLASSOFdecl(d)->CLASSOFdecl); 
#line 173 "../../prop-src/compiler.pcc"
                                } break;
                            }
                          } else { goto L6; }
                        } else { goto L4; }
                        } break;
                      default: {
                        L7:; 
                        if (_V3->ty) { goto L6; } else { goto L4; }
                        } break;
                    }
                  } else { goto L7; }
                }
              } else { goto L6; }
            }
#line 174 "../../prop-src/compiler.pcc"
#line 174 "../../prop-src/compiler.pcc"
            
            
#line 175 "../../prop-src/compiler.pcc"
          }
        }
#line 178 "../../prop-src/compiler.pcc"
#line 178 "../../prop-src/compiler.pcc"
        
        
#line 179 "../../prop-src/compiler.pcc"
        } break;
      case a_Decl::tag_TYPEEXPdecl: {
#line 180 "../../prop-src/compiler.pcc"
       pr ("%t", _TYPEEXPdecl(d)->TYPEEXPdecl,""); 
#line 180 "../../prop-src/compiler.pcc"
        } break;
      case a_Decl::tag_EXPdecl: {
        if (_EXPdecl(d)->exp) {
          switch (_EXPdecl(d)->exp->tag__) {
            case a_Exp::tag_THISSYNexp:
            case a_Exp::tag_SYNexp: {
#line 198 "../../prop-src/compiler.pcc"
             pr( "%e", _EXPdecl(d)->exp); 
#line 198 "../../prop-src/compiler.pcc"
              } break;
            default: {
              L8:; 
#line 200 "../../prop-src/compiler.pcc"
             pr( "%^%s%e%s", (_EXPdecl(d)->prefix ? _EXPdecl(d)->prefix : ""),_EXPdecl(d)->exp, (_EXPdecl(d)->suffix ? _EXPdecl(d)->suffix : "")); 
#line 200 "../../prop-src/compiler.pcc"
              } break;
          }
        } else { goto L8; }
        } break;
      case a_Decl::tag_MARKEDdecl: {
#line 202 "../../prop-src/compiler.pcc"
        
        line = _MARKEDdecl(d)->_1.begin_line;
        file = _MARKEDdecl(d)->_1.file_name;
        if (line_prefix)
          pr ("%#",line,file);
        gen(_MARKEDdecl(d)->_2);
        line = _MARKEDdecl(d)->_1.end_line;
        if (line_suffix)
          pr ("%#",line,file);
        
#line 211 "../../prop-src/compiler.pcc"
        } break;
      default: {
#line 212 "../../prop-src/compiler.pcc"
       bug("Unimplemented feature"); 
#line 212 "../../prop-src/compiler.pcc"
        } break;
    }
  } else {
#line 133 "../../prop-src/compiler.pcc"
   /* skip */ 
#line 133 "../../prop-src/compiler.pcc"
  }
}
#line 213 "../../prop-src/compiler.pcc"
#line 213 "../../prop-src/compiler.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to generate a report.
//
///////////////////////////////////////////////////////////////////////////////

std::ostream& Compiler::print_report(std::ostream& f)
{
  f << "------------------------------- Statistics -------------------------------"
    << "\nMerge matching rules         = " << (options.merge_match ?  "yes" : "no")
    << "\nNumber of DFA nodes merged   = " << merges
    << "\nNumber of ifs generated      = " << ifs
    << "\nNumber of switches generated = " << switches
    << "\nNumber of labels             = " << goto_labels
    << "\nNumber of gotos              = " << gotos
    << "\nAdaptive matching            = " << (options.adaptive_matching ? "enabled" : "disabled")
    << "\nFast string matching         = " << (options.fast_string_match ? "enabled" : "disabled")
    << "\nInline downcasts             = " << (options.inline_casts ? "enabled" : "disabled")
    << "\n"
       "--------------------------------------------------------------------------"
       "\n"
       ;
  return f;
}
#line 240 "../../prop-src/compiler.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 398
Number of ifs generated      = 14
Number of switches generated = 8
Number of labels             = 7
Number of gotos              = 10
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
