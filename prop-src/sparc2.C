///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.2.7),
//  last updated on Mar 20, 1996.
//  The original source file is "sparc2.pC".
///////////////////////////////////////////////////////////////////////////////

#define PROP_REWRITING_USED
#define PROP_QUARK_USED
#include <propdefs.h>
///////////////////////////////////////////////////////////////////////////////
// Forward class definition for Inst
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_Inst_defined
#define datatype_Inst_defined
   typedef class a_Inst * Inst;
#endif

///////////////////////////////////////////////////////////////////////////////
// Class hierarchy for datatype Inst
///////////////////////////////////////////////////////////////////////////////
class a_Inst; // base class for datatype Inst
   class Inst_ADDD;	// subclass for 'ADDD (Inst, Inst)'
   class Inst_ADDF;	// subclass for 'ADDF (Inst, Inst)'
   class Inst_ADDI;	// subclass for 'ADDI (Inst, Inst)'
   class Inst_ADDP;	// subclass for 'ADDP (Inst, Inst)'
   class Inst_ADDU;	// subclass for 'ADDU (Inst, Inst)'
   class Inst_ARGB;	// subclass for 'ARGB Inst'
   class Inst_ARGD;	// subclass for 'ARGD Inst'
   class Inst_ARGF;	// subclass for 'ARGF Inst'
   class Inst_ARGI;	// subclass for 'ARGI Inst'
   class Inst_ARGP;	// subclass for 'ARGP Inst'
   class Inst_ASGNB;	// subclass for 'ASGNB (Inst, Inst)'
   class Inst_ASGNC;	// subclass for 'ASGNC (Inst, Inst)'
   class Inst_ASGND;	// subclass for 'ASGND (Inst, Inst)'
   class Inst_ASGNF;	// subclass for 'ASGNF (Inst, Inst)'
   class Inst_ASGNI;	// subclass for 'ASGNI (Inst, Inst)'
   class Inst_ASGNP;	// subclass for 'ASGNP (Inst, Inst)'
   class Inst_ASGNS;	// subclass for 'ASGNS (Inst, Inst)'
   class Inst_BANDU;	// subclass for 'BANDU (Inst, Inst)'
   class Inst_BCOMU;	// subclass for 'BCOMU Inst'
   class Inst_BORU;	// subclass for 'BORU (Inst, Inst)'
   class Inst_BXORU;	// subclass for 'BXORU (Inst, Inst)'
   class Inst_CALLB;	// subclass for 'CALLB (Inst, Inst)'
   class Inst_CALLD;	// subclass for 'CALLD Inst'
   class Inst_CALLF;	// subclass for 'CALLF Inst'
   class Inst_CALLI;	// subclass for 'CALLI Inst'
   class Inst_CALLV;	// subclass for 'CALLV Inst'
   class Inst_CVCI;	// subclass for 'CVCI Inst'
   class Inst_CVCU;	// subclass for 'CVCU Inst'
   class Inst_CVDF;	// subclass for 'CVDF Inst'
   class Inst_CVDI;	// subclass for 'CVDI Inst'
   class Inst_CVFD;	// subclass for 'CVFD Inst'
   class Inst_CVIC;	// subclass for 'CVIC Inst'
   class Inst_CVID;	// subclass for 'CVID Inst'
   class Inst_CVIS;	// subclass for 'CVIS Inst'
   class Inst_CVIU;	// subclass for 'CVIU Inst'
   class Inst_CVPU;	// subclass for 'CVPU Inst'
   class Inst_CVSI;	// subclass for 'CVSI Inst'
   class Inst_CVSU;	// subclass for 'CVSU Inst'
   class Inst_CVUC;	// subclass for 'CVUC Inst'
   class Inst_CVUI;	// subclass for 'CVUI Inst'
   class Inst_CVUP;	// subclass for 'CVUP Inst'
   class Inst_CVUS;	// subclass for 'CVUS Inst'
   class Inst_DIVD;	// subclass for 'DIVD (Inst, Inst)'
   class Inst_DIVF;	// subclass for 'DIVF (Inst, Inst)'
   class Inst_DIVI;	// subclass for 'DIVI (Inst, Inst)'
   class Inst_DIVU;	// subclass for 'DIVU (Inst, Inst)'
   class Inst_EQD;	// subclass for 'EQD (Inst, Inst)'
   class Inst_EQF;	// subclass for 'EQF (Inst, Inst)'
   class Inst_EQI;	// subclass for 'EQI (Inst, Inst)'
   class Inst_GED;	// subclass for 'GED (Inst, Inst)'
   class Inst_GEF;	// subclass for 'GEF (Inst, Inst)'
   class Inst_GEI;	// subclass for 'GEI (Inst, Inst)'
   class Inst_GEU;	// subclass for 'GEU (Inst, Inst)'
   class Inst_GTD;	// subclass for 'GTD (Inst, Inst)'
   class Inst_GTF;	// subclass for 'GTF (Inst, Inst)'
   class Inst_GTI;	// subclass for 'GTI (Inst, Inst)'
   class Inst_GTU;	// subclass for 'GTU (Inst, Inst)'
   class Inst_INDIRB;	// subclass for 'INDIRB Inst'
   class Inst_INDIRC;	// subclass for 'INDIRC Inst'
   class Inst_INDIRD;	// subclass for 'INDIRD Inst'
   class Inst_INDIRF;	// subclass for 'INDIRF Inst'
   class Inst_INDIRI;	// subclass for 'INDIRI Inst'
   class Inst_INDIRP;	// subclass for 'INDIRP Inst'
   class Inst_INDIRS;	// subclass for 'INDIRS Inst'
   class Inst_JUMPV;	// subclass for 'JUMPV Inst'
   class Inst_LED;	// subclass for 'LED (Inst, Inst)'
   class Inst_LEF;	// subclass for 'LEF (Inst, Inst)'
   class Inst_LEI;	// subclass for 'LEI (Inst, Inst)'
   class Inst_LEU;	// subclass for 'LEU (Inst, Inst)'
   class Inst_LOADB;	// subclass for 'LOADB Inst'
   class Inst_LOADC;	// subclass for 'LOADC Inst'
   class Inst_LOADD;	// subclass for 'LOADD Inst'
   class Inst_LOADF;	// subclass for 'LOADF Inst'
   class Inst_LOADI;	// subclass for 'LOADI Inst'
   class Inst_LOADP;	// subclass for 'LOADP Inst'
   class Inst_LOADS;	// subclass for 'LOADS Inst'
   class Inst_LOADU;	// subclass for 'LOADU Inst'
   class Inst_LSHI;	// subclass for 'LSHI (Inst, Inst)'
   class Inst_LSHU;	// subclass for 'LSHU (Inst, Inst)'
   class Inst_LTD;	// subclass for 'LTD (Inst, Inst)'
   class Inst_LTF;	// subclass for 'LTF (Inst, Inst)'
   class Inst_LTI;	// subclass for 'LTI (Inst, Inst)'
   class Inst_LTU;	// subclass for 'LTU (Inst, Inst)'
   class Inst_MODI;	// subclass for 'MODI (Inst, Inst)'
   class Inst_MODU;	// subclass for 'MODU (Inst, Inst)'
   class Inst_MULD;	// subclass for 'MULD (Inst, Inst)'
   class Inst_MULF;	// subclass for 'MULF (Inst, Inst)'
   class Inst_MULI;	// subclass for 'MULI (Inst, Inst)'
   class Inst_MULU;	// subclass for 'MULU (Inst, Inst)'
   class Inst_NED;	// subclass for 'NED (Inst, Inst)'
   class Inst_NEF;	// subclass for 'NEF (Inst, Inst)'
   class Inst_NEI;	// subclass for 'NEI (Inst, Inst)'
   class Inst_NEGD;	// subclass for 'NEGD Inst'
   class Inst_NEGF;	// subclass for 'NEGF Inst'
   class Inst_NEGI;	// subclass for 'NEGI Inst'
   class Inst_RETD;	// subclass for 'RETD Inst'
   class Inst_RETF;	// subclass for 'RETF Inst'
   class Inst_RETI;	// subclass for 'RETI Inst'
   class Inst_RSHI;	// subclass for 'RSHI (Inst, Inst)'
   class Inst_RSHU;	// subclass for 'RSHU (Inst, Inst)'
   class Inst_SUBD;	// subclass for 'SUBD (Inst, Inst)'
   class Inst_SUBF;	// subclass for 'SUBF (Inst, Inst)'
   class Inst_SUBI;	// subclass for 'SUBI (Inst, Inst)'
   class Inst_SUBP;	// subclass for 'SUBP (Inst, Inst)'
   class Inst_SUBU;	// subclass for 'SUBU (Inst, Inst)'

///////////////////////////////////////////////////////////////////////////////
// Base class for datatype 'Inst'
///////////////////////////////////////////////////////////////////////////////
class a_Inst : public TermObj {
public:
#  define ADDRFP (Inst)0
#  define ADDRGP (Inst)1
#  define ADDRLP (Inst)2
#  define CNSTC (Inst)3
#  define CNSTD (Inst)4
#  define CNSTF (Inst)5
#  define CNSTI (Inst)6
#  define CNSTP (Inst)7
#  define CNSTS (Inst)8
#  define CNSTU (Inst)9
#  define LABELV (Inst)10
#  define VREGP (Inst)11
   enum Tag_Inst {
      tag_ADDD = 0, tag_ADDF = 1, tag_ADDI = 2, tag_ADDP = 3, 
      tag_ADDU = 4, tag_ARGB = 5, tag_ARGD = 6, tag_ARGF = 7, 
      tag_ARGI = 8, tag_ARGP = 9, tag_ASGNB = 10, tag_ASGNC = 11, 
      tag_ASGND = 12, tag_ASGNF = 13, tag_ASGNI = 14, tag_ASGNP = 15, 
      tag_ASGNS = 16, tag_BANDU = 17, tag_BCOMU = 18, tag_BORU = 19, 
      tag_BXORU = 20, tag_CALLB = 21, tag_CALLD = 22, tag_CALLF = 23, 
      tag_CALLI = 24, tag_CALLV = 25, tag_CVCI = 26, tag_CVCU = 27, 
      tag_CVDF = 28, tag_CVDI = 29, tag_CVFD = 30, tag_CVIC = 31, 
      tag_CVID = 32, tag_CVIS = 33, tag_CVIU = 34, tag_CVPU = 35, 
      tag_CVSI = 36, tag_CVSU = 37, tag_CVUC = 38, tag_CVUI = 39, 
      tag_CVUP = 40, tag_CVUS = 41, tag_DIVD = 42, tag_DIVF = 43, 
      tag_DIVI = 44, tag_DIVU = 45, tag_EQD = 46, tag_EQF = 47, 
      tag_EQI = 48, tag_GED = 49, tag_GEF = 50, tag_GEI = 51, 
      tag_GEU = 52, tag_GTD = 53, tag_GTF = 54, tag_GTI = 55, 
      tag_GTU = 56, tag_INDIRB = 57, tag_INDIRC = 58, tag_INDIRD = 59, 
      tag_INDIRF = 60, tag_INDIRI = 61, tag_INDIRP = 62, tag_INDIRS = 63, 
      tag_JUMPV = 64, tag_LED = 65, tag_LEF = 66, tag_LEI = 67, 
      tag_LEU = 68, tag_LOADB = 69, tag_LOADC = 70, tag_LOADD = 71, 
      tag_LOADF = 72, tag_LOADI = 73, tag_LOADP = 74, tag_LOADS = 75, 
      tag_LOADU = 76, tag_LSHI = 77, tag_LSHU = 78, tag_LTD = 79, 
      tag_LTF = 80, tag_LTI = 81, tag_LTU = 82, tag_MODI = 83, 
      tag_MODU = 84, tag_MULD = 85, tag_MULF = 86, tag_MULI = 87, 
      tag_MULU = 88, tag_NED = 89, tag_NEF = 90, tag_NEI = 91, 
      tag_NEGD = 92, tag_NEGF = 93, tag_NEGI = 94, tag_RETD = 95, 
      tag_RETF = 96, tag_RETI = 97, tag_RSHI = 98, tag_RSHU = 99, 
      tag_SUBD = 100, tag_SUBF = 101, tag_SUBI = 102, tag_SUBP = 103, 
      tag_SUBU = 104
   };

protected:
   const Tag_Inst _tag_;
   inline a_Inst(Tag_Inst _t_) : _tag_(_t_) {}
public:
   inline int untag() const { return _tag_; }
   inline friend int boxed(const a_Inst * x) { return (unsigned long)x >= 12; }
   inline friend int untag(const a_Inst * x) { return boxed(x) ? x->_tag_ + 12 : (unsigned long)x; }
   ////////////////////////////////////////////////////////////////////////////
   // Downcasting functions for Inst
   ////////////////////////////////////////////////////////////////////////////
   inline friend Inst_ADDD * _ADDD(Inst _x_) { return (Inst_ADDD *)_x_; }
   inline friend Inst_ADDF * _ADDF(Inst _x_) { return (Inst_ADDF *)_x_; }
   inline friend Inst_ADDI * _ADDI(Inst _x_) { return (Inst_ADDI *)_x_; }
   inline friend Inst_ADDP * _ADDP(Inst _x_) { return (Inst_ADDP *)_x_; }
   inline friend Inst_ADDU * _ADDU(Inst _x_) { return (Inst_ADDU *)_x_; }
   inline friend Inst_ARGB * _ARGB(Inst _x_) { return (Inst_ARGB *)_x_; }
   inline friend Inst_ARGD * _ARGD(Inst _x_) { return (Inst_ARGD *)_x_; }
   inline friend Inst_ARGF * _ARGF(Inst _x_) { return (Inst_ARGF *)_x_; }
   inline friend Inst_ARGI * _ARGI(Inst _x_) { return (Inst_ARGI *)_x_; }
   inline friend Inst_ARGP * _ARGP(Inst _x_) { return (Inst_ARGP *)_x_; }
   inline friend Inst_ASGNB * _ASGNB(Inst _x_) { return (Inst_ASGNB *)_x_; }
   inline friend Inst_ASGNC * _ASGNC(Inst _x_) { return (Inst_ASGNC *)_x_; }
   inline friend Inst_ASGND * _ASGND(Inst _x_) { return (Inst_ASGND *)_x_; }
   inline friend Inst_ASGNF * _ASGNF(Inst _x_) { return (Inst_ASGNF *)_x_; }
   inline friend Inst_ASGNI * _ASGNI(Inst _x_) { return (Inst_ASGNI *)_x_; }
   inline friend Inst_ASGNP * _ASGNP(Inst _x_) { return (Inst_ASGNP *)_x_; }
   inline friend Inst_ASGNS * _ASGNS(Inst _x_) { return (Inst_ASGNS *)_x_; }
   inline friend Inst_BANDU * _BANDU(Inst _x_) { return (Inst_BANDU *)_x_; }
   inline friend Inst_BCOMU * _BCOMU(Inst _x_) { return (Inst_BCOMU *)_x_; }
   inline friend Inst_BORU * _BORU(Inst _x_) { return (Inst_BORU *)_x_; }
   inline friend Inst_BXORU * _BXORU(Inst _x_) { return (Inst_BXORU *)_x_; }
   inline friend Inst_CALLB * _CALLB(Inst _x_) { return (Inst_CALLB *)_x_; }
   inline friend Inst_CALLD * _CALLD(Inst _x_) { return (Inst_CALLD *)_x_; }
   inline friend Inst_CALLF * _CALLF(Inst _x_) { return (Inst_CALLF *)_x_; }
   inline friend Inst_CALLI * _CALLI(Inst _x_) { return (Inst_CALLI *)_x_; }
   inline friend Inst_CALLV * _CALLV(Inst _x_) { return (Inst_CALLV *)_x_; }
   inline friend Inst_CVCI * _CVCI(Inst _x_) { return (Inst_CVCI *)_x_; }
   inline friend Inst_CVCU * _CVCU(Inst _x_) { return (Inst_CVCU *)_x_; }
   inline friend Inst_CVDF * _CVDF(Inst _x_) { return (Inst_CVDF *)_x_; }
   inline friend Inst_CVDI * _CVDI(Inst _x_) { return (Inst_CVDI *)_x_; }
   inline friend Inst_CVFD * _CVFD(Inst _x_) { return (Inst_CVFD *)_x_; }
   inline friend Inst_CVIC * _CVIC(Inst _x_) { return (Inst_CVIC *)_x_; }
   inline friend Inst_CVID * _CVID(Inst _x_) { return (Inst_CVID *)_x_; }
   inline friend Inst_CVIS * _CVIS(Inst _x_) { return (Inst_CVIS *)_x_; }
   inline friend Inst_CVIU * _CVIU(Inst _x_) { return (Inst_CVIU *)_x_; }
   inline friend Inst_CVPU * _CVPU(Inst _x_) { return (Inst_CVPU *)_x_; }
   inline friend Inst_CVSI * _CVSI(Inst _x_) { return (Inst_CVSI *)_x_; }
   inline friend Inst_CVSU * _CVSU(Inst _x_) { return (Inst_CVSU *)_x_; }
   inline friend Inst_CVUC * _CVUC(Inst _x_) { return (Inst_CVUC *)_x_; }
   inline friend Inst_CVUI * _CVUI(Inst _x_) { return (Inst_CVUI *)_x_; }
   inline friend Inst_CVUP * _CVUP(Inst _x_) { return (Inst_CVUP *)_x_; }
   inline friend Inst_CVUS * _CVUS(Inst _x_) { return (Inst_CVUS *)_x_; }
   inline friend Inst_DIVD * _DIVD(Inst _x_) { return (Inst_DIVD *)_x_; }
   inline friend Inst_DIVF * _DIVF(Inst _x_) { return (Inst_DIVF *)_x_; }
   inline friend Inst_DIVI * _DIVI(Inst _x_) { return (Inst_DIVI *)_x_; }
   inline friend Inst_DIVU * _DIVU(Inst _x_) { return (Inst_DIVU *)_x_; }
   inline friend Inst_EQD * _EQD(Inst _x_) { return (Inst_EQD *)_x_; }
   inline friend Inst_EQF * _EQF(Inst _x_) { return (Inst_EQF *)_x_; }
   inline friend Inst_EQI * _EQI(Inst _x_) { return (Inst_EQI *)_x_; }
   inline friend Inst_GED * _GED(Inst _x_) { return (Inst_GED *)_x_; }
   inline friend Inst_GEF * _GEF(Inst _x_) { return (Inst_GEF *)_x_; }
   inline friend Inst_GEI * _GEI(Inst _x_) { return (Inst_GEI *)_x_; }
   inline friend Inst_GEU * _GEU(Inst _x_) { return (Inst_GEU *)_x_; }
   inline friend Inst_GTD * _GTD(Inst _x_) { return (Inst_GTD *)_x_; }
   inline friend Inst_GTF * _GTF(Inst _x_) { return (Inst_GTF *)_x_; }
   inline friend Inst_GTI * _GTI(Inst _x_) { return (Inst_GTI *)_x_; }
   inline friend Inst_GTU * _GTU(Inst _x_) { return (Inst_GTU *)_x_; }
   inline friend Inst_INDIRB * _INDIRB(Inst _x_) { return (Inst_INDIRB *)_x_; }
   inline friend Inst_INDIRC * _INDIRC(Inst _x_) { return (Inst_INDIRC *)_x_; }
   inline friend Inst_INDIRD * _INDIRD(Inst _x_) { return (Inst_INDIRD *)_x_; }
   inline friend Inst_INDIRF * _INDIRF(Inst _x_) { return (Inst_INDIRF *)_x_; }
   inline friend Inst_INDIRI * _INDIRI(Inst _x_) { return (Inst_INDIRI *)_x_; }
   inline friend Inst_INDIRP * _INDIRP(Inst _x_) { return (Inst_INDIRP *)_x_; }
   inline friend Inst_INDIRS * _INDIRS(Inst _x_) { return (Inst_INDIRS *)_x_; }
   inline friend Inst_JUMPV * _JUMPV(Inst _x_) { return (Inst_JUMPV *)_x_; }
   inline friend Inst_LED * _LED(Inst _x_) { return (Inst_LED *)_x_; }
   inline friend Inst_LEF * _LEF(Inst _x_) { return (Inst_LEF *)_x_; }
   inline friend Inst_LEI * _LEI(Inst _x_) { return (Inst_LEI *)_x_; }
   inline friend Inst_LEU * _LEU(Inst _x_) { return (Inst_LEU *)_x_; }
   inline friend Inst_LOADB * _LOADB(Inst _x_) { return (Inst_LOADB *)_x_; }
   inline friend Inst_LOADC * _LOADC(Inst _x_) { return (Inst_LOADC *)_x_; }
   inline friend Inst_LOADD * _LOADD(Inst _x_) { return (Inst_LOADD *)_x_; }
   inline friend Inst_LOADF * _LOADF(Inst _x_) { return (Inst_LOADF *)_x_; }
   inline friend Inst_LOADI * _LOADI(Inst _x_) { return (Inst_LOADI *)_x_; }
   inline friend Inst_LOADP * _LOADP(Inst _x_) { return (Inst_LOADP *)_x_; }
   inline friend Inst_LOADS * _LOADS(Inst _x_) { return (Inst_LOADS *)_x_; }
   inline friend Inst_LOADU * _LOADU(Inst _x_) { return (Inst_LOADU *)_x_; }
   inline friend Inst_LSHI * _LSHI(Inst _x_) { return (Inst_LSHI *)_x_; }
   inline friend Inst_LSHU * _LSHU(Inst _x_) { return (Inst_LSHU *)_x_; }
   inline friend Inst_LTD * _LTD(Inst _x_) { return (Inst_LTD *)_x_; }
   inline friend Inst_LTF * _LTF(Inst _x_) { return (Inst_LTF *)_x_; }
   inline friend Inst_LTI * _LTI(Inst _x_) { return (Inst_LTI *)_x_; }
   inline friend Inst_LTU * _LTU(Inst _x_) { return (Inst_LTU *)_x_; }
   inline friend Inst_MODI * _MODI(Inst _x_) { return (Inst_MODI *)_x_; }
   inline friend Inst_MODU * _MODU(Inst _x_) { return (Inst_MODU *)_x_; }
   inline friend Inst_MULD * _MULD(Inst _x_) { return (Inst_MULD *)_x_; }
   inline friend Inst_MULF * _MULF(Inst _x_) { return (Inst_MULF *)_x_; }
   inline friend Inst_MULI * _MULI(Inst _x_) { return (Inst_MULI *)_x_; }
   inline friend Inst_MULU * _MULU(Inst _x_) { return (Inst_MULU *)_x_; }
   inline friend Inst_NED * _NED(Inst _x_) { return (Inst_NED *)_x_; }
   inline friend Inst_NEF * _NEF(Inst _x_) { return (Inst_NEF *)_x_; }
   inline friend Inst_NEI * _NEI(Inst _x_) { return (Inst_NEI *)_x_; }
   inline friend Inst_NEGD * _NEGD(Inst _x_) { return (Inst_NEGD *)_x_; }
   inline friend Inst_NEGF * _NEGF(Inst _x_) { return (Inst_NEGF *)_x_; }
   inline friend Inst_NEGI * _NEGI(Inst _x_) { return (Inst_NEGI *)_x_; }
   inline friend Inst_RETD * _RETD(Inst _x_) { return (Inst_RETD *)_x_; }
   inline friend Inst_RETF * _RETF(Inst _x_) { return (Inst_RETF *)_x_; }
   inline friend Inst_RETI * _RETI(Inst _x_) { return (Inst_RETI *)_x_; }
   inline friend Inst_RSHI * _RSHI(Inst _x_) { return (Inst_RSHI *)_x_; }
   inline friend Inst_RSHU * _RSHU(Inst _x_) { return (Inst_RSHU *)_x_; }
   inline friend Inst_SUBD * _SUBD(Inst _x_) { return (Inst_SUBD *)_x_; }
   inline friend Inst_SUBF * _SUBF(Inst _x_) { return (Inst_SUBF *)_x_; }
   inline friend Inst_SUBI * _SUBI(Inst _x_) { return (Inst_SUBI *)_x_; }
   inline friend Inst_SUBP * _SUBP(Inst _x_) { return (Inst_SUBP *)_x_; }
   inline friend Inst_SUBU * _SUBU(Inst _x_) { return (Inst_SUBU *)_x_; }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::ADDD (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_ADDD : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_ADDD (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_ADDD), _1(_x1), _2(_x2) {}
   inline friend a_Inst * ADDD (Inst _x1, Inst _x2)
      { return new Inst_ADDD (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::ADDF (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_ADDF : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_ADDF (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_ADDF), _1(_x1), _2(_x2) {}
   inline friend a_Inst * ADDF (Inst _x1, Inst _x2)
      { return new Inst_ADDF (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::ADDI (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_ADDI : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_ADDI (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_ADDI), _1(_x1), _2(_x2) {}
   inline friend a_Inst * ADDI (Inst _x1, Inst _x2)
      { return new Inst_ADDI (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::ADDP (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_ADDP : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_ADDP (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_ADDP), _1(_x1), _2(_x2) {}
   inline friend a_Inst * ADDP (Inst _x1, Inst _x2)
      { return new Inst_ADDP (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::ADDU (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_ADDU : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_ADDU (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_ADDU), _1(_x1), _2(_x2) {}
   inline friend a_Inst * ADDU (Inst _x1, Inst _x2)
      { return new Inst_ADDU (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::ARGB Inst'
///////////////////////////////////////////////////////////////////////////////
class Inst_ARGB : public a_Inst {
public:
   Inst ARGB; 
   inline Inst_ARGB (Inst _xARGB)
      : a_Inst(a_Inst::tag_ARGB), ARGB(_xARGB) {}
   inline friend a_Inst * ARGB (Inst _xARGB)
      { return new Inst_ARGB (_xARGB); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::ARGD Inst'
///////////////////////////////////////////////////////////////////////////////
class Inst_ARGD : public a_Inst {
public:
   Inst ARGD; 
   inline Inst_ARGD (Inst _xARGD)
      : a_Inst(a_Inst::tag_ARGD), ARGD(_xARGD) {}
   inline friend a_Inst * ARGD (Inst _xARGD)
      { return new Inst_ARGD (_xARGD); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::ARGF Inst'
///////////////////////////////////////////////////////////////////////////////
class Inst_ARGF : public a_Inst {
public:
   Inst ARGF; 
   inline Inst_ARGF (Inst _xARGF)
      : a_Inst(a_Inst::tag_ARGF), ARGF(_xARGF) {}
   inline friend a_Inst * ARGF (Inst _xARGF)
      { return new Inst_ARGF (_xARGF); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::ARGI Inst'
///////////////////////////////////////////////////////////////////////////////
class Inst_ARGI : public a_Inst {
public:
   Inst ARGI; 
   inline Inst_ARGI (Inst _xARGI)
      : a_Inst(a_Inst::tag_ARGI), ARGI(_xARGI) {}
   inline friend a_Inst * ARGI (Inst _xARGI)
      { return new Inst_ARGI (_xARGI); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::ARGP Inst'
///////////////////////////////////////////////////////////////////////////////
class Inst_ARGP : public a_Inst {
public:
   Inst ARGP; 
   inline Inst_ARGP (Inst _xARGP)
      : a_Inst(a_Inst::tag_ARGP), ARGP(_xARGP) {}
   inline friend a_Inst * ARGP (Inst _xARGP)
      { return new Inst_ARGP (_xARGP); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::ASGNB (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_ASGNB : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_ASGNB (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_ASGNB), _1(_x1), _2(_x2) {}
   inline friend a_Inst * ASGNB (Inst _x1, Inst _x2)
      { return new Inst_ASGNB (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::ASGNC (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_ASGNC : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_ASGNC (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_ASGNC), _1(_x1), _2(_x2) {}
   inline friend a_Inst * ASGNC (Inst _x1, Inst _x2)
      { return new Inst_ASGNC (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::ASGND (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_ASGND : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_ASGND (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_ASGND), _1(_x1), _2(_x2) {}
   inline friend a_Inst * ASGND (Inst _x1, Inst _x2)
      { return new Inst_ASGND (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::ASGNF (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_ASGNF : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_ASGNF (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_ASGNF), _1(_x1), _2(_x2) {}
   inline friend a_Inst * ASGNF (Inst _x1, Inst _x2)
      { return new Inst_ASGNF (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::ASGNI (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_ASGNI : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_ASGNI (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_ASGNI), _1(_x1), _2(_x2) {}
   inline friend a_Inst * ASGNI (Inst _x1, Inst _x2)
      { return new Inst_ASGNI (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::ASGNP (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_ASGNP : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_ASGNP (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_ASGNP), _1(_x1), _2(_x2) {}
   inline friend a_Inst * ASGNP (Inst _x1, Inst _x2)
      { return new Inst_ASGNP (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::ASGNS (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_ASGNS : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_ASGNS (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_ASGNS), _1(_x1), _2(_x2) {}
   inline friend a_Inst * ASGNS (Inst _x1, Inst _x2)
      { return new Inst_ASGNS (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::BANDU (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_BANDU : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_BANDU (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_BANDU), _1(_x1), _2(_x2) {}
   inline friend a_Inst * BANDU (Inst _x1, Inst _x2)
      { return new Inst_BANDU (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::BCOMU Inst'
///////////////////////////////////////////////////////////////////////////////
class Inst_BCOMU : public a_Inst {
public:
   Inst BCOMU; 
   inline Inst_BCOMU (Inst _xBCOMU)
      : a_Inst(a_Inst::tag_BCOMU), BCOMU(_xBCOMU) {}
   inline friend a_Inst * BCOMU (Inst _xBCOMU)
      { return new Inst_BCOMU (_xBCOMU); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::BORU (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_BORU : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_BORU (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_BORU), _1(_x1), _2(_x2) {}
   inline friend a_Inst * BORU (Inst _x1, Inst _x2)
      { return new Inst_BORU (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::BXORU (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_BXORU : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_BXORU (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_BXORU), _1(_x1), _2(_x2) {}
   inline friend a_Inst * BXORU (Inst _x1, Inst _x2)
      { return new Inst_BXORU (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::CALLB (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_CALLB : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_CALLB (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_CALLB), _1(_x1), _2(_x2) {}
   inline friend a_Inst * CALLB (Inst _x1, Inst _x2)
      { return new Inst_CALLB (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::CALLD Inst'
///////////////////////////////////////////////////////////////////////////////
class Inst_CALLD : public a_Inst {
public:
   Inst CALLD; 
   inline Inst_CALLD (Inst _xCALLD)
      : a_Inst(a_Inst::tag_CALLD), CALLD(_xCALLD) {}
   inline friend a_Inst * CALLD (Inst _xCALLD)
      { return new Inst_CALLD (_xCALLD); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::CALLF Inst'
///////////////////////////////////////////////////////////////////////////////
class Inst_CALLF : public a_Inst {
public:
   Inst CALLF; 
   inline Inst_CALLF (Inst _xCALLF)
      : a_Inst(a_Inst::tag_CALLF), CALLF(_xCALLF) {}
   inline friend a_Inst * CALLF (Inst _xCALLF)
      { return new Inst_CALLF (_xCALLF); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::CALLI Inst'
///////////////////////////////////////////////////////////////////////////////
class Inst_CALLI : public a_Inst {
public:
   Inst CALLI; 
   inline Inst_CALLI (Inst _xCALLI)
      : a_Inst(a_Inst::tag_CALLI), CALLI(_xCALLI) {}
   inline friend a_Inst * CALLI (Inst _xCALLI)
      { return new Inst_CALLI (_xCALLI); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::CALLV Inst'
///////////////////////////////////////////////////////////////////////////////
class Inst_CALLV : public a_Inst {
public:
   Inst CALLV; 
   inline Inst_CALLV (Inst _xCALLV)
      : a_Inst(a_Inst::tag_CALLV), CALLV(_xCALLV) {}
   inline friend a_Inst * CALLV (Inst _xCALLV)
      { return new Inst_CALLV (_xCALLV); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::CVCI Inst'
///////////////////////////////////////////////////////////////////////////////
class Inst_CVCI : public a_Inst {
public:
   Inst CVCI; 
   inline Inst_CVCI (Inst _xCVCI)
      : a_Inst(a_Inst::tag_CVCI), CVCI(_xCVCI) {}
   inline friend a_Inst * CVCI (Inst _xCVCI)
      { return new Inst_CVCI (_xCVCI); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::CVCU Inst'
///////////////////////////////////////////////////////////////////////////////
class Inst_CVCU : public a_Inst {
public:
   Inst CVCU; 
   inline Inst_CVCU (Inst _xCVCU)
      : a_Inst(a_Inst::tag_CVCU), CVCU(_xCVCU) {}
   inline friend a_Inst * CVCU (Inst _xCVCU)
      { return new Inst_CVCU (_xCVCU); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::CVDF Inst'
///////////////////////////////////////////////////////////////////////////////
class Inst_CVDF : public a_Inst {
public:
   Inst CVDF; 
   inline Inst_CVDF (Inst _xCVDF)
      : a_Inst(a_Inst::tag_CVDF), CVDF(_xCVDF) {}
   inline friend a_Inst * CVDF (Inst _xCVDF)
      { return new Inst_CVDF (_xCVDF); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::CVDI Inst'
///////////////////////////////////////////////////////////////////////////////
class Inst_CVDI : public a_Inst {
public:
   Inst CVDI; 
   inline Inst_CVDI (Inst _xCVDI)
      : a_Inst(a_Inst::tag_CVDI), CVDI(_xCVDI) {}
   inline friend a_Inst * CVDI (Inst _xCVDI)
      { return new Inst_CVDI (_xCVDI); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::CVFD Inst'
///////////////////////////////////////////////////////////////////////////////
class Inst_CVFD : public a_Inst {
public:
   Inst CVFD; 
   inline Inst_CVFD (Inst _xCVFD)
      : a_Inst(a_Inst::tag_CVFD), CVFD(_xCVFD) {}
   inline friend a_Inst * CVFD (Inst _xCVFD)
      { return new Inst_CVFD (_xCVFD); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::CVIC Inst'
///////////////////////////////////////////////////////////////////////////////
class Inst_CVIC : public a_Inst {
public:
   Inst CVIC; 
   inline Inst_CVIC (Inst _xCVIC)
      : a_Inst(a_Inst::tag_CVIC), CVIC(_xCVIC) {}
   inline friend a_Inst * CVIC (Inst _xCVIC)
      { return new Inst_CVIC (_xCVIC); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::CVID Inst'
///////////////////////////////////////////////////////////////////////////////
class Inst_CVID : public a_Inst {
public:
   Inst CVID; 
   inline Inst_CVID (Inst _xCVID)
      : a_Inst(a_Inst::tag_CVID), CVID(_xCVID) {}
   inline friend a_Inst * CVID (Inst _xCVID)
      { return new Inst_CVID (_xCVID); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::CVIS Inst'
///////////////////////////////////////////////////////////////////////////////
class Inst_CVIS : public a_Inst {
public:
   Inst CVIS; 
   inline Inst_CVIS (Inst _xCVIS)
      : a_Inst(a_Inst::tag_CVIS), CVIS(_xCVIS) {}
   inline friend a_Inst * CVIS (Inst _xCVIS)
      { return new Inst_CVIS (_xCVIS); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::CVIU Inst'
///////////////////////////////////////////////////////////////////////////////
class Inst_CVIU : public a_Inst {
public:
   Inst CVIU; 
   inline Inst_CVIU (Inst _xCVIU)
      : a_Inst(a_Inst::tag_CVIU), CVIU(_xCVIU) {}
   inline friend a_Inst * CVIU (Inst _xCVIU)
      { return new Inst_CVIU (_xCVIU); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::CVPU Inst'
///////////////////////////////////////////////////////////////////////////////
class Inst_CVPU : public a_Inst {
public:
   Inst CVPU; 
   inline Inst_CVPU (Inst _xCVPU)
      : a_Inst(a_Inst::tag_CVPU), CVPU(_xCVPU) {}
   inline friend a_Inst * CVPU (Inst _xCVPU)
      { return new Inst_CVPU (_xCVPU); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::CVSI Inst'
///////////////////////////////////////////////////////////////////////////////
class Inst_CVSI : public a_Inst {
public:
   Inst CVSI; 
   inline Inst_CVSI (Inst _xCVSI)
      : a_Inst(a_Inst::tag_CVSI), CVSI(_xCVSI) {}
   inline friend a_Inst * CVSI (Inst _xCVSI)
      { return new Inst_CVSI (_xCVSI); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::CVSU Inst'
///////////////////////////////////////////////////////////////////////////////
class Inst_CVSU : public a_Inst {
public:
   Inst CVSU; 
   inline Inst_CVSU (Inst _xCVSU)
      : a_Inst(a_Inst::tag_CVSU), CVSU(_xCVSU) {}
   inline friend a_Inst * CVSU (Inst _xCVSU)
      { return new Inst_CVSU (_xCVSU); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::CVUC Inst'
///////////////////////////////////////////////////////////////////////////////
class Inst_CVUC : public a_Inst {
public:
   Inst CVUC; 
   inline Inst_CVUC (Inst _xCVUC)
      : a_Inst(a_Inst::tag_CVUC), CVUC(_xCVUC) {}
   inline friend a_Inst * CVUC (Inst _xCVUC)
      { return new Inst_CVUC (_xCVUC); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::CVUI Inst'
///////////////////////////////////////////////////////////////////////////////
class Inst_CVUI : public a_Inst {
public:
   Inst CVUI; 
   inline Inst_CVUI (Inst _xCVUI)
      : a_Inst(a_Inst::tag_CVUI), CVUI(_xCVUI) {}
   inline friend a_Inst * CVUI (Inst _xCVUI)
      { return new Inst_CVUI (_xCVUI); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::CVUP Inst'
///////////////////////////////////////////////////////////////////////////////
class Inst_CVUP : public a_Inst {
public:
   Inst CVUP; 
   inline Inst_CVUP (Inst _xCVUP)
      : a_Inst(a_Inst::tag_CVUP), CVUP(_xCVUP) {}
   inline friend a_Inst * CVUP (Inst _xCVUP)
      { return new Inst_CVUP (_xCVUP); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::CVUS Inst'
///////////////////////////////////////////////////////////////////////////////
class Inst_CVUS : public a_Inst {
public:
   Inst CVUS; 
   inline Inst_CVUS (Inst _xCVUS)
      : a_Inst(a_Inst::tag_CVUS), CVUS(_xCVUS) {}
   inline friend a_Inst * CVUS (Inst _xCVUS)
      { return new Inst_CVUS (_xCVUS); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::DIVD (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_DIVD : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_DIVD (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_DIVD), _1(_x1), _2(_x2) {}
   inline friend a_Inst * DIVD (Inst _x1, Inst _x2)
      { return new Inst_DIVD (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::DIVF (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_DIVF : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_DIVF (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_DIVF), _1(_x1), _2(_x2) {}
   inline friend a_Inst * DIVF (Inst _x1, Inst _x2)
      { return new Inst_DIVF (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::DIVI (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_DIVI : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_DIVI (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_DIVI), _1(_x1), _2(_x2) {}
   inline friend a_Inst * DIVI (Inst _x1, Inst _x2)
      { return new Inst_DIVI (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::DIVU (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_DIVU : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_DIVU (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_DIVU), _1(_x1), _2(_x2) {}
   inline friend a_Inst * DIVU (Inst _x1, Inst _x2)
      { return new Inst_DIVU (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::EQD (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_EQD : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_EQD (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_EQD), _1(_x1), _2(_x2) {}
   inline friend a_Inst * EQD (Inst _x1, Inst _x2)
      { return new Inst_EQD (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::EQF (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_EQF : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_EQF (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_EQF), _1(_x1), _2(_x2) {}
   inline friend a_Inst * EQF (Inst _x1, Inst _x2)
      { return new Inst_EQF (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::EQI (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_EQI : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_EQI (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_EQI), _1(_x1), _2(_x2) {}
   inline friend a_Inst * EQI (Inst _x1, Inst _x2)
      { return new Inst_EQI (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::GED (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_GED : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_GED (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_GED), _1(_x1), _2(_x2) {}
   inline friend a_Inst * GED (Inst _x1, Inst _x2)
      { return new Inst_GED (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::GEF (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_GEF : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_GEF (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_GEF), _1(_x1), _2(_x2) {}
   inline friend a_Inst * GEF (Inst _x1, Inst _x2)
      { return new Inst_GEF (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::GEI (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_GEI : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_GEI (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_GEI), _1(_x1), _2(_x2) {}
   inline friend a_Inst * GEI (Inst _x1, Inst _x2)
      { return new Inst_GEI (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::GEU (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_GEU : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_GEU (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_GEU), _1(_x1), _2(_x2) {}
   inline friend a_Inst * GEU (Inst _x1, Inst _x2)
      { return new Inst_GEU (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::GTD (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_GTD : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_GTD (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_GTD), _1(_x1), _2(_x2) {}
   inline friend a_Inst * GTD (Inst _x1, Inst _x2)
      { return new Inst_GTD (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::GTF (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_GTF : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_GTF (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_GTF), _1(_x1), _2(_x2) {}
   inline friend a_Inst * GTF (Inst _x1, Inst _x2)
      { return new Inst_GTF (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::GTI (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_GTI : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_GTI (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_GTI), _1(_x1), _2(_x2) {}
   inline friend a_Inst * GTI (Inst _x1, Inst _x2)
      { return new Inst_GTI (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::GTU (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_GTU : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_GTU (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_GTU), _1(_x1), _2(_x2) {}
   inline friend a_Inst * GTU (Inst _x1, Inst _x2)
      { return new Inst_GTU (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::INDIRB Inst'
///////////////////////////////////////////////////////////////////////////////
class Inst_INDIRB : public a_Inst {
public:
   Inst INDIRB; 
   inline Inst_INDIRB (Inst _xINDIRB)
      : a_Inst(a_Inst::tag_INDIRB), INDIRB(_xINDIRB) {}
   inline friend a_Inst * INDIRB (Inst _xINDIRB)
      { return new Inst_INDIRB (_xINDIRB); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::INDIRC Inst'
///////////////////////////////////////////////////////////////////////////////
class Inst_INDIRC : public a_Inst {
public:
   Inst INDIRC; 
   inline Inst_INDIRC (Inst _xINDIRC)
      : a_Inst(a_Inst::tag_INDIRC), INDIRC(_xINDIRC) {}
   inline friend a_Inst * INDIRC (Inst _xINDIRC)
      { return new Inst_INDIRC (_xINDIRC); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::INDIRD Inst'
///////////////////////////////////////////////////////////////////////////////
class Inst_INDIRD : public a_Inst {
public:
   Inst INDIRD; 
   inline Inst_INDIRD (Inst _xINDIRD)
      : a_Inst(a_Inst::tag_INDIRD), INDIRD(_xINDIRD) {}
   inline friend a_Inst * INDIRD (Inst _xINDIRD)
      { return new Inst_INDIRD (_xINDIRD); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::INDIRF Inst'
///////////////////////////////////////////////////////////////////////////////
class Inst_INDIRF : public a_Inst {
public:
   Inst INDIRF; 
   inline Inst_INDIRF (Inst _xINDIRF)
      : a_Inst(a_Inst::tag_INDIRF), INDIRF(_xINDIRF) {}
   inline friend a_Inst * INDIRF (Inst _xINDIRF)
      { return new Inst_INDIRF (_xINDIRF); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::INDIRI Inst'
///////////////////////////////////////////////////////////////////////////////
class Inst_INDIRI : public a_Inst {
public:
   Inst INDIRI; 
   inline Inst_INDIRI (Inst _xINDIRI)
      : a_Inst(a_Inst::tag_INDIRI), INDIRI(_xINDIRI) {}
   inline friend a_Inst * INDIRI (Inst _xINDIRI)
      { return new Inst_INDIRI (_xINDIRI); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::INDIRP Inst'
///////////////////////////////////////////////////////////////////////////////
class Inst_INDIRP : public a_Inst {
public:
   Inst INDIRP; 
   inline Inst_INDIRP (Inst _xINDIRP)
      : a_Inst(a_Inst::tag_INDIRP), INDIRP(_xINDIRP) {}
   inline friend a_Inst * INDIRP (Inst _xINDIRP)
      { return new Inst_INDIRP (_xINDIRP); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::INDIRS Inst'
///////////////////////////////////////////////////////////////////////////////
class Inst_INDIRS : public a_Inst {
public:
   Inst INDIRS; 
   inline Inst_INDIRS (Inst _xINDIRS)
      : a_Inst(a_Inst::tag_INDIRS), INDIRS(_xINDIRS) {}
   inline friend a_Inst * INDIRS (Inst _xINDIRS)
      { return new Inst_INDIRS (_xINDIRS); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::JUMPV Inst'
///////////////////////////////////////////////////////////////////////////////
class Inst_JUMPV : public a_Inst {
public:
   Inst JUMPV; 
   inline Inst_JUMPV (Inst _xJUMPV)
      : a_Inst(a_Inst::tag_JUMPV), JUMPV(_xJUMPV) {}
   inline friend a_Inst * JUMPV (Inst _xJUMPV)
      { return new Inst_JUMPV (_xJUMPV); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::LED (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_LED : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_LED (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_LED), _1(_x1), _2(_x2) {}
   inline friend a_Inst * LED (Inst _x1, Inst _x2)
      { return new Inst_LED (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::LEF (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_LEF : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_LEF (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_LEF), _1(_x1), _2(_x2) {}
   inline friend a_Inst * LEF (Inst _x1, Inst _x2)
      { return new Inst_LEF (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::LEI (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_LEI : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_LEI (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_LEI), _1(_x1), _2(_x2) {}
   inline friend a_Inst * LEI (Inst _x1, Inst _x2)
      { return new Inst_LEI (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::LEU (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_LEU : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_LEU (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_LEU), _1(_x1), _2(_x2) {}
   inline friend a_Inst * LEU (Inst _x1, Inst _x2)
      { return new Inst_LEU (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::LOADB Inst'
///////////////////////////////////////////////////////////////////////////////
class Inst_LOADB : public a_Inst {
public:
   Inst LOADB; 
   inline Inst_LOADB (Inst _xLOADB)
      : a_Inst(a_Inst::tag_LOADB), LOADB(_xLOADB) {}
   inline friend a_Inst * LOADB (Inst _xLOADB)
      { return new Inst_LOADB (_xLOADB); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::LOADC Inst'
///////////////////////////////////////////////////////////////////////////////
class Inst_LOADC : public a_Inst {
public:
   Inst LOADC; 
   inline Inst_LOADC (Inst _xLOADC)
      : a_Inst(a_Inst::tag_LOADC), LOADC(_xLOADC) {}
   inline friend a_Inst * LOADC (Inst _xLOADC)
      { return new Inst_LOADC (_xLOADC); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::LOADD Inst'
///////////////////////////////////////////////////////////////////////////////
class Inst_LOADD : public a_Inst {
public:
   Inst LOADD; 
   inline Inst_LOADD (Inst _xLOADD)
      : a_Inst(a_Inst::tag_LOADD), LOADD(_xLOADD) {}
   inline friend a_Inst * LOADD (Inst _xLOADD)
      { return new Inst_LOADD (_xLOADD); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::LOADF Inst'
///////////////////////////////////////////////////////////////////////////////
class Inst_LOADF : public a_Inst {
public:
   Inst LOADF; 
   inline Inst_LOADF (Inst _xLOADF)
      : a_Inst(a_Inst::tag_LOADF), LOADF(_xLOADF) {}
   inline friend a_Inst * LOADF (Inst _xLOADF)
      { return new Inst_LOADF (_xLOADF); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::LOADI Inst'
///////////////////////////////////////////////////////////////////////////////
class Inst_LOADI : public a_Inst {
public:
   Inst LOADI; 
   inline Inst_LOADI (Inst _xLOADI)
      : a_Inst(a_Inst::tag_LOADI), LOADI(_xLOADI) {}
   inline friend a_Inst * LOADI (Inst _xLOADI)
      { return new Inst_LOADI (_xLOADI); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::LOADP Inst'
///////////////////////////////////////////////////////////////////////////////
class Inst_LOADP : public a_Inst {
public:
   Inst LOADP; 
   inline Inst_LOADP (Inst _xLOADP)
      : a_Inst(a_Inst::tag_LOADP), LOADP(_xLOADP) {}
   inline friend a_Inst * LOADP (Inst _xLOADP)
      { return new Inst_LOADP (_xLOADP); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::LOADS Inst'
///////////////////////////////////////////////////////////////////////////////
class Inst_LOADS : public a_Inst {
public:
   Inst LOADS; 
   inline Inst_LOADS (Inst _xLOADS)
      : a_Inst(a_Inst::tag_LOADS), LOADS(_xLOADS) {}
   inline friend a_Inst * LOADS (Inst _xLOADS)
      { return new Inst_LOADS (_xLOADS); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::LOADU Inst'
///////////////////////////////////////////////////////////////////////////////
class Inst_LOADU : public a_Inst {
public:
   Inst LOADU; 
   inline Inst_LOADU (Inst _xLOADU)
      : a_Inst(a_Inst::tag_LOADU), LOADU(_xLOADU) {}
   inline friend a_Inst * LOADU (Inst _xLOADU)
      { return new Inst_LOADU (_xLOADU); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::LSHI (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_LSHI : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_LSHI (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_LSHI), _1(_x1), _2(_x2) {}
   inline friend a_Inst * LSHI (Inst _x1, Inst _x2)
      { return new Inst_LSHI (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::LSHU (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_LSHU : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_LSHU (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_LSHU), _1(_x1), _2(_x2) {}
   inline friend a_Inst * LSHU (Inst _x1, Inst _x2)
      { return new Inst_LSHU (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::LTD (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_LTD : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_LTD (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_LTD), _1(_x1), _2(_x2) {}
   inline friend a_Inst * LTD (Inst _x1, Inst _x2)
      { return new Inst_LTD (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::LTF (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_LTF : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_LTF (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_LTF), _1(_x1), _2(_x2) {}
   inline friend a_Inst * LTF (Inst _x1, Inst _x2)
      { return new Inst_LTF (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::LTI (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_LTI : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_LTI (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_LTI), _1(_x1), _2(_x2) {}
   inline friend a_Inst * LTI (Inst _x1, Inst _x2)
      { return new Inst_LTI (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::LTU (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_LTU : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_LTU (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_LTU), _1(_x1), _2(_x2) {}
   inline friend a_Inst * LTU (Inst _x1, Inst _x2)
      { return new Inst_LTU (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::MODI (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_MODI : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_MODI (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_MODI), _1(_x1), _2(_x2) {}
   inline friend a_Inst * MODI (Inst _x1, Inst _x2)
      { return new Inst_MODI (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::MODU (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_MODU : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_MODU (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_MODU), _1(_x1), _2(_x2) {}
   inline friend a_Inst * MODU (Inst _x1, Inst _x2)
      { return new Inst_MODU (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::MULD (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_MULD : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_MULD (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_MULD), _1(_x1), _2(_x2) {}
   inline friend a_Inst * MULD (Inst _x1, Inst _x2)
      { return new Inst_MULD (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::MULF (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_MULF : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_MULF (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_MULF), _1(_x1), _2(_x2) {}
   inline friend a_Inst * MULF (Inst _x1, Inst _x2)
      { return new Inst_MULF (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::MULI (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_MULI : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_MULI (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_MULI), _1(_x1), _2(_x2) {}
   inline friend a_Inst * MULI (Inst _x1, Inst _x2)
      { return new Inst_MULI (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::MULU (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_MULU : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_MULU (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_MULU), _1(_x1), _2(_x2) {}
   inline friend a_Inst * MULU (Inst _x1, Inst _x2)
      { return new Inst_MULU (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::NED (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_NED : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_NED (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_NED), _1(_x1), _2(_x2) {}
   inline friend a_Inst * NED (Inst _x1, Inst _x2)
      { return new Inst_NED (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::NEF (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_NEF : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_NEF (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_NEF), _1(_x1), _2(_x2) {}
   inline friend a_Inst * NEF (Inst _x1, Inst _x2)
      { return new Inst_NEF (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::NEI (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_NEI : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_NEI (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_NEI), _1(_x1), _2(_x2) {}
   inline friend a_Inst * NEI (Inst _x1, Inst _x2)
      { return new Inst_NEI (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::NEGD Inst'
///////////////////////////////////////////////////////////////////////////////
class Inst_NEGD : public a_Inst {
public:
   Inst NEGD; 
   inline Inst_NEGD (Inst _xNEGD)
      : a_Inst(a_Inst::tag_NEGD), NEGD(_xNEGD) {}
   inline friend a_Inst * NEGD (Inst _xNEGD)
      { return new Inst_NEGD (_xNEGD); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::NEGF Inst'
///////////////////////////////////////////////////////////////////////////////
class Inst_NEGF : public a_Inst {
public:
   Inst NEGF; 
   inline Inst_NEGF (Inst _xNEGF)
      : a_Inst(a_Inst::tag_NEGF), NEGF(_xNEGF) {}
   inline friend a_Inst * NEGF (Inst _xNEGF)
      { return new Inst_NEGF (_xNEGF); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::NEGI Inst'
///////////////////////////////////////////////////////////////////////////////
class Inst_NEGI : public a_Inst {
public:
   Inst NEGI; 
   inline Inst_NEGI (Inst _xNEGI)
      : a_Inst(a_Inst::tag_NEGI), NEGI(_xNEGI) {}
   inline friend a_Inst * NEGI (Inst _xNEGI)
      { return new Inst_NEGI (_xNEGI); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::RETD Inst'
///////////////////////////////////////////////////////////////////////////////
class Inst_RETD : public a_Inst {
public:
   Inst RETD; 
   inline Inst_RETD (Inst _xRETD)
      : a_Inst(a_Inst::tag_RETD), RETD(_xRETD) {}
   inline friend a_Inst * RETD (Inst _xRETD)
      { return new Inst_RETD (_xRETD); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::RETF Inst'
///////////////////////////////////////////////////////////////////////////////
class Inst_RETF : public a_Inst {
public:
   Inst RETF; 
   inline Inst_RETF (Inst _xRETF)
      : a_Inst(a_Inst::tag_RETF), RETF(_xRETF) {}
   inline friend a_Inst * RETF (Inst _xRETF)
      { return new Inst_RETF (_xRETF); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::RETI Inst'
///////////////////////////////////////////////////////////////////////////////
class Inst_RETI : public a_Inst {
public:
   Inst RETI; 
   inline Inst_RETI (Inst _xRETI)
      : a_Inst(a_Inst::tag_RETI), RETI(_xRETI) {}
   inline friend a_Inst * RETI (Inst _xRETI)
      { return new Inst_RETI (_xRETI); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::RSHI (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_RSHI : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_RSHI (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_RSHI), _1(_x1), _2(_x2) {}
   inline friend a_Inst * RSHI (Inst _x1, Inst _x2)
      { return new Inst_RSHI (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::RSHU (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_RSHU : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_RSHU (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_RSHU), _1(_x1), _2(_x2) {}
   inline friend a_Inst * RSHU (Inst _x1, Inst _x2)
      { return new Inst_RSHU (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::SUBD (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_SUBD : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_SUBD (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_SUBD), _1(_x1), _2(_x2) {}
   inline friend a_Inst * SUBD (Inst _x1, Inst _x2)
      { return new Inst_SUBD (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::SUBF (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_SUBF : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_SUBF (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_SUBF), _1(_x1), _2(_x2) {}
   inline friend a_Inst * SUBF (Inst _x1, Inst _x2)
      { return new Inst_SUBF (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::SUBI (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_SUBI : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_SUBI (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_SUBI), _1(_x1), _2(_x2) {}
   inline friend a_Inst * SUBI (Inst _x1, Inst _x2)
      { return new Inst_SUBI (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::SUBP (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_SUBP : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_SUBP (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_SUBP), _1(_x1), _2(_x2) {}
   inline friend a_Inst * SUBP (Inst _x1, Inst _x2)
      { return new Inst_SUBP (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::SUBU (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_SUBU : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_SUBU (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_SUBU), _1(_x1), _2(_x2) {}
   inline friend a_Inst * SUBU (Inst _x1, Inst _x2)
      { return new Inst_SUBU (_x1, _x2); }
};



void compile (Inst e)
{
   extern void  _s_p_a_r_c_2co_X1_rewrite(Inst & );
   _s_p_a_r_c_2co_X1_rewrite(e); 
}
class _s_p_a_r_c_2co_X1 : public BURS {
private:
   _s_p_a_r_c_2co_X1(const _s_p_a_r_c_2co_X1&);               // no copy constructor
   void operator = (const _s_p_a_r_c_2co_X1&); // no assignment
public:
   struct _s_p_a_r_c_2co_X1_StateRec * stack__, * stack_top__;
          void labeler(Inst & redex);
   inline virtual void operator () (Inst & redex) { labeler(redex); }
          void  reduce(Inst redex);
private: 
   public:
      inline _s_p_a_r_c_2co_X1() {}
};
void  _s_p_a_r_c_2co_X1_rewrite(Inst &  _x_) 
{  _s_p_a_r_c_2co_X1 _r_;
   _r_(_x_); return _r_.reduce(_x_);
}


///////////////////////////////////////////////////////////////////////////////
// State record for rewrite class _s_p_a_r_c_2co_X1
///////////////////////////////////////////////////////////////////////////////
struct _s_p_a_r_c_2co_X1_StateRec {
   TreeTables::Cost cost[4]; // cost for each non-terminal
   struct { // accept rule number
      unsigned int _stmt : 4;
      unsigned int _con : 3;
      unsigned int _reg : 4;
   } rule;
};

///////////////////////////////////////////////////////////////////////////////
// Accept rules tables for rewrite class _s_p_a_r_c_2co_X1
///////////////////////////////////////////////////////////////////////////////
const char _s_p_a_r_c_2co_X1_stmt_accept[] = { -1, 17, 11, 10, 9, 8, 7, 6 };

const char _s_p_a_r_c_2co_X1_con_accept[] = { -1, 16, 15, 14, 13, 12 };

const char _s_p_a_r_c_2co_X1_reg_accept[] = { -1, 22, 21, 20, 19, 18, 5, 4, 3, 2, 1, 0 };

///////////////////////////////////////////////////////////////////////////////
// Closure methods for rewrite class _s_p_a_r_c_2co_X1
///////////////////////////////////////////////////////////////////////////////
static void _s_p_a_r_c_2co_X1_reg_closure(Inst redex,int cost);

static void _s_p_a_r_c_2co_X1_reg_closure(Inst redex,int cost__)
{
   _s_p_a_r_c_2co_X1_StateRec * _state_rec = (_s_p_a_r_c_2co_X1_StateRec *)(redex->get_state_rec());
   if (cost__ + 0 < _state_rec->cost[2])
   {  _state_rec->cost[2] = cost__ + 0;
      _state_rec->rule._stmt = 1;
   }
}

void _s_p_a_r_c_2co_X1::labeler (Inst redex)
{
   int cost__;
   _s_p_a_r_c_2co_X1_StateRec * _state_rec = (_s_p_a_r_c_2co_X1_StateRec *)mem[sizeof(_s_p_a_r_c_2co_X1_StateRec)];
   redex->set_state_rec(_state_rec);
   _state_rec->cost[0] = 0;
   _state_rec->cost[1] = 
   _state_rec->cost[2] = 
   _state_rec->cost[3] = 32767;
   {
      if (boxed(redex)) {
         switch (redex->untag()) {
            case a_Inst::tag_ADDD: {
               // Inst (12)
               } break;
            case a_Inst::tag_ADDF: {
               // Inst (13)
               } break;
            case a_Inst::tag_ADDI: {
               // Inst (14)
               } break;
            case a_Inst::tag_ADDP: {
               // Inst (15)
               } break;
            case a_Inst::tag_ADDU: {
               // Inst (16)
               } break;
            case a_Inst::tag_ARGB: {
               // Inst (17)
               } break;
            case a_Inst::tag_ARGD: {
               // Inst (18)
               } break;
            case a_Inst::tag_ARGF: {
               // Inst (19)
               } break;
            case a_Inst::tag_ARGI: {
               // Inst (20)
               } break;
            case a_Inst::tag_ARGP: {
               // Inst (21)
               } break;
            case a_Inst::tag_ASGNB: {
               // Inst (22)
               } break;
            case a_Inst::tag_ASGNC: {
               // Inst (23)
               if (boxed(_ASGNC(redex)->_1)) {} else {
                  switch ((int)_ASGNC(redex)->_1) {
                     case (int)VREGP: {
                        if (cost__ + 0 < state_rec->cost[2])
                        {   _state_rec->cost[2] = cost__ + 0;
                            _state_rec->rule._stmt = 7;
                           _s_p_a_r_c_2co_X1_stmt_closure(redex, cost__ + 0);
                        }} break;
                     default: {} break;
                  }
               }
               } break;
            case a_Inst::tag_ASGND: {
               // Inst (24)
               if (boxed(_ASGND(redex)->_1)) {} else {
                  switch ((int)_ASGND(redex)->_1) {
                     case (int)VREGP: {
                        if (cost__ + 0 < state_rec->cost[2])
                        {   _state_rec->cost[2] = cost__ + 0;
                            _state_rec->rule._stmt = 6;
                           _s_p_a_r_c_2co_X1_stmt_closure(redex, cost__ + 0);
                        }} break;
                     default: {} break;
                  }
               }
               } break;
            case a_Inst::tag_ASGNF: {
               // Inst (25)
               if (boxed(_ASGNF(redex)->_1)) {} else {
                  switch ((int)_ASGNF(redex)->_1) {
                     case (int)VREGP: {
                        if (cost__ + 0 < state_rec->cost[2])
                        {   _state_rec->cost[2] = cost__ + 0;
                            _state_rec->rule._stmt = 5;
                           _s_p_a_r_c_2co_X1_stmt_closure(redex, cost__ + 0);
                        }} break;
                     default: {} break;
                  }
               }
               } break;
            case a_Inst::tag_ASGNI: {
               // Inst (26)
               if (boxed(_ASGNI(redex)->_1)) {} else {
                  switch ((int)_ASGNI(redex)->_1) {
                     case (int)VREGP: {
                        if (cost__ + 0 < state_rec->cost[2])
                        {   _state_rec->cost[2] = cost__ + 0;
                            _state_rec->rule._stmt = 4;
                           _s_p_a_r_c_2co_X1_stmt_closure(redex, cost__ + 0);
                        }} break;
                     default: {} break;
                  }
               }
               } break;
            case a_Inst::tag_ASGNP: {
               // Inst (27)
               if (boxed(_ASGNP(redex)->_1)) {} else {
                  switch ((int)_ASGNP(redex)->_1) {
                     case (int)VREGP: {
                        if (cost__ + 0 < state_rec->cost[2])
                        {   _state_rec->cost[2] = cost__ + 0;
                            _state_rec->rule._stmt = 3;
                           _s_p_a_r_c_2co_X1_stmt_closure(redex, cost__ + 0);
                        }} break;
                     default: {} break;
                  }
               }
               } break;
            case a_Inst::tag_ASGNS: {
               // Inst (28)
               if (boxed(_ASGNS(redex)->_1)) {} else {
                  switch ((int)_ASGNS(redex)->_1) {
                     case (int)VREGP: {
                        if (cost__ + 0 < state_rec->cost[2])
                        {   _state_rec->cost[2] = cost__ + 0;
                            _state_rec->rule._stmt = 2;
                           _s_p_a_r_c_2co_X1_stmt_closure(redex, cost__ + 0);
                        }} break;
                     default: {} break;
                  }
               }
               } break;
            case a_Inst::tag_BANDU: {
               // Inst (29)
               } break;
            case a_Inst::tag_BCOMU: {
               // Inst (30)
               } break;
            case a_Inst::tag_BORU: {
               // Inst (31)
               } break;
            case a_Inst::tag_BXORU: {
               // Inst (32)
               } break;
            case a_Inst::tag_CALLB: {
               // Inst (33)
               } break;
            case a_Inst::tag_CALLD: {
               // Inst (34)
               } break;
            case a_Inst::tag_CALLF: {
               // Inst (35)
               } break;
            case a_Inst::tag_CALLI: {
               // Inst (36)
               } break;
            case a_Inst::tag_CALLV: {
               // Inst (37)
               } break;
            case a_Inst::tag_CVCI: {
               // Inst (38)
               } break;
            case a_Inst::tag_CVCU: {
               // Inst (39)
               } break;
            case a_Inst::tag_CVDF: {
               // Inst (40)
               } break;
            case a_Inst::tag_CVDI: {
               // Inst (41)
               } break;
            case a_Inst::tag_CVFD: {
               // Inst (42)
               } break;
            case a_Inst::tag_CVIC: {
               // Inst (43)
               } break;
            case a_Inst::tag_CVID: {
               // Inst (44)
               } break;
            case a_Inst::tag_CVIS: {
               // Inst (45)
               } break;
            case a_Inst::tag_CVIU: {
               // Inst (46)
               int _X2 = notarget(redex);
               if (cost__ + _X2 < state_rec->cost[1])
               {   _state_rec->cost[1] = cost__ + _X2;
                   _state_rec->rule._reg = 5;
                  _s_p_a_r_c_2co_X1_reg_closure(redex, cost__ + _X2);
               }} break;
            case a_Inst::tag_CVPU: {
               // Inst (47)
               int _X3 = notarget(redex);
               if (cost__ + _X3 < state_rec->cost[1])
               {   _state_rec->cost[1] = cost__ + _X3;
                   _state_rec->rule._reg = 4;
                  _s_p_a_r_c_2co_X1_reg_closure(redex, cost__ + _X3);
               }} break;
            case a_Inst::tag_CVSI: {
               // Inst (48)
               } break;
            case a_Inst::tag_CVSU: {
               // Inst (49)
               } break;
            case a_Inst::tag_CVUC: {
               // Inst (50)
               } break;
            case a_Inst::tag_CVUI: {
               // Inst (51)
               int _X4 = notarget(redex);
               if (cost__ + _X4 < state_rec->cost[1])
               {   _state_rec->cost[1] = cost__ + _X4;
                   _state_rec->rule._reg = 3;
                  _s_p_a_r_c_2co_X1_reg_closure(redex, cost__ + _X4);
               }} break;
            case a_Inst::tag_CVUP: {
               // Inst (52)
               int _X5 = notarget(redex);
               if (cost__ + _X5 < state_rec->cost[1])
               {   _state_rec->cost[1] = cost__ + _X5;
                   _state_rec->rule._reg = 2;
                  _s_p_a_r_c_2co_X1_reg_closure(redex, cost__ + _X5);
               }} break;
            case a_Inst::tag_CVUS: {
               // Inst (53)
               } break;
            case a_Inst::tag_DIVD: {
               // Inst (54)
               } break;
            case a_Inst::tag_DIVF: {
               // Inst (55)
               } break;
            case a_Inst::tag_DIVI: {
               // Inst (56)
               } break;
            case a_Inst::tag_DIVU: {
               // Inst (57)
               } break;
            case a_Inst::tag_EQD: {
               // Inst (58)
               } break;
            case a_Inst::tag_EQF: {
               // Inst (59)
               } break;
            case a_Inst::tag_EQI: {
               // Inst (60)
               } break;
            case a_Inst::tag_GED: {
               // Inst (61)
               } break;
            case a_Inst::tag_GEF: {
               // Inst (62)
               } break;
            case a_Inst::tag_GEI: {
               // Inst (63)
               } break;
            case a_Inst::tag_GEU: {
               // Inst (64)
               } break;
            case a_Inst::tag_GTD: {
               // Inst (65)
               } break;
            case a_Inst::tag_GTF: {
               // Inst (66)
               } break;
            case a_Inst::tag_GTI: {
               // Inst (67)
               } break;
            case a_Inst::tag_GTU: {
               // Inst (68)
               } break;
            case a_Inst::tag_INDIRB: {
               // Inst (69)
               } break;
            case a_Inst::tag_INDIRC: {
               // Inst (70)
               if (boxed(_INDIRC(redex)->INDIRC)) {} else {
                  switch ((int)_INDIRC(redex)->INDIRC) {
                     case (int)VREGP: {
                        if (cost__ + 0 < state_rec->cost[1])
                        {   _state_rec->cost[1] = cost__ + 0;
                            _state_rec->rule._reg = 11;
                           _s_p_a_r_c_2co_X1_reg_closure(redex, cost__ + 0);
                        }} break;
                     default: {} break;
                  }
               }
               } break;
            case a_Inst::tag_INDIRD: {
               // Inst (71)
               if (boxed(_INDIRD(redex)->INDIRD)) {} else {
                  switch ((int)_INDIRD(redex)->INDIRD) {
                     case (int)VREGP: {
                        if (cost__ + 0 < state_rec->cost[1])
                        {   _state_rec->cost[1] = cost__ + 0;
                            _state_rec->rule._reg = 10;
                           _s_p_a_r_c_2co_X1_reg_closure(redex, cost__ + 0);
                        }} break;
                     default: {} break;
                  }
               }
               } break;
            case a_Inst::tag_INDIRF: {
               // Inst (72)
               if (boxed(_INDIRF(redex)->INDIRF)) {} else {
                  switch ((int)_INDIRF(redex)->INDIRF) {
                     case (int)VREGP: {
                        if (cost__ + 0 < state_rec->cost[1])
                        {   _state_rec->cost[1] = cost__ + 0;
                            _state_rec->rule._reg = 9;
                           _s_p_a_r_c_2co_X1_reg_closure(redex, cost__ + 0);
                        }} break;
                     default: {} break;
                  }
               }
               } break;
            case a_Inst::tag_INDIRI: {
               // Inst (73)
               if (boxed(_INDIRI(redex)->INDIRI)) {} else {
                  switch ((int)_INDIRI(redex)->INDIRI) {
                     case (int)VREGP: {
                        if (cost__ + 0 < state_rec->cost[1])
                        {   _state_rec->cost[1] = cost__ + 0;
                            _state_rec->rule._reg = 8;
                           _s_p_a_r_c_2co_X1_reg_closure(redex, cost__ + 0);
                        }} break;
                     default: {} break;
                  }
               }
               } break;
            case a_Inst::tag_INDIRP: {
               // Inst (74)
               if (boxed(_INDIRP(redex)->INDIRP)) {} else {
                  switch ((int)_INDIRP(redex)->INDIRP) {
                     case (int)VREGP: {
                        if (cost__ + 0 < state_rec->cost[1])
                        {   _state_rec->cost[1] = cost__ + 0;
                            _state_rec->rule._reg = 7;
                           _s_p_a_r_c_2co_X1_reg_closure(redex, cost__ + 0);
                        }} break;
                     default: {} break;
                  }
               }
               } break;
            case a_Inst::tag_INDIRS: {
               // Inst (75)
               if (boxed(_INDIRS(redex)->INDIRS)) {} else {
                  switch ((int)_INDIRS(redex)->INDIRS) {
                     case (int)VREGP: {
                        if (cost__ + 0 < state_rec->cost[1])
                        {   _state_rec->cost[1] = cost__ + 0;
                            _state_rec->rule._reg = 6;
                           _s_p_a_r_c_2co_X1_reg_closure(redex, cost__ + 0);
                        }} break;
                     default: {} break;
                  }
               }
               } break;
            case a_Inst::tag_JUMPV: {
               // Inst (76)
               } break;
            case a_Inst::tag_LED: {
               // Inst (77)
               } break;
            case a_Inst::tag_LEF: {
               // Inst (78)
               } break;
            case a_Inst::tag_LEI: {
               // Inst (79)
               } break;
            case a_Inst::tag_LEU: {
               // Inst (80)
               } break;
            case a_Inst::tag_LOADB: {
               // Inst (81)
               } break;
            case a_Inst::tag_LOADC: {
               // Inst (82)
               } break;
            case a_Inst::tag_LOADD: {
               // Inst (83)
               } break;
            case a_Inst::tag_LOADF: {
               // Inst (84)
               } break;
            case a_Inst::tag_LOADI: {
               // Inst (85)
               } break;
            case a_Inst::tag_LOADP: {
               // Inst (86)
               } break;
            case a_Inst::tag_LOADS: {
               // Inst (87)
               } break;
            case a_Inst::tag_LOADU: {
               // Inst (88)
               } break;
            case a_Inst::tag_LSHI: {
               // Inst (89)
               } break;
            case a_Inst::tag_LSHU: {
               // Inst (90)
               } break;
            case a_Inst::tag_LTD: {
               // Inst (91)
               } break;
            case a_Inst::tag_LTF: {
               // Inst (92)
               } break;
            case a_Inst::tag_LTI: {
               // Inst (93)
               } break;
            case a_Inst::tag_LTU: {
               // Inst (94)
               } break;
            case a_Inst::tag_MODI: {
               // Inst (95)
               } break;
            case a_Inst::tag_MODU: {
               // Inst (96)
               } break;
            case a_Inst::tag_MULD: {
               // Inst (97)
               } break;
            case a_Inst::tag_MULF: {
               // Inst (98)
               } break;
            case a_Inst::tag_MULI: {
               // Inst (99)
               } break;
            case a_Inst::tag_MULU: {
               // Inst (100)
               } break;
            case a_Inst::tag_NED: {
               // Inst (101)
               } break;
            case a_Inst::tag_NEF: {
               // Inst (102)
               } break;
            case a_Inst::tag_NEI: {
               // Inst (103)
               } break;
            case a_Inst::tag_NEGD: {
               // Inst (104)
               } break;
            case a_Inst::tag_NEGF: {
               // Inst (105)
               } break;
            case a_Inst::tag_NEGI: {
               // Inst (106)
               } break;
            case a_Inst::tag_RETD: {
               // Inst (107)
               } break;
            case a_Inst::tag_RETF: {
               // Inst (108)
               } break;
            case a_Inst::tag_RETI: {
               // Inst (109)
               } break;
            case a_Inst::tag_RSHI: {
               // Inst (110)
               } break;
            case a_Inst::tag_RSHU: {
               // Inst (111)
               } break;
            case a_Inst::tag_SUBD: {
               // Inst (112)
               } break;
            case a_Inst::tag_SUBF: {
               // Inst (113)
               } break;
            case a_Inst::tag_SUBI: {
               // Inst (114)
               } break;
            case a_Inst::tag_SUBP: {
               // Inst (115)
               } break;
            default: {
               // Inst (116)
               } break;
         }
      } else {
         switch ((int)redex) {
            case (int)ADDRFP: {
               // Inst (0)
               } break;
            case (int)ADDRGP: {
               // Inst (1)
               if (cost__ + 0 < state_rec->cost[1])
               {   _state_rec->cost[1] = cost__ + 0;
                   _state_rec->rule._reg = 1;
                  _s_p_a_r_c_2co_X1_reg_closure(redex, cost__ + 0);
               }} break;
            case (int)ADDRLP: {
               // Inst (2)
               } break;
            case (int)CNSTC: {
               // Inst (3)
               if (cost__ + 0 < state_rec->cost[3])
               {   _state_rec->cost[3] = cost__ + 0;
                   _state_rec->rule._con = 5;
                  _s_p_a_r_c_2co_X1_con_closure(redex, cost__ + 0);
               }} break;
            case (int)CNSTD: {
               // Inst (4)
               } break;
            case (int)CNSTF: {
               // Inst (5)
               } break;
            case (int)CNSTI: {
               // Inst (6)
               if (cost__ + 0 < state_rec->cost[3])
               {   _state_rec->cost[3] = cost__ + 0;
                   _state_rec->rule._con = 4;
                  _s_p_a_r_c_2co_X1_con_closure(redex, cost__ + 0);
               }} break;
            case (int)CNSTP: {
               // Inst (7)
               if (cost__ + 0 < state_rec->cost[3])
               {   _state_rec->cost[3] = cost__ + 0;
                   _state_rec->rule._con = 3;
                  _s_p_a_r_c_2co_X1_con_closure(redex, cost__ + 0);
               }} break;
            case (int)CNSTS: {
               // Inst (8)
               if (cost__ + 0 < state_rec->cost[3])
               {   _state_rec->cost[3] = cost__ + 0;
                   _state_rec->rule._con = 2;
                  _s_p_a_r_c_2co_X1_con_closure(redex, cost__ + 0);
               }} break;
            case (int)CNSTU: {
               // Inst (9)
               if (cost__ + 0 < state_rec->cost[3])
               {   _state_rec->cost[3] = cost__ + 0;
                   _state_rec->rule._con = 1;
                  _s_p_a_r_c_2co_X1_con_closure(redex, cost__ + 0);
               }} break;
            case (int)LABELV: {
               // Inst (10)
               } break;
            default: {
               // Inst (11)
               } break;
         }
      }
   }
   
}

void _s_p_a_r_c_2co_X1::reduce(Inst redex)
{
   int r__ = (_s_p_a_r_c_2co_X1_StateRec *)(redex->get_state_rec());
   switch (r__) {
      case 22: { // ADDRGP
          "set %a,%%%c\n"  1; } break;
      case 21: { // CVUP reg
         reduce(_CVUP(redex)->CVUP);
          "%0"  notarget(a); } break;
      case 20: { // CVUI reg
         reduce(_CVUI(redex)->CVUI);
          "%0"  notarget(a); } break;
      case 19: { // CVPU reg
         reduce(_CVPU(redex)->CVPU);
          "%0"  notarget(a); } break;
      case 18: { // CVIU reg
         reduce(_CVIU(redex)->CVIU);
          "%0"  notarget(a); } break;
      case 17: { // reg
         reduce(redex);
         
         { redex = ""; r__ = 1; goto replacement__; }} break;
      case 16: { // CNSTU
         
         { redex = "%a"; r__ = 1; goto replacement__; }} break;
      case 15: { // CNSTS
         
         { redex = "%a"; r__ = 1; goto replacement__; }} break;
      case 14: { // CNSTP
         
         { redex = "%a"; r__ = 1; goto replacement__; }} break;
      case 13: { // CNSTI
         
         { redex = "%a"; r__ = 1; goto replacement__; }} break;
      case 12: { // CNSTC
         
         { redex = "%a"; r__ = 1; goto replacement__; }} break;
      case 11: { // ASGNS (VREGP, reg)
         reduce(_ASGNS(redex)->_2);
         
         { redex = "# write register\n"; r__ = 1; goto replacement__; }} break;
      case 10: { // ASGNP (VREGP, reg)
         reduce(_ASGNP(redex)->_2);
         
         { redex = "# write register\n"; r__ = 1; goto replacement__; }} break;
      case 9: { // ASGNI (VREGP, reg)
         reduce(_ASGNI(redex)->_2);
         
         { redex = "# write register\n"; r__ = 1; goto replacement__; }} break;
      case 8: { // ASGNF (VREGP, reg)
         reduce(_ASGNF(redex)->_2);
         
         { redex = "# write register\n"; r__ = 1; goto replacement__; }} break;
      case 7: { // ASGND (VREGP, reg)
         reduce(_ASGND(redex)->_2);
         
         { redex = "# write register\n"; r__ = 1; goto replacement__; }} break;
      case 6: { // ASGNC (VREGP, reg)
         reduce(_ASGNC(redex)->_2);
         
         { redex = "# write register\n"; r__ = 1; goto replacement__; }} break;
      case 5: { // INDIRS VREGP
         
         { redex = "# read register\n"; r__ = 1; goto replacement__; }} break;
      case 4: { // INDIRP VREGP
         
         { redex = "# read register\n"; r__ = 1; goto replacement__; }} break;
      case 3: { // INDIRI VREGP
         
         { redex = "# read register\n"; r__ = 1; goto replacement__; }} break;
      case 2: { // INDIRF VREGP
         
         { redex = "# read register\n"; r__ = 1; goto replacement__; }} break;
      case 1: { // INDIRD VREGP
         
         { redex = "# read register\n"; r__ = 1; goto replacement__; }} break;
      case 0: { // INDIRC VREGP
         
         { redex = "# read register\n"; r__ = 1; goto replacement__; }} break;
   }
}

/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 1511
Number of ifs generated      = 13
Number of switches generated = 14
Number of labels             = 0
Number of gotos              = 0
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
