///////////////////////////////////////////////////////////////////////////////
//
//  This file contains the definitions for the intermediate data structures
//  used within the Prop -> C++ translator.  Definitions for types, patterns,
//  decision trees, and pretty printing formats are located here.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef intermediate_representations_h
#define intermediate_representations_h

#include "basics.ph"

///////////////////////////////////////////////////////////////////////////////
//
//  Forward datatype declarations
//
///////////////////////////////////////////////////////////////////////////////

datatype Exp and Stmt and Decl and MatchRule and CollectionDesc;

class GraphTypeDef;
class EdgeDef;
class NodeDef;
class DatatypeHierarchy;
class DatatypeClass;

///////////////////////////////////////////////////////////////////////////////
//
//  Qualifiers determines various implementation characteristics
//  of the type.
//
///////////////////////////////////////////////////////////////////////////////

enum
{
  QUALnone          = 0,      // no qualifiers
  QUALprintable     = 1<<0,   // pretty printable
  QUALtracable      = 1<<1,   // reference countable
  QUALcollectable   = 1<<2,   // garbage collectable
  QUALrewritable    = 1<<3,   // rewritable
  QUALrelation      = 1<<4,   // a relation
  QUALpersistent    = 1<<5,   // persistent type
  QUALclass         = 1<<6,   // class type
  QUALconst         = 1<<7,   // const
  QUALunsigned      = 1<<8,   // unsigned
  QUALsigned        = 1<<9,   // signed
  QUALvirtual       = 1<<10,  // virtual inheritance
  QUALextensible    = 1<<11,  // extensible type
  QUALview          = 1<<12,  // a view
  QUALunifiable     = 1<<13,  // an unifiable term
  QUALtaggedpointer = 1<<14,  // use tagged pointers for representation
  QUALunboxed       = 1<<15,  // use unboxed presentation if possible
  QUALfinalizable   = 1<<16,  // object should be finalized
  QUALapplicative   = 1<<17,  // applicative rewrite
  QUALtreeparser    = 1<<18,  // tree parsing
  QUALparser        = 1<<19,  // parser class
  QUALlexeme        = 1<<20,  // usable as tokens
  QUALbitfield      = 1<<21,  // an opcode or opcode bitfield
  QUALtopdown       = 1<<22,  // use topdown tree matching in rewriting
  QUALvariable      = 1<<23,  // unifiable variable
  QUALgraphtype     = 1<<24,  // a graph type
  QUALgraphnode     = 1<<25,  // a graph node
  QUALgraphedge     = 1<<26,  // a graph edge
  QUALvirtualdestr  = 1<<27,  // virtual destructor
  QUALinline        = 1<<28,  // inline methods
  QUALextern        = 1<<29   // noninline methods
};

///////////////////////////////////////////////////////////////////////////////
//
//  Optimization options
//
///////////////////////////////////////////////////////////////////////////////

enum
{
  OPTnone          = 0,     // no optimization
  OPTtagless       = 1<<0,  // omit the embedded variant tag
  OPTsubclassless  = 1<<1,  // omit the subclass hierarchy
  OPTbaseclassless = 1<<2,  // omit inheritance from base class
  OPTtaggedpointer = 1<<3,  // embedded the variant tag in lower bits
                            // of the pointer.
  OPTunboxed       = 1<<4,  // use unboxed representation if possible
  OPTtaggedvar     = 1<<5   // tagged variables
};

///////////////////////////////////////////////////////////////////////////////
//
//  Scoping
//
///////////////////////////////////////////////////////////////////////////////

datatype Scope = PRIVATEscope
               | PROTECTEDscope
               | PUBLICscope

///////////////////////////////////////////////////////////////////////////////
//
//  Formal/actual parameters.
//
///////////////////////////////////////////////////////////////////////////////

and Parameter = TYbody | TYformal | TYsimpleformal | TYactual

///////////////////////////////////////////////////////////////////////////////
//
//  Pattern variable polarity.
//
///////////////////////////////////////////////////////////////////////////////

and Polarity = ISpositive
             | ISnegative
             | ISneither

///////////////////////////////////////////////////////////////////////////////
//
//  Type expression.
//
//  Note: All variant datatypes with arguments in the translator are
//  either inherited from class MEM or class Loc.  Class MEM
//  redefines the operator new() to allocate from a global memory pool,
//  which is much faster than the built-in malloc/free.  Class Loc,
//  which is derived from MEM, also keeps track of the source position
//  at the same time.
//
///////////////////////////////////////////////////////////////////////////////

and Ty : public MEM
        = NOty                          // no type
        | VARty    (Ty)                 // a type variable
        | INDty    (Id, int)            // indexed to quantifier table.
        | QUALty   (TyQual, Ty)         // a qualified type
        | TYCONty  (TyCon, List<Ty>)    // type constructor
        | POLYty   (Ty, int, TyVar [])  // quantified polymorphic type
        | DEFVALty (Ty, Exp)            // default argument.
        | NESTEDty (Ty, Ty)             // e.g. Class::type

///////////////////////////////////////////////////////////////////////////////
//
//  Type constructor.
//
///////////////////////////////////////////////////////////////////////////////

and TyCon : public MEM
		= POINTERtycon                  // pointer type
        | REFtycon                      // reference type
        | IDtycon (Id)                  // constructor name
        | TUPLEtycon                    // tuple type
        | EXTUPLEtycon                  // explicit tuple type
        | FUNtycon                      // function type
        | TYPEtycon                     // type of type
        | RECORDtycon (List<Id>, Bool)  // record type
        | ARRAYtycon  (Exp)             // array type
        | BITFIELDtycon                 // bitfield type
          {
            width     : int,            // width of field
            is_signed : Bool = false    // signed extended?
          }
        | DATATYPEtycon                 // algebraic datatype
          {
            id         : Id,            // name of type
            unit       : int,           // number of unit constructors
            arg        : int,           // number of arg. constructors
            terms      : Cons [],       // constructor descriptors
            tyvars     : TyVars,        // type variables (if any)
            polyty     : Ty,            // polymorphic type scheme
            inherit    : List<Inherit>, // inheritance relation
            qualifiers : TyQual,        // type qualifiers
            opt        : TyOpt,         // optimization flags
            body       : List<Decl>,    // additional declarations
            view_match : Exp,           //
            location   : const Loc *,   // location.
            hierarchy  : DatatypeHierarchy * = 0
          }
        | COLtycon   (CollectionDesc)   // collection type
        | GRAPHtycon (GraphTypeDef *)   // a graph type
        | NODEtycon (NodeDef *)         // a node type
        | EDGEtycon (EdgeDef *)         // an edge type

///////////////////////////////////////////////////////////////////////////////
//
//  Patterns.
//
///////////////////////////////////////////////////////////////////////////////

and  Pat : public MEM
        = NOpat                               // no pattern
        | WILDpat    ()                       // wild card '_'
        | INDpat     (Id, int, Ty)            // an index to quantifiers
        | POLYpat    (Id, int, Ids, Pat, Exp, Bool) // a pattern scheme
        | IDpat      (Id, Ty, Exp)            // pattern variable
        | CONSpat    (Cons)                   // constructor pattern
        | APPpat     (Pat, Pat)               // pattern application
        | TYPEDpat   (Pat, Ty)                // typed pattern
        | ASpat      (Id, Pat, Ty, Exp)       // 'as' pattern
        | LITERALpat (Literal)                // literal pattern
        | CONTEXTpat (Conses, Pat)            // context pattern
        | LEXEMEpat  (Id, Ty, int, Cons [])   // lexeme pattern
        | ARRAYpat   (List<Pat>, Bool)        // array pattern
        | TUPLEpat   (List<Pat>)              // implicit tuple pattern
        | EXTUPLEpat (List<Pat>)              // explicit tuple pattern
        | RECORDpat  (List<LabPat>, Bool)     // record pattern
        | LISTpat                             // list pattern
          {
            cons : Cons,                      // cons constructor
            nil  : Cons,                      // nil constructor
            head : List<Pat>,                 // head of list
            tail : Pat                        // tail of list
          }
        | VECTORpat                           // vector pattern
          {
            cons  : Cons,                     // constructor info
            len   : Pat,                      // length pattern
            array : Pat,                      // array pattern
            elements  : List<Pat>,            // elements of vector
            head_flex : Bool,                 // head flexible?
            tail_flex : Bool                  // tail flexible?
          }
        | APPENDpat  (Pat, Pat, Ty)           // append pattern
        | GUARDpat   (Pat, Exp)               // guard pattern
        | LOGICALpat (LogicalPat, Pat, Pat = NOpat) // logical patterns
        | BACKEDGEpat(int,Id,Pat)             // backedge (for loops)
        | UNIFYpat   (Pat,Exp)                // for unification
        | MARKEDpat  (Loc, Pat)               // marked with location
        public: { Exp selector; Ty ty; }

///////////////////////////////////////////////////////////////////////////////
//
//  Logical pattern connectives.
//  These are used to alter the standard interpretation of a pattern.
//  For example, ! pat matches iff pat does not match, and so on.
//
///////////////////////////////////////////////////////////////////////////////

and LogicalPat = NOTpat       // ! pat
               | ANDpat       // pat && pat
               | ORpat        // pat || pat
               | EQUIVpat     // pat equiv: pat
               | XORpat       // pat xor: pat
               | IMPLIESpat   // pat implies: pat

///////////////////////////////////////////////////////////////////////////////
//
//  Literal constants.
//
///////////////////////////////////////////////////////////////////////////////

and Literal : public MEM
        = INTlit    (int)          // integer literal
        | BOOLlit   (Bool)         // boolean literal
        | CHARlit   (char)         // character literal
        | REALlit   (double)       // floating point literal
        | STRINGlit (const char *) // string literal
        | REGEXPlit (const char *) // regular expression literal
        | QUARKlit  (const char *) // quark literal(i.e atom strings)
        | BIGINTlit (const char *) // big integer literal

///////////////////////////////////////////////////////////////////////////////
//
//  Constructor descriptor.
//
///////////////////////////////////////////////////////////////////////////////

and Cons : public MEM
        = NOcons
        | ONEcons
          {
            name           : Id,                 // constructor name
            alg_ty         : Ty,                 // algebraic type
            cons_ty        : Ty,                 // type of this constructor
            ty             : Ty,                 // type of argument
            tag            : int,                // tag assigned
            print_formats  : PrintFormats,       // printing format
            location       : const Loc *,        // location
            inherit        : List<Inherit>,      // inheritance relation
            body           : List<Decl>,         // additional decls.
            opt            : TyOpt,              // optimizations
            qual           : TyQual,             // qualifiers
            view_predicate : Exp,                // view predicate
            view_selectors : Exp [],             // selectors
            lexeme_pattern : Pat,                // pattern
	        class_def      : DatatypeClass * = 0
          }

///////////////////////////////////////////////////////////////////////////////
//
//  Production symbols formats.
//
///////////////////////////////////////////////////////////////////////////////

and  ProductionSymbol : public Loc
        = TERMsym      (char)          // terminal symbol
        | TERMSTRINGsym(const char *)  // strings
        | TERMREGEXPsym(const char *)  // regular expression
        | TOKENsym     (Cons)          // terminal token
        | NONTERMsym   (Id)            // non terminal
        | POSNONTERMsym(int)           // positional non terminal
        | ACTIONsym    (List<Decl>)    // action symbol
        | PREDICATEsym (Exp)           // semantic predicate
        | PRECsym      (Cons)          // precedence symbol
        | ERRORsym     ()              // error terminal
        | SPECIALsym   (char)          // special sequence

///////////////////////////////////////////////////////////////////////////////
//
//  Persistent type id
//
///////////////////////////////////////////////////////////////////////////////

and Pid : public MEM = PERSISTid  (const char *)
                     | PERSISTnone

///////////////////////////////////////////////////////////////////////////////
//
//  Inheritance
//
///////////////////////////////////////////////////////////////////////////////

and Inherit : public Loc = INHERIT
                           {
                             super_class : Ty,
                             scope       : Scope = PUBLICscope,
                             qualifiers  : TyQual = QUALnone
                           }

///////////////////////////////////////////////////////////////////////////////
//
//  Pattern laws.
//     Common abbreviations of function, pointer and reference types, etc.
//
///////////////////////////////////////////////////////////////////////////////

law FUNty (a,b)     = TYCONty(FUNtycon, #[ a, b ])
  | POINTERty a     = TYCONty(POINTERtycon, #[ a ])
  | REFty     a     = TYCONty(REFtycon, #[ a ])
  | TUPLEty   a     = TYCONty(TUPLEtycon, a)
  | EXTUPLEty a     = TYCONty(EXTUPLEtycon, a)
  | RECORDty(l,f,a) = TYCONty(RECORDtycon(l,f),a)
  | ARRAYty(t,e)    = TYCONty(ARRAYtycon(e),#[ t ])
  | IDty (id,a)     = TYCONty(IDtycon id, a)
  | DATATYPEty(d,a) = TYCONty(DATATYPEtycon d, a)
  | BITFIELDty desc = TYCONty(BITFIELDtycon desc, #[])
  | TYPEty          = TYCONty(TYPEtycon, #[])
  | GRAPHty G       = TYCONty(GRAPHtycon G,_)
  | NODEty n        = TYCONty(NODEtycon n,_)
  | EDGEty e        = TYCONty(EDGEtycon e,_)

  | INTpat    i     = LITERALpat(INTlit i)
  | REALpat   r     = LITERALpat(REALlit r)
  | BOOLpat   b     = LITERALpat(BOOLlit b)
  | CHARpat   c     = LITERALpat(CHARlit c)
  | BIGINTpat b     = LITERALpat(BIGINTlit b)
  | STRINGpat s     = LITERALpat(STRINGlit s)
  | QUARKpat  q     = LITERALpat(QUARKlit q)
  | REGEXPpat re    = LITERALpat(REGEXPlit re)

///////////////////////////////////////////////////////////////////////////////
//
//  Miscellaneous type abbreviations.
//
///////////////////////////////////////////////////////////////////////////////

where type TyQual       = int   // qualifier flags
and        TyOpt        = int   // optimizer flags
and        LabTy        = { label : Id, ty : Ty }
and        LabPat       = { label : Id, pat : Pat }
and        Inherits     = List<Inherit>
and        Conses       = List<Cons>
and        Tys          = List<Ty>
and        LabTys       = List<LabTy>
and        Pats         = List<Pat>
and        LabPats      = List<LabPat>
and        TyVar        = Id
and        TyVars       = List<TyVar>
and        PrintFormats = List<ProductionSymbol>
;

///////////////////////////////////////////////////////////////////////////////
//
//  Pretty printing methods
//
///////////////////////////////////////////////////////////////////////////////

extern std::ostream& operator << (std::ostream&, Ids);
extern std::ostream& operator << (std::ostream&, Scope);
extern std::ostream& operator << (std::ostream&, Ty);
extern std::ostream& operator << (std::ostream&, List<Ty>);
extern std::ostream& operator << (std::ostream&, Pat);
extern std::ostream& operator << (std::ostream&, LabPat);
extern std::ostream& operator << (std::ostream&, List<Pat>);
extern std::ostream& operator << (std::ostream&, List<LabPat>);
extern std::ostream& operator << (std::ostream&, Literal);
extern std::ostream& operator << (std::ostream&, Inherit);
extern std::ostream& operator << (std::ostream&, List<Inherit>);
extern std::ostream& operator << (std::ostream&, Pid);

extern std::ostream& print_cons (std::ostream&, Cons);
extern void     print_parameter (std::ostream&, Ty, Id, Parameter);
extern void     print_tyvars    (std::ostream&, TyVars, char, char, Bool);
extern Id       index_of (int, Id = 0);

#endif
