///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.4.0),
//  last updated on Jul 1, 2011.
//  The original source file is "..\..\prop-src\pat.pcc".
///////////////////////////////////////////////////////////////////////////////

#line 1 "../../prop-src/pat.pcc"
///////////////////////////////////////////////////////////////////////////////
//
//  This file implements the analysis routines for patterns and match
//  decision trees.  These are used for mode analysis and determinism
//  analysis for logic clauses compilation.
//
///////////////////////////////////////////////////////////////////////////////

#include "ir.h"
#include "matchcom.h"
#include "pat.h"

///////////////////////////////////////////////////////////////////////////////
//
//  Convert a pattern into an unifier if the constructor is part of
//  an unifiable type.
//
///////////////////////////////////////////////////////////////////////////////

Pat mkunifier( Cons cons, Pat pat, Pat transformed_pat)
{
  
#line 22 "../../prop-src/pat.pcc"
#line 36 "../../prop-src/pat.pcc"
{
  if (cons) {
    if (cons->alg_ty) {
      switch (cons->alg_ty->tag__) {
        case a_Ty::tag_TYCONty: {
          if (boxed(_TYCONty(cons->alg_ty)->_1)) {
            switch (_TYCONty(cons->alg_ty)->_1->tag__) {
              case a_TyCon::tag_DATATYPEtycon: {
                if (
#line 25 "../../prop-src/pat.pcc"
                (_DATATYPEtycon(_TYCONty(cons->alg_ty)->_1)->qualifiers & QUALunifiable)
#line 25 "../../prop-src/pat.pcc"
) {
                  
#line 26 "../../prop-src/pat.pcc"
                  
                  Cons unifier_cons = _DATATYPEtycon(_TYCONty(cons->alg_ty)->_1)->terms[_DATATYPEtycon(_TYCONty(cons->alg_ty)->_1)->unit];
                  Bool mode_save = write_mode;
                  write_mode = true;
                  Pat new_p = LOGICALpat( ORpat, transformed_pat,
                                    UNIFYpat( APPpat( CONSpat( unifier_cons), WILDpat()),
                                                pat2unifier( pat)));
                  write_mode = mode_save;
                  return new_p;
                  
#line 35 "../../prop-src/pat.pcc"
                } else {
                  
                  L1:; 
#line 36 "../../prop-src/pat.pcc"
                 return pat; 
#line 36 "../../prop-src/pat.pcc"
                }
                } break;
              default: { goto L1; } break;
            }
          } else { goto L1; }
          } break;
        default: { goto L1; } break;
      }
    } else { goto L1; }
  } else { goto L1; }
}
#line 37 "../../prop-src/pat.pcc"
#line 37 "../../prop-src/pat.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Convert a simple pattern into an unifier.
//
///////////////////////////////////////////////////////////////////////////////

Pat unifier_of( Pat pat)
{
  Pat new_p = pat;
  
#line 49 "../../prop-src/pat.pcc"
#line 87 "../../prop-src/pat.pcc"
{
  if (pat) {
    switch (pat->tag__) {
      case a_Pat::tag_CONSpat: {
#line 53 "../../prop-src/pat.pcc"
       new_p = mkunifier( _CONSpat(pat)->CONSpat, pat, pat); 
#line 53 "../../prop-src/pat.pcc"
        } break;
      case a_Pat::tag_APPpat: {
        if (_APPpat(pat)->_1) {
          switch (_APPpat(pat)->_1->tag__) {
            case a_Pat::tag_CONSpat: {
#line 55 "../../prop-src/pat.pcc"
             new_p = mkunifier( _CONSpat(_APPpat(pat)->_1)->CONSpat, pat, APPpat( _APPpat(pat)->_1, unifier_of(_APPpat(pat)->_2))); 
#line 55 "../../prop-src/pat.pcc"
              } break;
            default: {
              L2:; 
#line 87 "../../prop-src/pat.pcc"
             bug ("%Lunsupported unifier: %p", pat); 
#line 87 "../../prop-src/pat.pcc"
              } break;
          }
        } else { goto L2; }
        } break;
      case a_Pat::tag_TYPEDpat: {
#line 56 "../../prop-src/pat.pcc"
       new_p = TYPEDpat( unifier_of(_TYPEDpat(pat)->_1),_TYPEDpat(pat)->_2); 
#line 56 "../../prop-src/pat.pcc"
        } break;
      case a_Pat::tag_ASpat: {
#line 57 "../../prop-src/pat.pcc"
       new_p = ASpat( _ASpat(pat)->_1, unifier_of(_ASpat(pat)->_2),_ASpat(pat)->_3,_ASpat(pat)->_4); 
#line 57 "../../prop-src/pat.pcc"
        } break;
      case a_Pat::tag_ARRAYpat: {
#line 58 "../../prop-src/pat.pcc"
       new_p = ARRAYpat( unifier_of( _ARRAYpat(pat)->_1), _ARRAYpat(pat)->_2); 
#line 58 "../../prop-src/pat.pcc"
        } break;
      case a_Pat::tag_TUPLEpat: {
#line 59 "../../prop-src/pat.pcc"
       new_p = TUPLEpat( unifier_of( _TUPLEpat(pat)->TUPLEpat)); 
#line 59 "../../prop-src/pat.pcc"
        } break;
      case a_Pat::tag_EXTUPLEpat: {
#line 60 "../../prop-src/pat.pcc"
       new_p = EXTUPLEpat( unifier_of( _EXTUPLEpat(pat)->EXTUPLEpat)); 
#line 60 "../../prop-src/pat.pcc"
        } break;
      case a_Pat::tag_RECORDpat: {
#line 61 "../../prop-src/pat.pcc"
       new_p = RECORDpat( unifier_of(_RECORDpat(pat)->_1), _RECORDpat(pat)->_2); 
#line 61 "../../prop-src/pat.pcc"
        } break;
      case a_Pat::tag_LISTpat: {
#line 64 "../../prop-src/pat.pcc"
        
        new_p = 
#line 65 "../../prop-src/pat.pcc"
#line 65 "../../prop-src/pat.pcc"
        LISTpat(_LISTpat(pat)->cons, _LISTpat(pat)->nil, unifier_of(_LISTpat(pat)->head), unifier_of(_LISTpat(pat)->tail))
#line 70 "../../prop-src/pat.pcc"
#line 70 "../../prop-src/pat.pcc"
        ;
        
#line 71 "../../prop-src/pat.pcc"
        } break;
      case a_Pat::tag_VECTORpat: {
#line 73 "../../prop-src/pat.pcc"
        
        new_p = 
#line 74 "../../prop-src/pat.pcc"
#line 74 "../../prop-src/pat.pcc"
        VECTORpat(_VECTORpat(pat)->cons, unifier_of(_VECTORpat(pat)->len), unifier_of(_VECTORpat(pat)->array), unifier_of(_VECTORpat(pat)->elements), _VECTORpat(pat)->head_flex, _VECTORpat(pat)->tail_flex)
#line 82 "../../prop-src/pat.pcc"
#line 82 "../../prop-src/pat.pcc"
        ;
        
#line 83 "../../prop-src/pat.pcc"
        } break;
      case a_Pat::tag_GUARDpat: {
#line 62 "../../prop-src/pat.pcc"
       new_p = GUARDpat( unifier_of(_GUARDpat(pat)->_1), _GUARDpat(pat)->_2); 
#line 62 "../../prop-src/pat.pcc"
        } break;
      case a_Pat::tag_LOGICALpat: {
#line 85 "../../prop-src/pat.pcc"
       new_p = LOGICALpat(_LOGICALpat(pat)->_1,unifier_of(_LOGICALpat(pat)->_2),unifier_of(_LOGICALpat(pat)->_3)); 
#line 85 "../../prop-src/pat.pcc"
        } break;
      case a_Pat::tag_MARKEDpat: {
#line 86 "../../prop-src/pat.pcc"
       new_p = MARKEDpat(_MARKEDpat(pat)->_1, unifier_of(_MARKEDpat(pat)->_2)); 
#line 86 "../../prop-src/pat.pcc"
        } break;
      case a_Pat::tag_WILDpat:
      case a_Pat::tag_IDpat:
      case a_Pat::tag_LITERALpat:
      case a_Pat::tag_CONTEXTpat:
      case a_Pat::tag_LEXEMEpat: {
        L3:; } break;
      default: { goto L2; } break;
    }
  } else { goto L3; }
}
#line 88 "../../prop-src/pat.pcc"
#line 88 "../../prop-src/pat.pcc"

  if (new_p != pat && boxed(pat) && boxed(new_p))
  {
    new_p->selector = pat->selector;
    new_p->ty       = pat->ty;
  }
  return new_p;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Convert a simple pattern list into an unifier list.
//
///////////////////////////////////////////////////////////////////////////////

Pats unifier_of( Pats pats)
{
  
#line 105 "../../prop-src/pat.pcc"
#line 108 "../../prop-src/pat.pcc"
{
  if (pats) {
#line 108 "../../prop-src/pat.pcc"
   return 
#line 108 "../../prop-src/pat.pcc"
#line 108 "../../prop-src/pat.pcc"
    list_1_(unifier_of(pats->_1),unifier_of(pats->_2))
#line 108 "../../prop-src/pat.pcc"
#line 108 "../../prop-src/pat.pcc"
    ; 
#line 108 "../../prop-src/pat.pcc"
  } else {
#line 107 "../../prop-src/pat.pcc"
   return 
#line 107 "../../prop-src/pat.pcc"
#line 107 "../../prop-src/pat.pcc"
    nil_1_
#line 107 "../../prop-src/pat.pcc"
#line 107 "../../prop-src/pat.pcc"
    ; 
#line 107 "../../prop-src/pat.pcc"
  }
}
#line 109 "../../prop-src/pat.pcc"
#line 109 "../../prop-src/pat.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Convert a simple labeled pattern list into an labeled unifier list.
//
///////////////////////////////////////////////////////////////////////////////

LabPats unifier_of( LabPats pats)
{
  
#line 120 "../../prop-src/pat.pcc"
#line 128 "../../prop-src/pat.pcc"
{
  if (pats) {
#line 123 "../../prop-src/pat.pcc"
    
    LabPat lab_pat;
    lab_pat.label = pats->_1.label;
    lab_pat.pat   = unifier_of(pats->_1.pat);
    return 
#line 127 "../../prop-src/pat.pcc"
#line 127 "../../prop-src/pat.pcc"
    list_1_(lab_pat,unifier_of(pats->_2))
#line 127 "../../prop-src/pat.pcc"
#line 127 "../../prop-src/pat.pcc"
    ;
    
#line 128 "../../prop-src/pat.pcc"
  } else {
#line 122 "../../prop-src/pat.pcc"
   return 
#line 122 "../../prop-src/pat.pcc"
#line 122 "../../prop-src/pat.pcc"
    nil_1_
#line 122 "../../prop-src/pat.pcc"
#line 122 "../../prop-src/pat.pcc"
    ; 
#line 122 "../../prop-src/pat.pcc"
  }
}
#line 129 "../../prop-src/pat.pcc"
#line 129 "../../prop-src/pat.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Check whether pattern a subsumes b, i.e. more general.
//
///////////////////////////////////////////////////////////////////////////////

Bool subsumes( Pat a, Pat b, Bool v)
{
  
#line 140 "../../prop-src/pat.pcc"
#line 169 "../../prop-src/pat.pcc"
{
  if (a) {
    switch (a->tag__) {
      case a_Pat::tag_CONSpat: {
        if (b) {
          switch (b->tag__) {
            case a_Pat::tag_CONSpat: {
#line 161 "../../prop-src/pat.pcc"
             return _CONSpat(a)->CONSpat == _CONSpat(b)->CONSpat; 
#line 161 "../../prop-src/pat.pcc"
              } break;
            case a_Pat::tag_TYPEDpat: {
              L4:; 
#line 159 "../../prop-src/pat.pcc"
             return subsumes( a, _TYPEDpat(b)->_1, v); 
#line 159 "../../prop-src/pat.pcc"
              } break;
            case a_Pat::tag_ASpat: {
              L5:; 
#line 155 "../../prop-src/pat.pcc"
             return subsumes( a, _ASpat(b)->_2, v); 
#line 155 "../../prop-src/pat.pcc"
              } break;
            default: {
              L6:; 
#line 169 "../../prop-src/pat.pcc"
             return false; 
#line 169 "../../prop-src/pat.pcc"
              } break;
          }
        } else { goto L6; }
        } break;
      case a_Pat::tag_APPpat: {
        if (b) {
          switch (b->tag__) {
            case a_Pat::tag_APPpat: {
#line 163 "../../prop-src/pat.pcc"
             return subsumes( _APPpat(a)->_1, _APPpat(b)->_1, v) && subsumes( _APPpat(a)->_2, _APPpat(b)->_2, v); 
#line 163 "../../prop-src/pat.pcc"
              } break;
            case a_Pat::tag_TYPEDpat: { goto L4; } break;
            case a_Pat::tag_ASpat: { goto L5; } break;
            default: { goto L6; } break;
          }
        } else { goto L6; }
        } break;
      case a_Pat::tag_TYPEDpat: {
        if (b) {
          switch (b->tag__) {
            case a_Pat::tag_ASpat: { goto L5; } break;
            default: {
              L7:; 
#line 157 "../../prop-src/pat.pcc"
             return subsumes( _TYPEDpat(a)->_1, b, v); 
#line 157 "../../prop-src/pat.pcc"
              } break;
          }
        } else { goto L7; }
        } break;
      case a_Pat::tag_ASpat: {
#line 153 "../../prop-src/pat.pcc"
       return subsumes( _ASpat(a)->_2, b, v); 
#line 153 "../../prop-src/pat.pcc"
        } break;
      case a_Pat::tag_LITERALpat: {
        if (b) {
          switch (b->tag__) {
            case a_Pat::tag_TYPEDpat: { goto L4; } break;
            case a_Pat::tag_ASpat: { goto L5; } break;
            case a_Pat::tag_LITERALpat: {
#line 147 "../../prop-src/pat.pcc"
             return literal_equal( _LITERALpat(a)->LITERALpat, _LITERALpat(b)->LITERALpat); 
#line 147 "../../prop-src/pat.pcc"
              } break;
            default: { goto L6; } break;
          }
        } else { goto L6; }
        } break;
      case a_Pat::tag_TUPLEpat: {
        if (b) {
          switch (b->tag__) {
            case a_Pat::tag_TYPEDpat: { goto L4; } break;
            case a_Pat::tag_ASpat: { goto L5; } break;
            case a_Pat::tag_TUPLEpat: {
#line 149 "../../prop-src/pat.pcc"
             return subsumes( _TUPLEpat(a)->TUPLEpat, _TUPLEpat(b)->TUPLEpat, v); 
#line 149 "../../prop-src/pat.pcc"
              } break;
            default: { goto L6; } break;
          }
        } else { goto L6; }
        } break;
      case a_Pat::tag_EXTUPLEpat: {
        if (b) {
          switch (b->tag__) {
            case a_Pat::tag_TYPEDpat: { goto L4; } break;
            case a_Pat::tag_ASpat: { goto L5; } break;
            case a_Pat::tag_EXTUPLEpat: {
#line 151 "../../prop-src/pat.pcc"
             return subsumes( _EXTUPLEpat(a)->EXTUPLEpat, _EXTUPLEpat(b)->EXTUPLEpat, v); 
#line 151 "../../prop-src/pat.pcc"
              } break;
            default: { goto L6; } break;
          }
        } else { goto L6; }
        } break;
      case a_Pat::tag_GUARDpat: {
        if (b) {
          switch (b->tag__) {
            case a_Pat::tag_TYPEDpat: { goto L4; } break;
            case a_Pat::tag_ASpat: { goto L5; } break;
            case a_Pat::tag_GUARDpat: {
#line 165 "../../prop-src/pat.pcc"
             return subsumes( _GUARDpat(a)->_1, _GUARDpat(b)->_1, v) && equal( _GUARDpat(a)->_2, _GUARDpat(b)->_2); 
#line 165 "../../prop-src/pat.pcc"
              } break;
            default: { goto L6; } break;
          }
        } else { goto L6; }
        } break;
      case a_Pat::tag_LOGICALpat: {
        if (b) {
          switch (b->tag__) {
            case a_Pat::tag_TYPEDpat: { goto L4; } break;
            case a_Pat::tag_ASpat: { goto L5; } break;
            default: {
              L8:; 
              switch (_LOGICALpat(a)->_1) {
                case ORpat: {
                  L9:; 
#line 167 "../../prop-src/pat.pcc"
                 return subsumes(_LOGICALpat(a)->_2,b,v) && subsumes(_LOGICALpat(a)->_3,b,v); 
#line 167 "../../prop-src/pat.pcc"
                  } break;
                default: { goto L6; } break;
              }
              } break;
          }
        } else { goto L8; }
        } break;
      case a_Pat::tag_BACKEDGEpat: {
#line 145 "../../prop-src/pat.pcc"
       return subsumes( _BACKEDGEpat(a)->_3, b, v); 
#line 145 "../../prop-src/pat.pcc"
        } break;
      case a_Pat::tag_WILDpat:
      case a_Pat::tag_IDpat: {
#line 143 "../../prop-src/pat.pcc"
       return true; 
#line 143 "../../prop-src/pat.pcc"
        } break;
      default: {
        L10:; 
        if (b) {
          switch (b->tag__) {
            case a_Pat::tag_TYPEDpat: { goto L4; } break;
            case a_Pat::tag_ASpat: { goto L5; } break;
            default: { goto L6; } break;
          }
        } else { goto L6; }
        } break;
    }
  } else { goto L10; }
}
#line 170 "../../prop-src/pat.pcc"
#line 170 "../../prop-src/pat.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Checks whether list a subsumes list b.  Subsumption is computed
//  componentwise.
//
///////////////////////////////////////////////////////////////////////////////

Bool subsumes( Pats a, Pats b, Bool v)
{  
#line 181 "../../prop-src/pat.pcc"
#line 185 "../../prop-src/pat.pcc"
{
  if (a) {
    if (b) {
#line 184 "../../prop-src/pat.pcc"
     return subsumes(a->_1,b->_1,v) && subsumes(a->_2,b->_2,v); 
#line 184 "../../prop-src/pat.pcc"
    } else {
      L11:; 
#line 185 "../../prop-src/pat.pcc"
     return false; 
#line 185 "../../prop-src/pat.pcc"
    }
  } else {
    if (b) { goto L11; } else {
#line 183 "../../prop-src/pat.pcc"
     return true; 
#line 183 "../../prop-src/pat.pcc"
    }
  }
}
#line 186 "../../prop-src/pat.pcc"
#line 186 "../../prop-src/pat.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Computes the subsumption info for two labeled pat lists.
//
///////////////////////////////////////////////////////////////////////////////

Bool subsumes( LabPats, LabPats, Bool verbose)
{
  return false;
}
#line 199 "../../prop-src/pat.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 751
Number of ifs generated      = 21
Number of switches generated = 15
Number of labels             = 11
Number of gotos              = 41
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
