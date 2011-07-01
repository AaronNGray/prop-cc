///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.8),
//  last updated on Sep 16, 2005.
//  The original source file is "..\..\prop-src\trs3.pcc".
///////////////////////////////////////////////////////////////////////////////

#define PROP_TUPLE2_USED
#include <propdefs.h>
#line 1 "../../prop-src/trs3.pcc"
///////////////////////////////////////////////////////////////////////////////
//
//  These are the routines for code generation after partial evaluation
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "trs.h"
#include "ir.h"
#include "ast.h"
#include "type.h"
#include "list.h"
#include "rwgen.h"


///////////////////////////////////////////////////////////////////////////////
//
//  Method to clear statistics
//
///////////////////////////////////////////////////////////////////////////////

void TRS::clear_statistics()
{
  number_of_specializations = 0;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to print statistics
//
///////////////////////////////////////////////////////////////////////////////

void TRS::print_report( std::ostream& log) const
{
  print(log);

  log << "Number of specializations = " << number_of_specializations
      << "\n\nSpecializations follow:\n\n";

  print_specializations(log);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to print the specializations
//
///////////////////////////////////////////////////////////////////////////////

void TRS::print_specializations( std::ostream& log) const
{
  for (Rule r = 0; r < number_of_rules; r++)
  {
    MatchRule rule = rule_map[r];

    for (int i = 0; i < num_var_map[r]; i++)
    {
      if (residue_map[r][i] == 
#line 57 "../../prop-src/trs3.pcc"
#line 57 "../../prop-src/trs3.pcc"
nil_1_
#line 57 "../../prop-src/trs3.pcc"
#line 57 "../../prop-src/trs3.pcc"
)
        continue;
      for_each (Residue, res, residue_map[r][i])
	  {
	    log << "line " << rule->begin_line << ": " << rule << ' ';
	    print(log,rhs_map[r]); log << '\n';
	    log << "\twhen " << var_pat_map[r][i] << " is in state:\n";
	    treeauto.print_state(log,res._1);
	    log << "\toptimize rhs to ";
	    print(log,res._2);
	    log << "\n\n";
	  }
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to generate residue
//
///////////////////////////////////////////////////////////////////////////////

void TRS::generate_residue( Rule rule, int arity, State state, Term rhs)
{
  number_of_specializations++;
  // print_residue(rule,rhs);
  residue_map[rule][arity] = 
#line 83 "../../prop-src/trs3.pcc"
#line 83 "../../prop-src/trs3.pcc"
list_1_(mkTuple2(state,rhs),residue_map[rule][arity])
#line 83 "../../prop-src/trs3.pcc"
#line 83 "../../prop-src/trs3.pcc"
;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to translate a term into code
//
///////////////////////////////////////////////////////////////////////////////

Exp TRS::make_exp(Term term) const
{
  
#line 94 "../../prop-src/trs3.pcc"
#line 117 "../../prop-src/trs3.pcc"
{
  switch (term->tag__) {
    case a_Term::tag_CONSterm: {
      if (_CONSterm(term)->_2) {
        switch (_CONSterm(term)->_3) {
          case 0: {
#line 97 "../../prop-src/trs3.pcc"
           return CONSexp(_CONSterm(term)->_2,
#line 97 "../../prop-src/trs3.pcc"
#line 97 "../../prop-src/trs3.pcc"
            nil_1_
#line 97 "../../prop-src/trs3.pcc"
#line 97 "../../prop-src/trs3.pcc"
            ,NOexp); 
#line 97 "../../prop-src/trs3.pcc"
          } break;
          case 1: {
#line 98 "../../prop-src/trs3.pcc"
           return CONSexp(_CONSterm(term)->_2,
#line 98 "../../prop-src/trs3.pcc"
#line 98 "../../prop-src/trs3.pcc"
            nil_1_
#line 98 "../../prop-src/trs3.pcc"
#line 98 "../../prop-src/trs3.pcc"
            ,make_exp(_CONSterm(term)->_4[0])); 
#line 98 "../../prop-src/trs3.pcc"
          } break;
          case 2: {
            if (
#line 99 "../../prop-src/trs3.pcc"
            is_list_constructor(_CONSterm(term)->_2)
#line 99 "../../prop-src/trs3.pcc"
) {
              
#line 100 "../../prop-src/trs3.pcc"
              
              Exps heads = 
#line 101 "../../prop-src/trs3.pcc"
#line 101 "../../prop-src/trs3.pcc"
              nil_1_
#line 101 "../../prop-src/trs3.pcc"
#line 101 "../../prop-src/trs3.pcc"
              ;
              	  Term t = term;
              	  
#line 103 "../../prop-src/trs3.pcc"
#line 110 "../../prop-src/trs3.pcc"
              {
                for (;;) {
                  switch (t->tag__) {
                    case a_Term::tag_CONSterm: {
                      switch (_CONSterm(t)->_3) {
                        case 0: {
                          if (
#line 107 "../../prop-src/trs3.pcc"
                          is_list_constructor(_CONSterm(t)->_2)
#line 107 "../../prop-src/trs3.pcc"
) {
                            
#line 108 "../../prop-src/trs3.pcc"
                           return LISTexp(_CONSterm(term)->_2,_CONSterm(t)->_2,rev(heads),NOexp); 
#line 108 "../../prop-src/trs3.pcc"
                          } else {
                            
                            L2:; 
#line 110 "../../prop-src/trs3.pcc"
                          return LISTexp(_CONSterm(term)->_2,NOcons,rev(heads),make_exp(term)); 
#line 110 "../../prop-src/trs3.pcc"
                          }
                        } break;
                        case 2: {
                          if (
#line 105 "../../prop-src/trs3.pcc"
                          (_CONSterm(term)->_1 == _CONSterm(t)->_1)
#line 105 "../../prop-src/trs3.pcc"
) {
                            
#line 106 "../../prop-src/trs3.pcc"
                           heads = 
#line 106 "../../prop-src/trs3.pcc"
#line 106 "../../prop-src/trs3.pcc"
                            list_1_(make_exp(_CONSterm(t)->_4[0]),heads)
#line 106 "../../prop-src/trs3.pcc"
#line 106 "../../prop-src/trs3.pcc"
                            ; t = _CONSterm(t)->_4[1]; 
#line 106 "../../prop-src/trs3.pcc"
                          } else {
                             goto L2; }
                        } break;
                        default: { goto L2; }
                      }
                      } break;
                    default: { goto L2; } break;
                  }
                }
              }
#line 111 "../../prop-src/trs3.pcc"
#line 111 "../../prop-src/trs3.pcc"
              
              
#line 112 "../../prop-src/trs3.pcc"
            } else {
              
              L3:; 
#line 114 "../../prop-src/trs3.pcc"
             return CONSexp( _CONSterm(term)->_2, 
#line 114 "../../prop-src/trs3.pcc"
#line 114 "../../prop-src/trs3.pcc"
              nil_1_
#line 114 "../../prop-src/trs3.pcc"
#line 114 "../../prop-src/trs3.pcc"
              , TUPLEexp( make_exp( _CONSterm(term)->_3, _CONSterm(term)->_4))); 
#line 114 "../../prop-src/trs3.pcc"
            }
          } break;
          default: { goto L3; }
        }
      } else {
#line 96 "../../prop-src/trs3.pcc"
       return LITERALexp(literal_map[_CONSterm(term)->_1]); 
#line 96 "../../prop-src/trs3.pcc"
      }
      } break;
    case a_Term::tag_VARterm: {
#line 115 "../../prop-src/trs3.pcc"
     return _VARterm(term)->_3; 
#line 115 "../../prop-src/trs3.pcc"
      } break;
    case a_Term::tag_CODEterm: {
#line 116 "../../prop-src/trs3.pcc"
     return _CODEterm(term)->CODEterm; 
#line 116 "../../prop-src/trs3.pcc"
      } break;
    default: {
#line 117 "../../prop-src/trs3.pcc"
     bug("TRS::make_exp"); return NOexp; 
#line 117 "../../prop-src/trs3.pcc"
      } break;
  }
}
#line 118 "../../prop-src/trs3.pcc"
#line 118 "../../prop-src/trs3.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to translate a term into code
//
///////////////////////////////////////////////////////////////////////////////

Exps TRS::make_exp(int n, Term terms[]) const
{
  Exps exps = 
#line 129 "../../prop-src/trs3.pcc"
#line 129 "../../prop-src/trs3.pcc"
nil_1_
#line 129 "../../prop-src/trs3.pcc"
#line 129 "../../prop-src/trs3.pcc"
;
  for (int i = n - 1; i >= 0; i--)
     exps = 
#line 131 "../../prop-src/trs3.pcc"
#line 131 "../../prop-src/trs3.pcc"
list_1_(make_exp(terms[i]),exps)
#line 131 "../../prop-src/trs3.pcc"
#line 131 "../../prop-src/trs3.pcc"
;
  return exps;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to emit replacement code for the rhs, taking into account
//  of the specializations.
//
///////////////////////////////////////////////////////////////////////////////

Bool TRS::gen_replacement(CodeGen& C, Rule r, Exp default_rhs)
{
  int levels = 0;
  MatchRule rule = rule_map[r];
  Bool optimized = false;

  for (int i = 0; i < num_var_map[r]; i++)
  {
    Residues residues = residue_map[r][i];
    if (residues != 
#line 151 "../../prop-src/trs3.pcc"
#line 151 "../../prop-src/trs3.pcc"
nil_1_
#line 151 "../../prop-src/trs3.pcc"
#line 151 "../../prop-src/trs3.pcc"
)
    {
      levels++;
      optimized = true;
	  if (levels == 1)
	  {
	    C.pr("%^%t repl__;", rule->ty, "");
	  }
      Pat pat     = var_pat_map[r][i];
      Exp pat_exp = pat->selector;
      Ty  pat_ty  = pat->ty;
    Id  state_var = compiler.gen_get_rewrite_state(pat_ty,pat_exp);
    C.pr("%^switch (%s) {%+", state_var);
    for_each(Residue, res, residues)
    {
      C.pr("%^case %i: repl__ = %e; break;", res._1, make_exp(res._2));
    }
    C.pr("%^default: ");
    }
  }

  if (levels > 0)
  {
    if (optimized_map[r] != NOexp)
      default_rhs = optimized_map[r];
    C.pr("%^repl__ = %e; break;", default_rhs);
    for (int j = 0; j < levels; j++)
    {
      C.pr("%-%^}");
    }
  }
  else if (optimized_map[r] != NOexp)
  {
    C.pr("%^%t repl__ = %e;", rule->ty, "", optimized_map[r]);
    optimized = true;
  }

  return optimized;
}
#line 190 "../../prop-src/trs3.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 17
Number of ifs generated      = 4
Number of switches generated = 4
Number of labels             = 2
Number of gotos              = 4
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
