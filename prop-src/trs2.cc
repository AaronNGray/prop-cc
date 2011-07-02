///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.4.0),
//  last updated on Jul 1, 2011.
//  The original source file is "..\..\prop-src\trs2.pcc".
///////////////////////////////////////////////////////////////////////////////

#define PROP_STRCMP_USED
#define PROP_TUPLE2_USED
#include <propdefs.h>
#line 1 "../../prop-src/trs2.pcc"
///////////////////////////////////////////////////////////////////////////////
//
//  This is the main partial evaluation routines.
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <stdlib.h>
#include "trs.h"
#include "ir.h"
#include "ast.h"
#include "type.h"
#include "list.h"
#include "matchcom.h"
#include "funmap.h"
#include "rwgen.h"


///////////////////////////////////////////////////////////////////////////////
//
//  Type definitions
//
///////////////////////////////////////////////////////////////////////////////

typedef TreeAutomaton::Functor Functor;
typedef TreeAutomaton::State   State;
typedef TreeAutomaton::Rule    Rule;

///////////////////////////////////////////////////////////////////////////////
//
//  Method for partial evaluating the trs
//
///////////////////////////////////////////////////////////////////////////////

void TRS::mix()
{
  for (Rule r = 0; r < number_of_rules; r++)
    mix(r);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method for partial evaluating one rule
//
///////////////////////////////////////////////////////////////////////////////

void TRS::mix( Rule r)
{
  mix_0(r);
  mix_1(r);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method for partial evaluting one rule, using 0-strategy.
//
///////////////////////////////////////////////////////////////////////////////

void TRS::mix_0( Rule r)
{
  int arity = num_var_map[r];
  for (int i = 0; i < arity; i++)
    states[i] = 0;
  // msg("0-Partial evaluating %r ", rule_map[r]) << rhs_map[r] << '\n';
  Term rhs = copy( rhs_map[r]);
  int reductions = 0;
  State new_state = normalize( rhs, reductions);
  if (reductions > 0)
  {
    print_residue( r, rhs);
    make_rhs( r, optimized_map[r] = make_exp(rhs));
  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method for partial evaluting one rule, using 1-strategy.
//
///////////////////////////////////////////////////////////////////////////////

void TRS::mix_1( Rule r)
{
  int arity            = num_var_map[r];
  int number_of_states = treeauto.number_of_states();
  // msg("1-Partial evaluating %r ", rule_map[r]) << rhs_map[r] << '\n';
  for (int i = 0; i < arity; i++)
  {
    // If the variable does not have an index we can't do anything with it.

    if ( !compiler.has_index( var_pat_map[r][i]->ty))
      continue;
    for (int j = 0; j < arity; j++)
      states[j] = 0;
    for (State s = 1; s < number_of_states; s++)
    {  // skip accept states
       states[i] = s;
       if (treeauto.is_accept_state(s))
         continue;
       if (! is_relevant(r))
         continue;
       int reductions = 0;
       Term rhs = copy(rhs_map[r]);
       State new_state = normalize(rhs,reductions);
       if (reductions > 0)
	      generate_residue(r,i,s,rhs);
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to check that a particular specialization is relevant
//
///////////////////////////////////////////////////////////////////////////////

Bool TRS::is_relevant( Rule r)
{
  int redex_count = 0;
  count_redex = true;
  State s = normalize(lhs_map[r],redex_count);
  count_redex = false;
  // std::cerr << lhs_map[r] << " has " << redex_count << " redexes\n";
  if (redex_count > 1)
    return false;
  if (treeauto.accept1_rule(s) != r)
    return false;
  return true;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to normalize a rule
//
///////////////////////////////////////////////////////////////////////////////

TRS::State TRS::normalize( Term& term, int& reductions)
{
  Bool changed;
  State new_state;
  do
  {
    changed = false;
    
#line 144 "../../prop-src/trs2.pcc"
#line 168 "../../prop-src/trs2.pcc"
{
  switch (term->tag__) {
    case a_Term::tag_CONSterm: {
#line 147 "../../prop-src/trs2.pcc"
      
      int mu[MAX_VARS];
      
      for (int i = 0; i < _CONSterm(term)->_3; i++)
      {
        State s = normalize( _CONSterm(term)->_4[i], reductions);
        mu[i]   = treeauto.index_map( _CONSterm(term)->_1, i, s);
      }
      new_state = treeauto.get_delta( _CONSterm(term)->_1, mu);
      // Check for redex
      if (treeauto.is_accept_state( new_state))
      {
        if (count_redex)
        {
      		    reductions++;
      		    return new_state;
        }
      	      term = reduce( term, new_state, reductions, changed);
      }
      
#line 166 "../../prop-src/trs2.pcc"
      } break;
    case a_Term::tag_VARterm: {
#line 167 "../../prop-src/trs2.pcc"
     return states[_VARterm(term)->_1]; 
#line 167 "../../prop-src/trs2.pcc"
      } break;
    default: {
#line 168 "../../prop-src/trs2.pcc"
     return 0; 
#line 168 "../../prop-src/trs2.pcc"
      } break;
  }
}
#line 169 "../../prop-src/trs2.pcc"
#line 169 "../../prop-src/trs2.pcc"

  } while (changed);
  return new_state;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to reduce a rule during accepting
//
///////////////////////////////////////////////////////////////////////////////

Term TRS::reduce( Term term, State state, int& reductions, Bool& changed)
{
  // Test for conditional rules
  // For each rule that can accept, check the guard associated
  // with the rule.  Evaluate the guard if possible.
  // We'll not reduce if we are not guaranteed that the reduction
  // can be performed.

  const BitSet& accept = treeauto.accept_rules(state);
  for (Rule r = 0; r <= number_of_rules; r++)
  {
    if (accept[r])
    {
      Exp guard = guard_map[r];
      EvalResult result = SUCCESS;
      if (guard == NOexp)
        result = SUCCESS;
      else
        result = eval_guard(guard);
      switch (result)
      {
      case SUCCESS:
        {
          Term rule_rhs = rhs_map[r];
          Bool ok = true;
          Term new_rhs = subst(rule_rhs,term,ok);
          if (! ok)
            return term; // no reduction
          reductions++;
          changed = true;
          return new_rhs;
        }
      case UNKNOWN: return term; // no reduction
      case FAILURE:  break; // try next rule
      }
    }
  }
  return term;  // no reduction
}

///////////////////////////////////////////////////////////////////////////////
//
//  Apply a rule
//
///////////////////////////////////////////////////////////////////////////////

Term TRS::subst( Term rhs, Term redex, Bool& ok)
{
  
#line 228 "../../prop-src/trs2.pcc"
#line 236 "../../prop-src/trs2.pcc"
{
  switch (rhs->tag__) {
    case a_Term::tag_CONSterm: {
#line 231 "../../prop-src/trs2.pcc"
    return CONSterm( _CONSterm(rhs)->_1, _CONSterm(rhs)->_2, _CONSterm(rhs)->_3, subst( _CONSterm(rhs)->_3, _CONSterm(rhs)->_4, redex, ok)); 
#line 231 "../../prop-src/trs2.pcc"
      } break;
    case a_Term::tag_VARterm: {
#line 233 "../../prop-src/trs2.pcc"
    return proj( _VARterm(rhs)->_3, redex, ok); 
#line 233 "../../prop-src/trs2.pcc"
      } break;
    case a_Term::tag_CODEterm: {
#line 235 "../../prop-src/trs2.pcc"
    return proj( _CODEterm(rhs)->CODEterm, redex, ok); 
#line 235 "../../prop-src/trs2.pcc"
      } break;
    default: {
#line 236 "../../prop-src/trs2.pcc"
     bug("TRS::subst"); return redex; 
#line 236 "../../prop-src/trs2.pcc"
      } break;
  }
}
#line 237 "../../prop-src/trs2.pcc"
#line 237 "../../prop-src/trs2.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Apply a rule
//
///////////////////////////////////////////////////////////////////////////////

Term * TRS::subst( int n, Term * rhs, Term redex, Bool& ok)
{
  Term * args = (Term*)mem_pool.m_alloc(sizeof(Term) * n);
  for (int i = 0; i < n; i++)
    args[i] = subst( rhs[i], redex, ok);
  return args;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Perform projection a rule
//
///////////////////////////////////////////////////////////////////////////////

Term TRS::proj( Exp exp, Term redex, Bool& ok)
{
  int nth;
  
#line 263 "../../prop-src/trs2.pcc"
#line 312 "../../prop-src/trs2.pcc"
{
  if (exp) {
    switch (exp->tag__) {
      case a_Exp::tag_IDexp: {
        if (_equal_string(_IDexp(exp)->IDexp,"redex")) {
#line 265 "../../prop-src/trs2.pcc"
       return redex; 
#line 265 "../../prop-src/trs2.pcc"
}
        else {
        L1:; 
#line 308 "../../prop-src/trs2.pcc"
      // msg("3 Can't project %e ", exp);
        	  // print(msg(""),redex); msg("\n");
        	  ok = false;
              return CODEterm(NOexp);
            
#line 312 "../../prop-src/trs2.pcc"
}
        } break;
      case a_Exp::tag_DOTexp: {
        if (_DOTexp(exp)->_1) {
          switch (_DOTexp(exp)->_1->tag__) {
            case a_Exp::tag_SELECTORexp: {
#line 267 "../../prop-src/trs2.pcc"
              
              
#line 268 "../../prop-src/trs2.pcc"
#line 288 "../../prop-src/trs2.pcc"
              {
                Term _V1 = proj(_SELECTORexp(_DOTexp(exp)->_1)->_1,redex,ok);
                switch (_V1->tag__) {
                  case a_Term::tag_CONSterm: {
                    if (
#line 270 "../../prop-src/trs2.pcc"
                    ((_SELECTORexp(_DOTexp(exp)->_1)->_2 == _CONSterm(_V1)->_2) && (nth = (atol((_DOTexp(exp)->_2 + 1)) - 1)),(nth < _CONSterm(_V1)->_3))
#line 271 "../../prop-src/trs2.pcc"
) {
                      
#line 272 "../../prop-src/trs2.pcc"
                    return _CONSterm(_V1)->_4[nth]; 
#line 272 "../../prop-src/trs2.pcc"
                    } else {
                      
#line 278 "../../prop-src/trs2.pcc"
                    // msg("1 Can't project %e %i %i", exp,nth,n);
                      	      // print(msg(""),redex); msg("\n");
                      	      ok = false;
                                return _V1;
                              
#line 282 "../../prop-src/trs2.pcc"
                    }
                    } break;
                  case a_Term::tag_VARterm: {
#line 276 "../../prop-src/trs2.pcc"
                   return CODEterm( DOTexp( SELECTORexp( _VARterm(_V1)->_3, _SELECTORexp(_DOTexp(exp)->_1)->_2, _SELECTORexp(_DOTexp(exp)->_1)->_3), _DOTexp(exp)->_2)); 
#line 276 "../../prop-src/trs2.pcc"
                    } break;
                  case a_Term::tag_CODEterm: {
#line 274 "../../prop-src/trs2.pcc"
                   return CODEterm( DOTexp( SELECTORexp( _CODEterm(_V1)->CODEterm, _SELECTORexp(_DOTexp(exp)->_1)->_2, _SELECTORexp(_DOTexp(exp)->_1)->_3), _DOTexp(exp)->_2)); 
#line 274 "../../prop-src/trs2.pcc"
                    } break;
                  default: {
#line 284 "../../prop-src/trs2.pcc"
                  // msg("1 Can't project %e", exp);
                    	      // print(msg(""),redex); msg("\n");
                    	      ok = false;
                              return redex;
                    	    
#line 288 "../../prop-src/trs2.pcc"
                    } break;
                }
              }
#line 289 "../../prop-src/trs2.pcc"
#line 289 "../../prop-src/trs2.pcc"
              
              
#line 290 "../../prop-src/trs2.pcc"
              } break;
            default: { goto L1; } break;
          }
        } else { goto L1; }
        } break;
      case a_Exp::tag_SELECTORexp: {
#line 292 "../../prop-src/trs2.pcc"
        
        
#line 293 "../../prop-src/trs2.pcc"
#line 304 "../../prop-src/trs2.pcc"
        {
          Term _V2 = proj(_SELECTORexp(exp)->_1,redex,ok);
          switch (_V2->tag__) {
            case a_Term::tag_CONSterm: {
              if (
#line 295 "../../prop-src/trs2.pcc"
              (_SELECTORexp(exp)->_2 == _CONSterm(_V2)->_2)
#line 295 "../../prop-src/trs2.pcc"
) {
                
#line 296 "../../prop-src/trs2.pcc"
              return _CONSterm(_V2)->_4[0]; 
#line 296 "../../prop-src/trs2.pcc"
              } else {
                
                L2:; 
#line 300 "../../prop-src/trs2.pcc"
              // msg("2 Can't project %e ", exp);
                	    // print(msg(""),redex); msg("\n");
                	      ok = false;
                          return _V2;
                        
#line 304 "../../prop-src/trs2.pcc"
              }
              } break;
            case a_Term::tag_VARterm: {
#line 298 "../../prop-src/trs2.pcc"
             return CODEterm(SELECTORexp(_VARterm(_V2)->_3,_SELECTORexp(exp)->_2,_SELECTORexp(exp)->_3)); 
#line 298 "../../prop-src/trs2.pcc"
              } break;
            case a_Term::tag_CODEterm: {
#line 297 "../../prop-src/trs2.pcc"
             return CODEterm(SELECTORexp(_CODEterm(_V2)->CODEterm,_SELECTORexp(exp)->_2,_SELECTORexp(exp)->_3)); 
#line 297 "../../prop-src/trs2.pcc"
              } break;
            default: { goto L2; } break;
          }
        }
#line 305 "../../prop-src/trs2.pcc"
#line 305 "../../prop-src/trs2.pcc"
        
        
#line 306 "../../prop-src/trs2.pcc"
        } break;
      default: { goto L1; } break;
    }
  } else { goto L1; }
}
#line 313 "../../prop-src/trs2.pcc"
#line 313 "../../prop-src/trs2.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Compose two projection expression
//
///////////////////////////////////////////////////////////////////////////////

Exp TRS::proj( Exp e1, Exp e2, Bool& ok)
{
  
#line 324 "../../prop-src/trs2.pcc"
#line 329 "../../prop-src/trs2.pcc"
{
  if (e1) {
    switch (e1->tag__) {
      case a_Exp::tag_IDexp: {
        if (_equal_string(_IDexp(e1)->IDexp,"redex")) {
#line 326 "../../prop-src/trs2.pcc"
       return e2; 
#line 326 "../../prop-src/trs2.pcc"
}
        else {
        L3:; 
#line 329 "../../prop-src/trs2.pcc"
       msg("Can't project %e %e\n", e1, e2);  return NOexp; 
#line 329 "../../prop-src/trs2.pcc"
}
        } break;
      case a_Exp::tag_DOTexp: {
#line 328 "../../prop-src/trs2.pcc"
       return DOTexp(proj( _DOTexp(e1)->_1, e2, ok), _DOTexp(e1)->_2); 
#line 328 "../../prop-src/trs2.pcc"
        } break;
      case a_Exp::tag_SELECTORexp: {
#line 327 "../../prop-src/trs2.pcc"
       return SELECTORexp(proj( _SELECTORexp(e1)->_1, e2, ok), _SELECTORexp(e1)->_2, _SELECTORexp(e1)->_3); 
#line 327 "../../prop-src/trs2.pcc"
        } break;
      default: { goto L3; } break;
    }
  } else { goto L3; }
}
#line 330 "../../prop-src/trs2.pcc"
#line 330 "../../prop-src/trs2.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Copying the rhs
//
///////////////////////////////////////////////////////////////////////////////

Term TRS::copy( Term rhs)
{
  
#line 341 "../../prop-src/trs2.pcc"
#line 345 "../../prop-src/trs2.pcc"
{
  switch (rhs->tag__) {
    case a_Term::tag_CONSterm: {
#line 344 "../../prop-src/trs2.pcc"
     return CONSterm( _CONSterm(rhs)->_1, _CONSterm(rhs)->_2, _CONSterm(rhs)->_3, copy( _CONSterm(rhs)->_3, _CONSterm(rhs)->_4)); 
#line 344 "../../prop-src/trs2.pcc"
      } break;
    default: {
#line 345 "../../prop-src/trs2.pcc"
     return rhs; 
#line 345 "../../prop-src/trs2.pcc"
      } break;
  }
}
#line 346 "../../prop-src/trs2.pcc"
#line 346 "../../prop-src/trs2.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Copying the rhs
//
///////////////////////////////////////////////////////////////////////////////

Term * TRS::copy( int n, Term rhs [])
{
  Term * args = (Term*)mem_pool.m_alloc( sizeof( Term) * n);
  for (int i = 0; i < n; i++)
    args[i] = copy( rhs[i]);
  return args;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to evaluate a guard expression
//
///////////////////////////////////////////////////////////////////////////////

TRS::EvalResult TRS::eval_guard(Exp exp)
{
  return UNKNOWN;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to print out the residue.
//
///////////////////////////////////////////////////////////////////////////////

void TRS::print_residue( Rule r, Term rhs_residue) const
{
  std::ostream& log = open_logfile();
  MatchRule rule = rule_map[r];

  log << "line " << rule->begin_line << ": "
      << rule_map[r] << ' ';

  print(log, rhs_map[r]); log << '\n';

  for (int i = 0; i < num_var_map[r]; i++)
  {
    if (states[i] != 0)
    {
      log << "\twhen " << var_pat_map[r][i] << " is in state:\n";
      treeauto.print_state( log, states[i]);
    }
  }
  log << "\toptimize rhs to ";
  print( log, rhs_residue);
  log << "\n\n";
}
#line 402 "../../prop-src/trs2.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 121
Number of ifs generated      = 7
Number of switches generated = 8
Number of labels             = 3
Number of gotos              = 7
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
