///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.8),
//  last updated on Sep 16, 2005.
//  The original source file is "..\..\prop-src\matchgen.pcc".
///////////////////////////////////////////////////////////////////////////////

#line 1 "../../prop-src/matchgen.pcc"
///////////////////////////////////////////////////////////////////////////////
//
//  This file implements the backend for pattern matching,
//  string matching, and lexical scanning constructs.  C++ code is
//  emitted in this file.
//
///////////////////////////////////////////////////////////////////////////////

#include <limits>
#include <iostream>
#include <strstream>
#include <AD/contain/bitset.h>
#include <AD/automata/lexergen.h>
#include <AD/strings/charesc.h>
#include <AD/memory/mempool.h>
#include <AD/sort/heapsort.h>
#include <AD/sort/heapsrt2.h>
#include "ir.h"
#include "ast.h"
#include "matchcom.h"
#include "type.h"
#include "labelgen.h"
#include "hashtab.h"
#include "config.h"
#include "options.h"
#include "list.h"


///////////////////////////////////////////////////////////////////////////////
//
//  Class to mark the current rule.
//
///////////////////////////////////////////////////////////////////////////////

MarkCurrentRule::MarkCurrentRule(MatchRule& c, MatchRule n)
    : current_rule(c), old_rule(c) { c = n; }

MarkCurrentRule::~MarkCurrentRule() { current_rule = old_rule; }

///////////////////////////////////////////////////////////////////////////////
//
//  Method to extract the line number of the current rule
//
///////////////////////////////////////////////////////////////////////////////

int MatchCompiler::current_rule_line() const
{
  if (current_rule == 0)
    bug( "MatchCompiler::current_rule_line()\n");
  return current_rule->begin_line;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to extract the text of the current rule
//
///////////////////////////////////////////////////////////////////////////////

const char * MatchCompiler::current_rule_text() const
{
  if (current_rule == 0)
    bug( "MatchCompiler::current_rule_text()\n");
  char buffer[4096];
  std::ostrstream stream(buffer,sizeof(buffer));
  std::ostream& s = stream;
  s << current_rule << std::ends;
  buffer[sizeof(buffer)-1] = '\0';
  return make_quoted_string(buffer);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Current index map.
//
///////////////////////////////////////////////////////////////////////////////

HashTable * current_index_map = 0;
Bool        merge_match       = true;  // should we merge the DFAs?
Id          current_failure   = 0;     // jump label for failure

///////////////////////////////////////////////////////////////////////////////
//
//  Is the expression simple?
//
///////////////////////////////////////////////////////////////////////////////

Bool is_simple_exp( Exp exp)
{
  
#line 89 "../../prop-src/matchgen.pcc"
#line 93 "../../prop-src/matchgen.pcc"
{
  for (;;) {
    if (exp) {
      switch (exp->tag__) {
        case a_Exp::tag_MARKEDexp: {
#line 92 "../../prop-src/matchgen.pcc"
         exp = _MARKEDexp(exp)->_2; 
#line 92 "../../prop-src/matchgen.pcc"
          } break;
        case a_Exp::tag_LITERALexp:
        case a_Exp::tag_IDexp: {
#line 91 "../../prop-src/matchgen.pcc"
         return true; 
#line 91 "../../prop-src/matchgen.pcc"
          } break;
        default: {
          L2:; 
#line 93 "../../prop-src/matchgen.pcc"
         return false; 
#line 93 "../../prop-src/matchgen.pcc"
          } break;
      }
    } else { goto L2; }
  }
}
#line 94 "../../prop-src/matchgen.pcc"
#line 94 "../../prop-src/matchgen.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Generate match variable bindings for complex match expressions.
//
///////////////////////////////////////////////////////////////////////////////

void compute_match_variables( MatchExps exps)
{
  static LabelGen vars("_V");
  for_each (MatchExp, me, exps)
  {
    
#line 108 "../../prop-src/matchgen.pcc"
#line 112 "../../prop-src/matchgen.pcc"
{
  if (
#line 110 "../../prop-src/matchgen.pcc"
  ((me->_2 == 0) && (! is_simple_exp(me->_1)))
#line 110 "../../prop-src/matchgen.pcc"
) {
    
#line 111 "../../prop-src/matchgen.pcc"
   me->_2 = vars.new_label(); 
#line 111 "../../prop-src/matchgen.pcc"
  } else {
    
#line 112 "../../prop-src/matchgen.pcc"
   /* skip */ 
#line 112 "../../prop-src/matchgen.pcc"
  }
}
#line 113 "../../prop-src/matchgen.pcc"
#line 113 "../../prop-src/matchgen.pcc"

  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Generate pattern matching code from a match dag
//
///////////////////////////////////////////////////////////////////////////////

void MatchCompiler::gen( Match mt, MatchOptions match_options, Ty match_ty)
{
   if (mt == FAILmatch)
   {
      if (current_failure)
        pr ( "%? goto %s; ", current_failure);
      return;
   }

   // check for duplicates

   if (mt->label)
   {
     pr( "%? goto %s; ", mt->label);
     gotos++;
     return;
   }
   if (mt->shared > 1)
   {
     goto_labels++;
     pr( "%^%s:; ", mt->label = labels.new_label());
   }

   
#line 146 "../../prop-src/matchgen.pcc"
#line 238 "../../prop-src/matchgen.pcc"
{
  if (boxed(mt)) {
    switch (mt->tag__) {
      case a_Match::tag_SUCCESSmatch: {
#line 150 "../../prop-src/matchgen.pcc"
        
        MarkCurrentRule mark( current_rule, _SUCCESSmatch(mt)->_2);
        pr ("%&", _SUCCESSmatch(mt)->_2->_5);
        
#line 153 "../../prop-src/matchgen.pcc"
        } break;
      case a_Match::tag_SUCCESSESmatch: {
#line 161 "../../prop-src/matchgen.pcc"
        
        if (current_options & MATCHwithtreecost)
          gen_treecost_match( FAILmatch, _SUCCESSESmatch(mt)->_2, _SUCCESSESmatch(mt)->_3);
        else
          gen_success_match( _SUCCESSESmatch(mt)->_1, _SUCCESSESmatch(mt)->_2, _SUCCESSESmatch(mt)->_3);
        
#line 166 "../../prop-src/matchgen.pcc"
        } break;
      case a_Match::tag_COSTmatch: {
#line 155 "../../prop-src/matchgen.pcc"
       gen_cost_success_match( _COSTmatch(mt)->_1, _COSTmatch(mt)->_3, _COSTmatch(mt)->_4); 
#line 155 "../../prop-src/matchgen.pcc"
        } break;
      case a_Match::tag_GUARDmatch: {
#line 170 "../../prop-src/matchgen.pcc"
      ifs++; pr ("%^if (%E) {%+%^%m%-%?} else {%+%^%m%-%?}\n", _GUARDmatch(mt)->_1, _GUARDmatch(mt)->_2, _GUARDmatch(mt)->_3); 
#line 170 "../../prop-src/matchgen.pcc"
        } break;
      case a_Match::tag_LITERALmatch: {
        switch (_LITERALmatch(mt)->_3[0]->tag__) {
          case a_Literal::tag_REGEXPlit: {
#line 232 "../../prop-src/matchgen.pcc"
           if (options.generate_report) open_logfile() << mt << '\n';
            gen_regexp_match( _LITERALmatch(mt)->_2, _LITERALmatch(mt)->_4, _LITERALmatch(mt)->_3, _LITERALmatch(mt)->_5, _LITERALmatch(mt)->_6, match_options, match_ty);
            
#line 234 "../../prop-src/matchgen.pcc"
            } break;
          case a_Literal::tag_QUARKlit: {
#line 236 "../../prop-src/matchgen.pcc"
           gen_quark_match( _LITERALmatch(mt)->_2, _LITERALmatch(mt)->_4, _LITERALmatch(mt)->_3, _LITERALmatch(mt)->_5, _LITERALmatch(mt)->_6, match_options); 
#line 236 "../../prop-src/matchgen.pcc"
            } break;
          case a_Literal::tag_BIGINTlit: {
            L3:; 
#line 238 "../../prop-src/matchgen.pcc"
           bug ("gen(Match)"); 
#line 238 "../../prop-src/matchgen.pcc"
            } break;
          case a_Literal::tag_REALlit:
          case a_Literal::tag_STRINGlit: {
#line 230 "../../prop-src/matchgen.pcc"
           gen_binary_search_on_literals( _LITERALmatch(mt)->_2, _LITERALmatch(mt)->_4, _LITERALmatch(mt)->_3, _LITERALmatch(mt)->_5, _LITERALmatch(mt)->_6); 
#line 230 "../../prop-src/matchgen.pcc"
            } break;
          default: {
#line 197 "../../prop-src/matchgen.pcc"
            
            Bool is_boolean;
            
#line 199 "../../prop-src/matchgen.pcc"
#line 202 "../../prop-src/matchgen.pcc"
            {
              Literal _V1 = _LITERALmatch(mt)->_3[0];
              switch (_V1->tag__) {
                case a_Literal::tag_BOOLlit: {
#line 201 "../../prop-src/matchgen.pcc"
                 is_boolean = true; 
#line 201 "../../prop-src/matchgen.pcc"
                  } break;
                default: {
#line 202 "../../prop-src/matchgen.pcc"
                 is_boolean = false; 
#line 202 "../../prop-src/matchgen.pcc"
                  } break;
              }
            }
#line 203 "../../prop-src/matchgen.pcc"
#line 203 "../../prop-src/matchgen.pcc"
            
            switches++;
            pr ( "%^switch (%e) {\n%+", _LITERALmatch(mt)->_2);
            for (int i = 0; i < _LITERALmatch(mt)->_4; )
            {
              int j;
              for (j = i+1; j < _LITERALmatch(mt)->_4; j++) if (_LITERALmatch(mt)->_5[i] != _LITERALmatch(mt)->_5[j]) break;
              int k = i;
              if (is_boolean && j == _LITERALmatch(mt)->_4 && _LITERALmatch(mt)->_4 == 2)
              {
                pr ("%^default:"); i = _LITERALmatch(mt)->_4;
              }
              else
              {
                for ( ; i < j; i++)
                {
                  pr ("%^case %l:", _LITERALmatch(mt)->_3[i]);
                  if (i != j - 1)
                    pr ("\n");
                }
              }
              pr(" {%+%m%-%?} break;\n", _LITERALmatch(mt)->_5[k]);
            }
            if (! is_boolean || _LITERALmatch(mt)->_4 < 2) pr ("%^default: {%+%m%-%?}", _LITERALmatch(mt)->_6);
            pr("%-%^}\n");
            
#line 228 "../../prop-src/matchgen.pcc"
            } break;
        }
        } break;
      case a_Match::tag_RANGEmatch: {
#line 168 "../../prop-src/matchgen.pcc"
       gen_range_match( _RANGEmatch(mt)->_1, _RANGEmatch(mt)->_2, _RANGEmatch(mt)->_3, _RANGEmatch(mt)->_4, _RANGEmatch(mt)->_5, _RANGEmatch(mt)->_6, mt); 
#line 168 "../../prop-src/matchgen.pcc"
        } break;
      case a_Match::tag_CONSmatch: {
        if (_CONSmatch(mt)->_4) {
          switch (_CONSmatch(mt)->_4->tag__) {
            case a_Ty::tag_TYCONty: {
              if (boxed(_TYCONty(_CONSmatch(mt)->_4)->_1)) {
                switch (_TYCONty(_CONSmatch(mt)->_4)->_1->tag__) {
                  case a_TyCon::tag_DATATYPEtycon: {
                    if (
#line 173 "../../prop-src/matchgen.pcc"
                    (_DATATYPEtycon(_TYCONty(_CONSmatch(mt)->_4)->_1)->qualifiers & QUALview)
#line 173 "../../prop-src/matchgen.pcc"
) {
                      
#line 174 "../../prop-src/matchgen.pcc"
                     gen_view_match( _DATATYPEtycon(_TYCONty(_CONSmatch(mt)->_4)->_1)->id, _CONSmatch(mt)->_2, _DATATYPEtycon(_TYCONty(_CONSmatch(mt)->_4)->_1)->view_match, _CONSmatch(mt)->_5, _DATATYPEtycon(_TYCONty(_CONSmatch(mt)->_4)->_1)->terms, _CONSmatch(mt)->_6, _CONSmatch(mt)->_7,
                      _DATATYPEtycon(_TYCONty(_CONSmatch(mt)->_4)->_1)->opt, _DATATYPEtycon(_TYCONty(_CONSmatch(mt)->_4)->_1)->qualifiers & QUALextensible); 
#line 175 "../../prop-src/matchgen.pcc"
                    } else {
                      
                      switch (_DATATYPEtycon(_TYCONty(_CONSmatch(mt)->_4)->_1)->arg) {
                        case 0: {
#line 178 "../../prop-src/matchgen.pcc"
                         gen_switch( _DATATYPEtycon(_TYCONty(_CONSmatch(mt)->_4)->_1)->id, _CONSmatch(mt)->_2, _CONSmatch(mt)->_3, _DATATYPEtycon(_TYCONty(_CONSmatch(mt)->_4)->_1)->unit, _DATATYPEtycon(_TYCONty(_CONSmatch(mt)->_4)->_1)->terms, _CONSmatch(mt)->_6, _CONSmatch(mt)->_7, mt->shared,
                          false, false, _DATATYPEtycon(_TYCONty(_CONSmatch(mt)->_4)->_1)->opt, _DATATYPEtycon(_TYCONty(_CONSmatch(mt)->_4)->_1)->qualifiers & QUALextensible); 
#line 179 "../../prop-src/matchgen.pcc"
                        } break;
                        default: {
                          switch (_DATATYPEtycon(_TYCONty(_CONSmatch(mt)->_4)->_1)->unit) {
                            case 0: {
#line 182 "../../prop-src/matchgen.pcc"
                             gen_switch( _DATATYPEtycon(_TYCONty(_CONSmatch(mt)->_4)->_1)->id, _CONSmatch(mt)->_2, _CONSmatch(mt)->_3, _DATATYPEtycon(_TYCONty(_CONSmatch(mt)->_4)->_1)->arg, _DATATYPEtycon(_TYCONty(_CONSmatch(mt)->_4)->_1)->terms, _CONSmatch(mt)->_6, _CONSmatch(mt)->_7, mt->shared,
                              false, true, _DATATYPEtycon(_TYCONty(_CONSmatch(mt)->_4)->_1)->opt, _DATATYPEtycon(_TYCONty(_CONSmatch(mt)->_4)->_1)->qualifiers & QUALextensible); 
#line 183 "../../prop-src/matchgen.pcc"
                            } break;
                            default: {
#line 186 "../../prop-src/matchgen.pcc"
                              
                              ifs++;
                              pr ((_DATATYPEtycon(_TYCONty(_CONSmatch(mt)->_4)->_1)->unit > 1 ? "%^if (boxed(%e)) {%+" : "%^if (%e) {%+"), _CONSmatch(mt)->_2);
                              gen_switch( _DATATYPEtycon(_TYCONty(_CONSmatch(mt)->_4)->_1)->id, _CONSmatch(mt)->_2, _CONSmatch(mt)->_3, _DATATYPEtycon(_TYCONty(_CONSmatch(mt)->_4)->_1)->arg, _DATATYPEtycon(_TYCONty(_CONSmatch(mt)->_4)->_1)->terms + _DATATYPEtycon(_TYCONty(_CONSmatch(mt)->_4)->_1)->unit, _CONSmatch(mt)->_6 + _DATATYPEtycon(_TYCONty(_CONSmatch(mt)->_4)->_1)->unit, _CONSmatch(mt)->_7, mt->shared,
                                          true, true, _DATATYPEtycon(_TYCONty(_CONSmatch(mt)->_4)->_1)->opt, _DATATYPEtycon(_TYCONty(_CONSmatch(mt)->_4)->_1)->qualifiers & QUALextensible);
                              pr ( "%-%?} else {%+");
                              gen_switch( _DATATYPEtycon(_TYCONty(_CONSmatch(mt)->_4)->_1)->id, _CONSmatch(mt)->_2, _CONSmatch(mt)->_3, _DATATYPEtycon(_TYCONty(_CONSmatch(mt)->_4)->_1)->unit, _DATATYPEtycon(_TYCONty(_CONSmatch(mt)->_4)->_1)->terms, _CONSmatch(mt)->_6, _CONSmatch(mt)->_7, mt->shared,
                                          true, false, _DATATYPEtycon(_TYCONty(_CONSmatch(mt)->_4)->_1)->opt, _DATATYPEtycon(_TYCONty(_CONSmatch(mt)->_4)->_1)->qualifiers & QUALextensible);
                              pr ( "%-%?}\n");
                              
#line 195 "../../prop-src/matchgen.pcc"
                            }
                          }
                        }
                      }
                    }
                    } break;
                  default: { goto L3; } break;
                }
              } else { goto L3; }
              } break;
            default: { goto L3; } break;
          }
        } else { goto L3; }
        } break;
      case a_Match::tag_TREECOSTmatch: {
#line 157 "../../prop-src/matchgen.pcc"
       gen_treecost_match( _TREECOSTmatch(mt)->_1, _TREECOSTmatch(mt)->_2, _TREECOSTmatch(mt)->_3); 
#line 157 "../../prop-src/matchgen.pcc"
        } break;
      case a_Match::tag_TREELABELmatch: {
#line 159 "../../prop-src/matchgen.pcc"
       gen_treelabel_match( _TREELABELmatch(mt)->_1, _TREELABELmatch(mt)->_2, _TREELABELmatch(mt)->_3, _TREELABELmatch(mt)->_4); 
#line 159 "../../prop-src/matchgen.pcc"
        } break;
      default: { goto L3; } break;
    }
  } else {
    if (mt) {
       goto L3; } else {
      }
  }
}
#line 239 "../../prop-src/matchgen.pcc"
#line 239 "../../prop-src/matchgen.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to generate a bitmap of all the successful matching rules.
//
///////////////////////////////////////////////////////////////////////////////

void MatchCompiler::gen_success_match( int n, const BitSet *set, MatchRules)
{
  pr(
      "%^{%+  static const unsigned char matched_set__[%i] =\n%^{  %+",
      (n + 7) / 8
    );
  for( int i = 0; i < (n + 7) / 8; i++)
  {
    if (i > 0)
      pr (", ");
    if (i != 0 && (i % 8) == 0)
      pr ("%^");
    pr ("%i ", (int) set->byte(i));
  }
  pr(
      "%-};\n"
      "%^m__ = matched_set__;\n"
      "%-%^}\n"
    );
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to generate code for cost minimalization.
//
///////////////////////////////////////////////////////////////////////////////

void MatchCompiler::gen_cost_success_match( int n, const BitSet *set,
                                            MatchRules rules)
{
  int rule_no = 0;
  
#line 279 "../../prop-src/matchgen.pcc"
#line 300 "../../prop-src/matchgen.pcc"
{
  for (;;) {
    if (rules) {
#line 282 "../../prop-src/matchgen.pcc"
      
      if ((*set)[rule_no])
      {
        
#line 285 "../../prop-src/matchgen.pcc"
#line 295 "../../prop-src/matchgen.pcc"
      {
        MatchRule _V2 = rules->_1;
#line 288 "../../prop-src/matchgen.pcc"
        
        
#line 289 "../../prop-src/matchgen.pcc"
#line 294 "../../prop-src/matchgen.pcc"
        {
          Cost _V3 = _V2->_4;
          if (_V3) {
            if (_V3->tag__) {
              } else {
              }
          } else {}
        }
#line 294 "../../prop-src/matchgen.pcc"
#line 294 "../../prop-src/matchgen.pcc"
        
        
#line 295 "../../prop-src/matchgen.pcc"
      }
#line 296 "../../prop-src/matchgen.pcc"
#line 296 "../../prop-src/matchgen.pcc"
      
      }
      rules = rules->_2;
      rule_no++;
      
#line 300 "../../prop-src/matchgen.pcc"
    } else { goto L4; }
  }
  L4:;
}
#line 301 "../../prop-src/matchgen.pcc"
#line 301 "../../prop-src/matchgen.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to generate a switch statement for pattern matching.
//  This method is responsible for generating optimized code for a one-level
//  match using C++'s "switch" statement.
//
///////////////////////////////////////////////////////////////////////////////

void MatchCompiler::gen_switch
   (Id id, Exp e, Ty ty, int n, Cons terms[], Match m[], Match def, int shared,
    Bool variant, Bool boxed, TyOpt optimizations, Bool is_refutable)
{
  if (n == 1)          // only one arm
     gen(m[0]);
  else if (n == 2)   // two arms, use "if"
  {
    if (m[0] == m[1])
    {
      merges++;
      if (m[0] != FAILmatch)
        m[0]->shared -= shared;
      gen(m[0]);
    }
    else
    {
       ifs++;
       Id prefix, suffix;
       if (boxed)
       {
         if (optimizations & OPTtaggedpointer)
         {
           prefix = "untagp(";
           suffix = ")";
         }
         else
         {
           prefix = "";
           suffix = "->tag__";
         }
       }
       else
         prefix = suffix = "";

       pr( "%^if (%s%e%s) {%+%^%m%-%?} else {%+%^%m%-%?}\n",
           prefix, e, suffix, m[1], m[0]);
    }
  }
  else
  {
    /////////////////////////////////////////////////////////////////////////
    //  The following is the general case for handling n-ary branches.
    /////////////////////////////////////////////////////////////////////////

    int i, j;

    /////////////////////////////////////////////////////////////////////////
    // If all n branches are the same, eliminate the match
    /////////////////////////////////////////////////////////////////////////

    for (i = n - 1; i > 0; i--) if (m[i] != m[i-1]) break;
    if (i == 0)
    {
      if (m[0] != FAILmatch)
        m[0]->shared -= (n-1) * shared;
      merges++; gen(m[0]); return;
    }

    switches++;
    Id prefix, suffix;

    /////////////////////////////////////////////////////////////////////////
    // Generate the "switch" expression.
    /////////////////////////////////////////////////////////////////////////

    if (boxed)
    {
      if (optimizations & OPTtaggedpointer)
      {
        prefix = "untagp(";
        suffix = ")";
      }
      else
      {
        prefix = "";
        suffix = "->tag__";
      }
    }
    else
    {
      if (variant)
      {
        prefix = "(int)";
        suffix = "";
      }
      else
      prefix = suffix = "";
    }

    pr ("%^switch (%s%e%s) {\n%+", prefix, e, suffix);

    /////////////////////////////////////////////////////////////////////////
    //  Partition the arms of the matches into alternatives with the
    //  same actions.  Sort the partitions in increasing sizes.
    /////////////////////////////////////////////////////////////////////////

    struct ConsMatch
    {
      Cons term;
      Match action;
      int tag;
    };

    struct MatchPartition
    {
      int count;
      Conses terms;
      Match action;
      int first_tag;
    };

    ConsMatch *sorted =
            (ConsMatch *) mem_pool.c_alloc( sizeof( ConsMatch) * n);
    MatchPartition *parts =
            (MatchPartition *)mem_pool.c_alloc( sizeof( MatchPartition) * n);

    int number_of_parts = 0;
    {
      for (i = 0; i < n; i++)
      {
        sorted[i].term      = terms[i];
        sorted[i].action    = m[i];
        if (terms[i] != NOcons)
          sorted[i].tag = terms[i]->tag;
      }

      // sort branches according the actions

      heapSort( ConsMatch, sorted, n,
                (key.action < sorted[i].action ||
                key.action == sorted[i].action &&
                key.tag < sorted[i].tag));

      // partition each branch by action

      for (i = n - 1; i >= 0; i--)
      {
        if (i == n-1 || sorted[i].action != sorted[i+1].action)
        {
          parts[number_of_parts].terms  = 
#line 452 "../../prop-src/matchgen.pcc"
#line 452 "../../prop-src/matchgen.pcc"
list_1_(sorted[i].term)
#line 452 "../../prop-src/matchgen.pcc"
#line 452 "../../prop-src/matchgen.pcc"
;
          parts[number_of_parts].action = sorted[i].action;
          parts[number_of_parts].count  = 1;
          parts[number_of_parts].first_tag = sorted[i].tag;
          number_of_parts++;
        }
        else
        {
          parts[number_of_parts-1].terms =
              
#line 461 "../../prop-src/matchgen.pcc"
#line 461 "../../prop-src/matchgen.pcc"
list_1_(sorted[i].term,parts[(number_of_parts - 1)].terms)
#line 461 "../../prop-src/matchgen.pcc"
#line 461 "../../prop-src/matchgen.pcc"
;
          parts[number_of_parts-1].count++;
          if (parts[number_of_parts-1].first_tag > sorted[i].tag)
            parts[number_of_parts-1].first_tag = sorted[i].tag;
        }
      }

      // Sort partitions in order of frequency; so that
      // the most frequent case becomes the "default" inside
      // the "switch" statement.
      heapSort( MatchPartition, parts, number_of_parts,
                (key.count < parts[i].count ||
                key.count == parts[i].count &&
                key.first_tag < parts[i].first_tag));
    }

    /////////////////////////////////////////////////////////////////////////
    // Generate the arms of the "switch".
    // We try to combine the arms that are the same together into
    // one rule to help the compiler.
    /////////////////////////////////////////////////////////////////////////
    for (i = 0; i < number_of_parts; i++)
    {
      if (i == number_of_parts - 1)
        pr( "%^default:");
      else
      {
        Conses tags = parts[i].terms;
        
#line 489 "../../prop-src/matchgen.pcc"
#line 497 "../../prop-src/matchgen.pcc"
{
  for (;;) {
    if (tags) {
#line 492 "../../prop-src/matchgen.pcc"
      
      pr( "%^case %*:", tags->_1, false);
      if (tags->_2 != 
#line 494 "../../prop-src/matchgen.pcc"
#line 494 "../../prop-src/matchgen.pcc"
      nil_1_
#line 494 "../../prop-src/matchgen.pcc"
#line 494 "../../prop-src/matchgen.pcc"
      )
      pr( "\n");
      tags = tags->_2;
      
#line 497 "../../prop-src/matchgen.pcc"
    } else { goto L5; }
  }
  L5:;
}
#line 498 "../../prop-src/matchgen.pcc"
#line 498 "../../prop-src/matchgen.pcc"

      }
      if (parts[i].action != FAILmatch)
        parts[i].action->shared -= (parts[i].count - 1) * shared;
      pr( " {%+%?%m%?} break;\n%-", parts[i].action);
    }

    pr( "%-%^}\n");
  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Generate binary search for testing literals
//
///////////////////////////////////////////////////////////////////////////////

void MatchCompiler::gen_binary_search_on_literals
   (Exp e, int n, Literal l[], Match m[], Match d)
{
  if (n <= 4)
  {
    /////////////////////////////////////////////////////////////////////////
    //  Generate linear tests for simple literal tests.
    /////////////////////////////////////////////////////////////////////////
    for (int i = 0; i < n; i++)
    {
       ifs++;
       if (i > 0)
         pr( "%^else ");
       else
         pr( "%^");
       pr( "if (%=(%e,%l)) {%m}\n", l[i], e, l[i], m[i]);
    }
    if (d != FAILmatch)
      pr( "%^else {%m}\n", d);
    else if (current_failure)
      pr( "%^else goto %s;\n", current_failure);
  }
  else
  {
    /////////////////////////////////////////////////////////////////////////
    //  Generate binary search for tests containing many alternatives.
    /////////////////////////////////////////////////////////////////////////
    int k = (n+1)/2;
    ifs++;
    pr( "%^if (%<(%e,%l)) {\n%+", l[k], e, l[k]);
    gen_binary_search_on_literals( e, k, l, m, d);
    pr( "%-%^} else {\n%+");
    gen_binary_search_on_literals( e, n-k, l+k, m+k, d);
    pr( "%-%^}\n");
  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Generate range matching
//
///////////////////////////////////////////////////////////////////////////////

void MatchCompiler::gen_range_match
   (Pos pos, Exp e, int lo, int hi, Match a, Match b, Match m)
{
  if (lo == hi)
  {
    switches++;
    pr( "%^switch (%e) {%+",e);
    
#line 565 "../../prop-src/matchgen.pcc"
#line 568 "../../prop-src/matchgen.pcc"
{
  for (;;) {
    if (boxed(m)) {
      switch (m->tag__) {
        case a_Match::tag_RANGEmatch: {
          if (
#line 567 "../../prop-src/matchgen.pcc"
          ((_RANGEmatch(m)->_3 == _RANGEmatch(m)->_4) && pos_equal(pos,_RANGEmatch(m)->_1))
#line 567 "../../prop-src/matchgen.pcc"
) {
            
#line 568 "../../prop-src/matchgen.pcc"
           pr( "%^case %i: {%+%m%-%?} break;", _RANGEmatch(m)->_3, _RANGEmatch(m)->_5); m = _RANGEmatch(m)->_6; 
#line 568 "../../prop-src/matchgen.pcc"
          } else {
             goto L6; }
          } break;
        default: { goto L6; } break;
      }
    } else { goto L6; }
  }
  L6:;
}
#line 569 "../../prop-src/matchgen.pcc"
#line 569 "../../prop-src/matchgen.pcc"

    pr( "%^default: {%+%m%-%?}" "%-%^}\n", m);
  }
  else
  {
    ifs++;
    if (lo == 0)
      pr ( "%^if (%e <= %i) {%+%^%m%-%?} else {%+%^%m%-%?}\n", e, hi, a, b);
    else if (hi == INT_MAX)
       pr( "%^if (%e >= %i) {%+%^%m%-%?} else {%+%^%m%-%?}\n", e, lo, a, b);
    else
       pr( "%^if (%i <= %e && %e <= %i) {%+%^%m%-%?} else {%+%^%m%-%?}\n",
           lo, e, e, hi, a, b);
  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Generate view matching
//
///////////////////////////////////////////////////////////////////////////////

void MatchCompiler::gen_view_match
   (Id id, Exp e, Exp view_match, int n, Cons terms [], Match m[], Match d,
    TyOpt opt, TyQual qual)
{
  if (view_match != NOexp)
  {
    switches++;
    pr( "%^switch (%e) {%+", subst( view_match, &e));
    for (int i = 0; i < n; i++)
      pr( "%^case %e: {%+%m%-%?} break;", terms[i]->view_predicate, m[i]);
    pr( "%-%^}\n");
  }
  else
  {
    int i;
    for (i = 0; i < n; i++)
    {
      int j;
      for (j = i + 1; j < n; j++)
        if (m[i] != m[j])
          break;
      if (j == n)
        break;
      Exp predicate_fun = terms[i]->view_predicate;
      Exp predicate     = subst(predicate_fun,&e);
      ifs++;
      pr( "%^%sif (%e) {%+%^%m%-%?} ", (i > 0 ? "else " : ""), predicate, m[i]);
    }
    if (i < n)
      pr( "%^%s{%+%^%m%-%?}\n", (i > 0 ? "else " : ""), m[i]);
  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Generate regular expression matching as a DFA.
//
///////////////////////////////////////////////////////////////////////////////
void MatchCompiler::gen_regexp_match
   (Exp e, int n, Literal l[], Match m[], Match d,
    MatchOptions options, Ty match_ty)
{
  LexerGen lexerGen;
  const char ** regexps = (const char **)mem_pool[n * sizeof(const char *)];
  const char ** contexts = 0;

  ////////////////////////////////////////////////////////////////////////////
  //  If we have a match type, locate the set of contexts.
  ////////////////////////////////////////////////////////////////////////////
  if (options & MATCHscanner)
  {
    
#line 642 "../../prop-src/matchgen.pcc"
#line 661 "../../prop-src/matchgen.pcc"
{
  Ty _V4 = deref_all(match_ty);
  if (_V4) {
    switch (_V4->tag__) {
      case a_Ty::tag_TYCONty: {
        if (boxed(_TYCONty(_V4)->_1)) {
          switch (_TYCONty(_V4)->_1->tag__) {
            case a_TyCon::tag_DATATYPEtycon: {
#line 646 "../../prop-src/matchgen.pcc"
              
              contexts = (const char **)mem_pool[(_DATATYPEtycon(_TYCONty(_V4)->_1)->unit+1)*sizeof(const char *)];
              if (_DATATYPEtycon(_TYCONty(_V4)->_1)->unit <= 1)
                msg("%L%wdatatype has less than 2 unit constructors for contexts");
              for (int i = 1; i < _DATATYPEtycon(_TYCONty(_V4)->_1)->unit; i++)
              {
                
#line 652 "../../prop-src/matchgen.pcc"
#line 656 "../../prop-src/matchgen.pcc"
              {
                Cons _V5 = _DATATYPEtycon(_TYCONty(_V4)->_1)->terms[i];
                if (_V5) {
#line 654 "../../prop-src/matchgen.pcc"
                 contexts[i-1] = _V5->name; 
#line 654 "../../prop-src/matchgen.pcc"
                } else {}
              }
#line 656 "../../prop-src/matchgen.pcc"
#line 656 "../../prop-src/matchgen.pcc"
              
              }
              contexts[_DATATYPEtycon(_TYCONty(_V4)->_1)->unit-1] = 0;
              
#line 659 "../../prop-src/matchgen.pcc"
              } break;
            default: {
              L7:; 
#line 661 "../../prop-src/matchgen.pcc"
             error ("%Lillegal context type: %T\n", match_ty); 
#line 661 "../../prop-src/matchgen.pcc"
              } break;
          }
        } else { goto L7; }
        } break;
      default: { goto L7; } break;
    }
  } else {}
}
#line 662 "../../prop-src/matchgen.pcc"
#line 662 "../../prop-src/matchgen.pcc"

  }

  ////////////////////////////////////////////////////////////////////////////
  //  Allocate a regexp array
  ////////////////////////////////////////////////////////////////////////////
  for (int i = 0; i < n; i++)
  {
    
#line 670 "../../prop-src/matchgen.pcc"
#line 679 "../../prop-src/matchgen.pcc"
{
  Literal _V6 = l[i];
  switch (_V6->tag__) {
    case a_Literal::tag_REGEXPlit: {
#line 673 "../../prop-src/matchgen.pcc"
      
      int len           = strlen(_REGEXPlit(_V6)->REGEXPlit);
       char * regexp     = str_pool(_REGEXPlit(_V6)->REGEXPlit+1,len-1);
       regexp[len-2]     = '\0';
       regexps[i]        = regexp;
      
#line 678 "../../prop-src/matchgen.pcc"
      } break;
    default: {
#line 679 "../../prop-src/matchgen.pcc"
     bug("gen_regexp_match"); 
#line 679 "../../prop-src/matchgen.pcc"
      } break;
  }
}
#line 680 "../../prop-src/matchgen.pcc"
#line 680 "../../prop-src/matchgen.pcc"

  }

  int opt = LexerGen::None;
  if (options & MATCHscanner)
  {
    opt |= LexerGen::Backtracking;
    debug_msg("%Lgenerating backtracking scanner\n");
  }
  if (options & MATCHcaseinsensitive)
    opt |= LexerGen::CaseInsensitive;

  lexerGen.compile( n, regexps, contexts, 255, opt);

  if (! lexerGen.ok())
    error( "%L%s in: %l\n", lexerGen.error_message(), l[lexerGen.bad()]);
  else
  {
    /////////////////////////////////////////////////////////////////////////
    //  Generate the action code
    /////////////////////////////////////////////////////////////////////////
    Id id = vars.new_label();
    pr ("%^{\n%+");
    lexerGen.gen_code(*output, id);
    switches++;
    pr(
        "%^static const RegexMatch %s"
        "%^                ( %s_base,"
        "%^                  %s_check,"
        "%^                  %s_def,"
        "%^                  %s_next,"
        "%^                  %s_accept_rule,"
        "%^                  %s_equiv_classes );\n",
        id, id, id, id, id, id, id
      );
    Id rule_binding = "";
    if (options & MATCHlexemepat)
    {
      pr( "%^int rule__;");
      rule_binding = "rule__ = ";
    }
    if (options & MATCHscanner)
      pr(
          "%^const char * next = 0;\n"
          "%^switch(%s%s.MatchText(RegexMatch::start_state,%e,next)) {%+",
          rule_binding, id, e
        );
    else
      pr( "%^switch(%s%s.MatchText(%e)) {%+", rule_binding, id, e);

    for (int i = 0; i < n; i++)
      pr( "%^case %i: {%+%m%-%?} break;", i+1, m[i]);
    pr( "%^default: {%+%m%-%?}", d);
    pr( "%-%^}\n"
        "%-%^}\n");

    /////////////////////////////////////////////////////////////////////////
    //  Generate a report
    /////////////////////////////////////////////////////////////////////////
    if (::options.generate_report)
      lexerGen.print_report( open_logfile());
  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Generate quark pattern matching
//
///////////////////////////////////////////////////////////////////////////////

void MatchCompiler::gen_quark_match
   (Exp e, int n, Literal l[], Match m[], Match d, MatchOptions options)
{
  for (int i = 0; i < n; i++)
  {
    ifs++;
    pr( "%^%sif (%e == %l) {%+%^%m%-%?} ",
        (i > 0 ? "else " : ""), e, l[i], m[i]);
  }
  pr( "%^%s{%+%^%m%-%?}\n", (n > 0 ? "else " : ""), d);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to translate and merge a set of patterns
//
///////////////////////////////////////////////////////////////////////////////

Match MatchCompiler::trans_merge
   (int n, MatchRules rules, int match_options, Cost * costs)
{
  Match m = FAILmatch;
  int rule_no = 0;
  for_each ( MatchRule, r, rules)
  {
    
#line 775 "../../prop-src/matchgen.pcc"
#line 803 "../../prop-src/matchgen.pcc"
{
#line 778 "../../prop-src/matchgen.pcc"
  
  if (! r->is_chain_rule)
  {
    Match rhs;
    if (match_options & (MATCHall | MATCHwithcost))
    {
      BitSet * set = new (mem_pool,n) BitSet;
      set->add( rule_no);
      if (costs && ! (match_options & MATCHwithtreecost))
        rhs = COSTmatch( n, costs, set, rules);
      else
        rhs = SUCCESSESmatch( n, set, rules);
    }
    else
    {
      r->used = false;
      rhs = SUCCESSmatch(rule_no,r);
    }
    if (r->_3 != NOexp)
      rhs = GUARDmatch( r->_3, rhs, FAILmatch);
    rhs = trans(r->_2, POSzero, false, rhs, FAILmatch);
    debug_msg("%r => %M\n", r, rhs);
    m = merge (m, rhs);
  }
  rule_no++;
  
#line 803 "../../prop-src/matchgen.pcc"
}
#line 804 "../../prop-src/matchgen.pcc"
#line 804 "../../prop-src/matchgen.pcc"

  }
  return m;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to translate but do not merge a set of patterns.
//  Use Wadler's algorithm.
//
///////////////////////////////////////////////////////////////////////////////

Match MatchCompiler::trans_no_merge
   (int n, int rule_no, MatchRules rules, int match_options, Cost * costs)
{
  if (rules == 
#line 819 "../../prop-src/matchgen.pcc"
#line 819 "../../prop-src/matchgen.pcc"
nil_1_
#line 819 "../../prop-src/matchgen.pcc"
#line 819 "../../prop-src/matchgen.pcc"
)
    return FAILmatch;
  else
  {
    
#line 823 "../../prop-src/matchgen.pcc"
#line 846 "../../prop-src/matchgen.pcc"
{
  MatchRule _V7 = rules->_1;
#line 826 "../../prop-src/matchgen.pcc"
  
  Match rhs;
  if (match_options & (MATCHall | MATCHwithcost)) {
     BitSet * set = new (mem_pool,n) BitSet;
     set->add(rule_no);
     if (costs)
       rhs = COSTmatch( n, costs, set, rules);
     else
       rhs = SUCCESSESmatch( n, set, rules);
  }
  else
  {
     _V7->used = false;
     rhs = SUCCESSmatch( rule_no, _V7);
  }
  Match no =
     trans_no_merge( n, rule_no+1, rules->_2, match_options, costs);
  if (_V7->_3 != NOexp)
    rhs = GUARDmatch( _V7->_3, rhs, no);
  return trans( _V7->_2, POSzero, false, rhs, no);
  
#line 846 "../../prop-src/matchgen.pcc"
}
#line 847 "../../prop-src/matchgen.pcc"
#line 847 "../../prop-src/matchgen.pcc"

  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Instrument the matching code if tracing is on
//
///////////////////////////////////////////////////////////////////////////////

void MatchCompiler::instrument_trace(MatchRules rules)
{
  for_each ( MatchRule, r, rules)
  {
    
#line 861 "../../prop-src/matchgen.pcc"
#line 880 "../../prop-src/matchgen.pcc"
{
#line 864 "../../prop-src/matchgen.pcc"
  
  char buffer[4096];
  std::ostrstream stream( buffer, sizeof(buffer));
  std::ostream& s = stream;
  s << r << std::ends;
  r->_5 =
    
#line 870 "../../prop-src/matchgen.pcc"
#line 870 "../../prop-src/matchgen.pcc"
  list_1_(EXPdecl(APPexp(IDexp("PROP_TRACE"),TUPLEexp(list_1_(LITERALexp(STRINGlit(make_quoted_string(buffer))),list_1_(LITERALexp(STRINGlit(make_quoted_string(r->file_name))),list_1_(LITERALexp(INTlit(r->begin_line)))))))),list_1_(OPAQUEdecl(";"),r->_5))
#line 879 "../../prop-src/matchgen.pcc"
#line 879 "../../prop-src/matchgen.pcc"
  ;
  
#line 880 "../../prop-src/matchgen.pcc"
}
#line 881 "../../prop-src/matchgen.pcc"
#line 881 "../../prop-src/matchgen.pcc"

  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Compute the match dag from a set of pattern matching rules.
//
///////////////////////////////////////////////////////////////////////////////

Match MatchCompiler::match_of
   (int n, MatchRules rules, MatchOptions match_options)
{
  Match m;

  ////////////////////////////////////////////////////////////////////////////
  //  Save the last index map.
  ////////////////////////////////////////////////////////////////////////////

  HashTable * last_index_map = current_index_map;

  ////////////////////////////////////////////////////////////////////////////
  //  Create index map for this pattern set if necessary.
  ////////////////////////////////////////////////////////////////////////////

  if (options.adaptive_matching)
  {
    debug_msg( "Creating index map\n");
    current_index_map = new HashTable(pos_hash, pos_equal, 129);
    indexing( rules, *current_index_map);
    debug_msg( "Finished indexing\n");
  }
  else
    current_index_map = 0;

  ////////////////////////////////////////////////////////////////////////////
  //  If tracing is on, instrument the code.
  ////////////////////////////////////////////////////////////////////////////

  if (options.trace && (match_options & MATCHnotrace) == 0)
    instrument_trace(rules);

  ////////////////////////////////////////////////////////////////////////////
  //  Make a cost vector if cost minimization is in effect
  ////////////////////////////////////////////////////////////////////////////

  Cost * cost_vector = 0;

  if (match_options & MATCHwithintcost)
  {
    cost_vector = (Cost*)mem_pool[n * sizeof(Cost)];
    int i = 0;
    for_each ( MatchRule, r, rules)
    {
      
#line 935 "../../prop-src/matchgen.pcc"
#line 936 "../../prop-src/matchgen.pcc"
{
#line 936 "../../prop-src/matchgen.pcc"
 cost_vector[i] = r->_4; i++; 
#line 936 "../../prop-src/matchgen.pcc"
}
#line 936 "../../prop-src/matchgen.pcc"
#line 936 "../../prop-src/matchgen.pcc"

    }
  }

  ////////////////////////////////////////////////////////////////////////////
  //  Translate each pattern into a matching tree and merge them together.
  ////////////////////////////////////////////////////////////////////////////
  if (merge_match)
    m = trans_merge( n, rules, match_options, cost_vector);
  else
    m = trans_no_merge( n, 0, rules, match_options, cost_vector);

  m = make_dag( m, match_options, rules);
  debug_msg( "Matching DFA: %M\n", m);

  ////////////////////////////////////////////////////////////////////////////
  // Error checking.
  ////////////////////////////////////////////////////////////////////////////

  // BUG 3/6/97: Always check for selectability!!!

  if (true || (match_options & MATCHnocheck) == 0)
  {
    if (match_options & (MATCHall | MATCHwithcost))
    {
      BitSet * may_match = new (mem_pool,n) BitSet;
      matchables( m, *may_match);
      int i = 0;
      for_each ( MatchRule, r, rules)
      {
        if (! may_match->contains(i) && ! r->is_chain_rule)
          error("%!this rule is never selected: %r\n", r->loc(), r);
        i++;
      }
    }
    else
    {
      {
        for_each (MatchRule,r,rules)
        {
          if (! r->used)
            error ("%!this rule is never used: %r\n", r->loc(), r);
        }
      }
    }
  }

  ////////////////////////////////////////////////////////////////////////////
  //  Clean up the index map
  ////////////////////////////////////////////////////////////////////////////

  if (current_index_map)
    delete current_index_map;
  current_index_map = last_index_map;
  return m;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Returns true if the set of rules involve cost expressions.
//
///////////////////////////////////////////////////////////////////////////////
int involve_cost( MatchRules rules)
{
  int options = MATCHnone;
  for_each( MatchRule, r, rules)
  {
    
#line 1003 "../../prop-src/matchgen.pcc"
#line 1010 "../../prop-src/matchgen.pcc"
{
  if (r->_4) {
    if (r->_4->tag__) {
      
#line 1006 "../../prop-src/matchgen.pcc"
     options |= MATCHwithcost | MATCHwithintcost; 
#line 1006 "../../prop-src/matchgen.pcc"
    } else {
      
#line 1008 "../../prop-src/matchgen.pcc"
     options |= MATCHwithcost | MATCHwithexpcost; 
#line 1008 "../../prop-src/matchgen.pcc"
    }
  } else {}
}
#line 1010 "../../prop-src/matchgen.pcc"
#line 1010 "../../prop-src/matchgen.pcc"

  }
  return options;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to check for refutable set of rules and print out
//  warning/error messages.
//
///////////////////////////////////////////////////////////////////////////////
static Bool check_refutable
   (Match m, MatchRules rules, MatchOptions match_options)
{
  Bool is_refutable = refutable(m);            // error checking
  if (! (match_options & MATCHnocheck) &&
      ! (match_options & MATCHwhile) && is_refutable)
  {
    msg( "%!%wpatterns are not exhaustive:\n", rules->_1->loc());
    for_each( MatchRule, r, rules)
      msg( "%!\t%r\n", r->loc(), r);
  }
  return is_refutable;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Compile a match/matchall statement.
//
///////////////////////////////////////////////////////////////////////////////

void MatchCompiler::gen_match_stmt
   (MatchExps exps, MatchRules rules, MatchOptions match_options, Ty match_ty)
{
  MemPoolMark marker = mem_pool.getMark();     // set heap marker
  int n              = length(rules);
  Ty pattern_tys     = type_match_rules(rules);    // type inference
  Id save_failure    = current_failure;
  current_failure    = 0;
  MatchOptions save  = current_options;
  current_options    = match_options;

  if (pattern_tys != NOty)
  {
    pr( "%^{\n%+");
    if (match_options & MATCHwhile)
    {
      pr( "%^for (;;) {%+");
      current_failure = labels.new_label();
    }

    // check for cost expressions
    int cost_opts = involve_cost(rules);
    if (cost_opts & MATCHwithcost)
    {
      if (match_options & MATCHall)
        if (! (match_options & MATCHwithtreecost))
          msg ("%L%wmatching costs are ignored.\n");
        else
          match_options |= cost_opts;
    }

    Match m = match_of( n, rules, match_options); // compile patterns
    Bool is_refutable = check_refutable( m, rules, match_options);

    // prefix code for matchall

    if ((match_options & (MATCHall | MATCHwithcost)) &&
        ! (match_options & MATCHwithtreecost))
      pr( "%^const unsigned char * m__%s;\n", (is_refutable ? " = 0" : ""));

    gen_match_variables( exps, pattern_tys);
    gen( m, match_options, match_ty);

    // suffix code for cost minimization

    if (! (match_options & MATCHwithtreecost))
    {
      if (match_options & MATCHwithexpcost)
        gen_match_cost_minimization( n, m, rules, is_refutable);
      // suffix code for matchall
      else if (match_options & MATCHall)
        gen_matchall_suffix( n, m, rules, is_refutable);
    }

    if (match_options & MATCHwhile)
    {
      pr( "%-%^}");
      if (is_refutable)
        pr( "%^%s:;", current_failure);
    }
    pr( "%-%^}");
  }
  mem_pool.setMark( marker); // release all memory used
  current_failure = save_failure;
  current_options = save;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Generate suffix code for a matchall statement.
//  The suffix code goes thru the bitmap and select all rule with
//  its bit set.
//
///////////////////////////////////////////////////////////////////////////////

void MatchCompiler::gen_matchall_suffix
   (int n, Match m, MatchRules rules, Bool is_refutable)
{  int index = 0; int bit = 0;
   const BitSet& always_match = always_matchables(m,n);
   if (is_refutable) { ifs++; pr ("%^if (m__) {%+"); }

   for_each (MatchRule, r, rules)
   {  
#line 1123 "../../prop-src/matchgen.pcc"
#line 1134 "../../prop-src/matchgen.pcc"
{
#line 1125 "../../prop-src/matchgen.pcc"
if (! always_match.contains(index * 8 + bit)) {
  ifs++;
  pr ("%^if (m__[%i] & %i) ", index, 1 << bit);
  } else {
  pr ("%^");
  }
  	    MarkCurrentRule mark(current_rule,r);
  pr ("{%+%&%-%?}\n", r->_5);
  if (++bit == 8) { bit = 0; index++; }
  
#line 1134 "../../prop-src/matchgen.pcc"
}
#line 1135 "../../prop-src/matchgen.pcc"
#line 1135 "../../prop-src/matchgen.pcc"

   }
   if (is_refutable) pr ("%-%^}");
}

///////////////////////////////////////////////////////////////////////////////
//
//  Generate suffix code for a match statement with cost minimization.
//  The bitmap selected with determine which cost function to execute.
//  When all the appropriate cost functions are executed, we choose the
//  matched rule with the lowest cost.  Ties are broken by the lexical
//  order of the rules.
//
///////////////////////////////////////////////////////////////////////////////

void MatchCompiler::gen_match_cost_minimization
   (int n, Match m, MatchRules rules, Bool is_refutable)
{
  int index, bit;
  const BitSet& always_match = always_matchables(m,n);

  pr( "%^do {%+"
      "%^int tmp_cost__, cost__ = %i, rule__ = -1;", MAX_COST);
  if (is_refutable)
  {
    ifs++;
    pr ("%^if (m__) {%+");
  }
  {
    index = bit = 0;
    for_each ( MatchRule, r, rules)
    {
      pr( "%^");
      if (! always_match.contains(index * 8 + bit))
      {
        ifs++;
        pr( "if (m__[%i] & %i) ", index, 1 << bit);
      }
      int rule_no = index * 8 + bit;
      
#line 1174 "../../prop-src/matchgen.pcc"
#line 1184 "../../prop-src/matchgen.pcc"
{
  if (r->_4) {
    if (r->_4->tag__) {
      
#line 1184 "../../prop-src/matchgen.pcc"
    pr ("if (cost__ > %i) { cost__ = %i; rule__ = %i; }", _INTcost(r->_4)->INTcost, _INTcost(r->_4)->INTcost, rule_no); 
#line 1184 "../../prop-src/matchgen.pcc"
    } else {
      
#line 1177 "../../prop-src/matchgen.pcc"
      
      pr( "if ((tmp_cost__ = %e) < cost__) { cost__ = tmp_cost__; rule_ = %i; }",
            _EXPcost(r->_4)->_1, rule_no);
      
#line 1180 "../../prop-src/matchgen.pcc"
    }
  } else {
#line 1182 "../../prop-src/matchgen.pcc"
  pr ("{ rule__ = %i; break; }", rule_no);  
#line 1182 "../../prop-src/matchgen.pcc"
  }
}
#line 1185 "../../prop-src/matchgen.pcc"
#line 1185 "../../prop-src/matchgen.pcc"

      if (++bit == 8)
        { bit = 0; index++; }
    }
  }
  if (is_refutable)
    pr( "%-%^}");
  pr(
      "%-%^} while (0);"
      "%^switch (rule__) {%+"
    );
  {
    int i = 0;
    for_each ( MatchRule, r, rules)
    {
      
#line 1200 "../../prop-src/matchgen.pcc"
#line 1207 "../../prop-src/matchgen.pcc"
{
#line 1203 "../../prop-src/matchgen.pcc"
  
  MarkCurrentRule mark( current_rule, r);
  pr( "%^case %i: {%+%&%-%?} break;", i, r->_5);
  i++;
  
#line 1207 "../../prop-src/matchgen.pcc"
}
#line 1208 "../../prop-src/matchgen.pcc"
#line 1208 "../../prop-src/matchgen.pcc"

    }
  }
  pr( "%-%^}");
}

///////////////////////////////////////////////////////////////////////////////
//
//  Generate code that binds match variables.
//
///////////////////////////////////////////////////////////////////////////////

void MatchCompiler::gen_match_variables( MatchExps es, Ty ty)
{  Tys tys;
   if (length(es) > 1) {
      
#line 1223 "../../prop-src/matchgen.pcc"
#line 1225 "../../prop-src/matchgen.pcc"
{
  Ty _V8 = deref(ty);
  if (_V8) {
    switch (_V8->tag__) {
      case a_Ty::tag_TYCONty: {
        if (boxed(_TYCONty(_V8)->_1)) {
          L8:; 
#line 1225 "../../prop-src/matchgen.pcc"
         bug("gen_match_variables()"); 
#line 1225 "../../prop-src/matchgen.pcc"
        } else {
          switch ((int)_TYCONty(_V8)->_1) {
            case ((int)TUPLEtycon): {
#line 1224 "../../prop-src/matchgen.pcc"
             tys = _TYCONty(_V8)->_2; 
#line 1224 "../../prop-src/matchgen.pcc"
              } break;
            default: { goto L8; } break;
          }
        }
        } break;
      default: { goto L8; } break;
    }
  } else { goto L8; }
}
#line 1226 "../../prop-src/matchgen.pcc"
#line 1226 "../../prop-src/matchgen.pcc"

   } else {
      tys = 
#line 1228 "../../prop-src/matchgen.pcc"
#line 1228 "../../prop-src/matchgen.pcc"
list_1_(ty)
#line 1228 "../../prop-src/matchgen.pcc"
#line 1228 "../../prop-src/matchgen.pcc"
;
   }
   for ( ; es && tys; es = es->_2, tys = tys->_2) {
      
#line 1231 "../../prop-src/matchgen.pcc"
#line 1238 "../../prop-src/matchgen.pcc"
{
  MatchExp _V9 = es->_1;
  if (
#line 1232 "../../prop-src/matchgen.pcc"
  (_V9->_2 != 0)
#line 1232 "../../prop-src/matchgen.pcc"
) {
    
#line 1233 "../../prop-src/matchgen.pcc"
  if (! is_ground(tys->_1))
    error ("%!missing type info in expression %e : %T\n",
           _V9->loc(), _V9->_1, tys->_1);
    pr ("%^%t = %e;\n", tys->_1, _V9->_2, _V9->_1);
    
#line 1237 "../../prop-src/matchgen.pcc"
  } else {
    
#line 1238 "../../prop-src/matchgen.pcc"
   /* skip */ 
#line 1238 "../../prop-src/matchgen.pcc"
  }
}
#line 1239 "../../prop-src/matchgen.pcc"
#line 1239 "../../prop-src/matchgen.pcc"

   }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Generate code for a set of function definitions.
//
///////////////////////////////////////////////////////////////////////////////

void MatchCompiler::gen_fun_def (FunDefs fundefs)
{
  // Generate the prototype first (to deal with recursive definitions).
  MemPoolMark marker = mem_pool.getMark();     // set heap marker
  {
    for_each (FunDef, f, fundefs)
    {
      
#line 1256 "../../prop-src/matchgen.pcc"
#line 1271 "../../prop-src/matchgen.pcc"
{
#line 1259 "../../prop-src/matchgen.pcc"
  
  f->_2 = type_match_rules(f->_4);
  char buf[1024];
  std::ostrstream b(buf,sizeof(buf));
  std::ostream& s = b;
  s << f->_1 << std::ends;
  Ty ret_ty = f->_3 == NOty ? void_ty : f->_3;
  pr( "%^%t %b;\n",
      ret_ty, buf, f->_2, "1", TYformal);
  if (! is_ground(f->_2))
    error( "%!missing type info in function %q %T\n",
           f->loc(), f->_1, f->_2);
  
#line 1271 "../../prop-src/matchgen.pcc"
}
#line 1272 "../../prop-src/matchgen.pcc"
#line 1272 "../../prop-src/matchgen.pcc"

    }
  }

  // Then generate the body of the functions.
  {
    for_each (FunDef, f, fundefs)
    {
      
#line 1280 "../../prop-src/matchgen.pcc"
#line 1296 "../../prop-src/matchgen.pcc"
{
#line 1283 "../../prop-src/matchgen.pcc"
  
  int n = length(f->_4);
  Match m = match_of(n, f->_4, MATCHnone);
  check_refutable(m, f->_4, MATCHnone);
  Ty ret_ty = f->_3 == NOty ? void_ty : f->_3;
  char buf[1024];
  std::ostrstream b(buf,sizeof(buf));
  std::ostream& s = b;
  s << f->_1 << std::ends;
  pr( "%^%t %b\n{\n%+",
      ret_ty, buf, f->_2, "1", TYformal);
  gen(m);
  pr( "%-%^}\n");
  
#line 1296 "../../prop-src/matchgen.pcc"
}
#line 1297 "../../prop-src/matchgen.pcc"
#line 1297 "../../prop-src/matchgen.pcc"

    }
  }
  mem_pool.setMark( marker); // release all memory used
}
#line 1302 "../../prop-src/matchgen.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 147
Number of ifs generated      = 23
Number of switches generated = 14
Number of labels             = 4
Number of gotos              = 12
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
