#ifndef SETL_abstract_syntax_h
#define SETL_abstract_syntax_h

#include "foundation.ph"

datatype Exp :: collectable 
   =  IDexp     (Id) 
   |  LITexp    (Literal)
   |  APPexp    (Exp, Exp)
   |  TUPLEexp  (Exps)
   |  RECORDexp (LabeledExps)
   |  SETexp    (Exps)
   |  CASEexp   (Exp, Exps)
   |  IFexp     (Exp, Exp, Exp)
   |  WHILEexp  (Exp, Exp)
   |  SEQexp    (Exps)
   |  LETexp    (Decls, Exp)
   |  PRIMexp   (Prim)

and Prim :: collectable
   =  "+"    | "-"    | "*"   | "/"   | ":="
   |  "="    | "<"    | ">"   | ">="  | "<="
   |  "/="   | "#"    | "arb" | "div" | "mod"
   |  "with" | "less"

and Decl :: collectable
   =  TYPEdecl     (Id, Ids, Ty)
   |  DATATYPEdecl (Id, Ids, Terms)

and Term :: collectable = TERM (Id, Ty)

and Ty :: collectable =
      NOty
   |  VARty   (Ty)

and LabeledExp :: collectable = LABELEDexp{ id : Id, exp : Exp }

and Literal :: collectable 
   =  INTlit    (int)
   |  REALlit   (double)
   |  STRINGlit (const char *)
   |  CHARlit   (char)

where type Ids         = List<Id>
       and Literals    = List<Literal>
       and Exps        = List<Exp>
       and LabeledExps = List<LabeledExp>
       and Decls       = List<Decl>
       and Terms       = List<Term>
       and Tys         = List<Ty>
;

#endif
