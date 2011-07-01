///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.2.7),
//  last updated on Mar 20, 1996.
//  The original source file is "sparc3.pC".
///////////////////////////////////////////////////////////////////////////////

#define PROP_REWRITING_USED
#define PROP_EQUALITY_USED
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
   class Inst_INT;	// subclass for 'INT int'
   class Inst_LOAD;	// subclass for 'LOAD Inst'
   class Inst_ADD;	// subclass for 'ADD (Inst, Inst)'
   class Inst_SUB;	// subclass for 'SUB (Inst, Inst)'
   class Inst_DIV;	// subclass for 'DIV (Inst, Inst)'
   class Inst_MUL;	// subclass for 'MUL (Inst, Inst)'

///////////////////////////////////////////////////////////////////////////////
// Base class for datatype 'Inst'
///////////////////////////////////////////////////////////////////////////////
class a_Inst : public TermObj {
public:
   enum Tag_Inst {
      tag_INT = 0, tag_LOAD = 1, tag_ADD = 2, tag_SUB = 3, 
      tag_DIV = 4, tag_MUL = 5
   };

protected:
   const Tag_Inst _tag_;
   inline a_Inst(Tag_Inst _t_) : _tag_(_t_) {}
public:
   inline int untag() const { return _tag_; }
   inline friend int boxed(const a_Inst * x) { return 1; }
   inline friend int untag(const a_Inst * x) { return x->_tag_; }
   ////////////////////////////////////////////////////////////////////////////
   // Downcasting functions for Inst
   ////////////////////////////////////////////////////////////////////////////
   inline friend Inst_INT * _INT(Inst _x_) { return (Inst_INT *)_x_; }
   inline friend Inst_LOAD * _LOAD(Inst _x_) { return (Inst_LOAD *)_x_; }
   inline friend Inst_ADD * _ADD(Inst _x_) { return (Inst_ADD *)_x_; }
   inline friend Inst_SUB * _SUB(Inst _x_) { return (Inst_SUB *)_x_; }
   inline friend Inst_DIV * _DIV(Inst _x_) { return (Inst_DIV *)_x_; }
   inline friend Inst_MUL * _MUL(Inst _x_) { return (Inst_MUL *)_x_; }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::INT int'
///////////////////////////////////////////////////////////////////////////////
class Inst_INT : public a_Inst {
public:
   int INT; 
   inline Inst_INT (int _xINT)
      : a_Inst(a_Inst::tag_INT), INT(_xINT) {}
   inline friend a_Inst * INT (int _xINT)
      { return new Inst_INT (_xINT); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::LOAD Inst'
///////////////////////////////////////////////////////////////////////////////
class Inst_LOAD : public a_Inst {
public:
   Inst LOAD; 
   inline Inst_LOAD (Inst _xLOAD)
      : a_Inst(a_Inst::tag_LOAD), LOAD(_xLOAD) {}
   inline friend a_Inst * LOAD (Inst _xLOAD)
      { return new Inst_LOAD (_xLOAD); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::ADD (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_ADD : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_ADD (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_ADD), _1(_x1), _2(_x2) {}
   inline friend a_Inst * ADD (Inst _x1, Inst _x2)
      { return new Inst_ADD (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::SUB (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_SUB : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_SUB (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_SUB), _1(_x1), _2(_x2) {}
   inline friend a_Inst * SUB (Inst _x1, Inst _x2)
      { return new Inst_SUB (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::DIV (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_DIV : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_DIV (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_DIV), _1(_x1), _2(_x2) {}
   inline friend a_Inst * DIV (Inst _x1, Inst _x2)
      { return new Inst_DIV (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'Inst::MUL (Inst, Inst)'
///////////////////////////////////////////////////////////////////////////////
class Inst_MUL : public a_Inst {
public:
   Inst _1; Inst _2; 
   inline Inst_MUL (Inst _x1, Inst _x2)
      : a_Inst(a_Inst::tag_MUL), _1(_x1), _2(_x2) {}
   inline friend a_Inst * MUL (Inst _x1, Inst _x2)
      { return new Inst_MUL (_x1, _x2); }
};



void compile (Inst e)
{
   extern void  _s_p_a_r_c_3co_X1_rewrite(Inst & );
   _s_p_a_r_c_3co_X1_rewrite(e); 
}
class _s_p_a_r_c_3co_X1 : public BURS {
private:
   _s_p_a_r_c_3co_X1(const _s_p_a_r_c_3co_X1&);               // no copy constructor
   void operator = (const _s_p_a_r_c_3co_X1&); // no assignment
public:
   struct _s_p_a_r_c_3co_X1_StateRec * stack__, * stack_top__;
          void labeler(Inst & redex);
   inline virtual void operator () (Inst & redex) { labeler(redex); }
          void  reduce(Inst redex);
private: 
   public:
      inline _s_p_a_r_c_3co_X1() {}
};
void  _s_p_a_r_c_3co_X1_rewrite(Inst &  _x_) 
{  _s_p_a_r_c_3co_X1 _r_;
   _r_(_x_); return _r_.reduce(_x_);
}


///////////////////////////////////////////////////////////////////////////////
// State record for rewrite class _s_p_a_r_c_3co_X1
///////////////////////////////////////////////////////////////////////////////
struct _s_p_a_r_c_3co_X1_StateRec {
   TreeTables::Cost cost[3]; // cost for each non-terminal
   struct { // accept rule number
      unsigned int _exp : 3;
      unsigned int _reg : 3;
   } rule;
};

///////////////////////////////////////////////////////////////////////////////
// Accept rules tables for rewrite class _s_p_a_r_c_3co_X1
///////////////////////////////////////////////////////////////////////////////
const char _s_p_a_r_c_3co_X1_exp_accept[] = { -1, 8, 7, 6, 5, 4 };

const char _s_p_a_r_c_3co_X1_reg_accept[] = { -1, 3, 2, 1, 0 };

///////////////////////////////////////////////////////////////////////////////
// Closure methods for rewrite class _s_p_a_r_c_3co_X1
///////////////////////////////////////////////////////////////////////////////
static void _s_p_a_r_c_3co_X1_reg_closure(Inst redex,int cost);

static void _s_p_a_r_c_3co_X1_reg_closure(Inst redex,int cost__)
{
   _s_p_a_r_c_3co_X1_StateRec * _state_rec = (_s_p_a_r_c_3co_X1_StateRec *)(redex->get_state_rec());
   if (cost__ + 0 < _state_rec->cost[2])
   {  _state_rec->cost[2] = cost__ + 0;
      _state_rec->rule._exp = 1;
   }
}

void _s_p_a_r_c_3co_X1::labeler (Inst redex)
{
   int cost__;
   _s_p_a_r_c_3co_X1_StateRec * _state_rec = (_s_p_a_r_c_3co_X1_StateRec *)mem[sizeof(_s_p_a_r_c_3co_X1_StateRec)];
   redex->set_state_rec(_state_rec);
   _state_rec->cost[0] = 0;
   _state_rec->cost[1] = 
   _state_rec->cost[2] = 32767;
   {
      switch (redex->untag()) {
         case a_Inst::tag_INT: {
            // Inst (0)
            if (cost__ + 1 < state_rec->cost[1])
            {   _state_rec->cost[1] = cost__ + 1;
                _state_rec->rule._reg = 4;
               _s_p_a_r_c_3co_X1_reg_closure(redex, cost__ + 1);
            }} break;
         case a_Inst::tag_LOAD: {
            // Inst (1)
            switch (_LOAD(redex)->LOAD->untag()) {
               case a_Inst::tag_INT: {
                  if (cost__ + 2 < state_rec->cost[1])
                  {   _state_rec->cost[1] = cost__ + 2;
                      _state_rec->rule._reg = 3;
                     _s_p_a_r_c_3co_X1_reg_closure(redex, cost__ + 2);
                  }} break;
               case a_Inst::tag_ADD: {
                  if (cost__ + 3 < state_rec->cost[1])
                  {   _state_rec->cost[1] = cost__ + 3;
                      _state_rec->rule._reg = 2;
                     _s_p_a_r_c_3co_X1_reg_closure(redex, cost__ + 3);
                  }} break;
               default: {} break;
            }
            int _X2 = cost(_LOAD(redex)->LOAD);
            if (cost__ + _X2 < state_rec->cost[1])
            {   _state_rec->cost[1] = cost__ + _X2;
                _state_rec->rule._reg = 1;
               _s_p_a_r_c_3co_X1_reg_closure(redex, cost__ + _X2);
            }} break;
         case a_Inst::tag_ADD: {
            // Inst (2)
            if (cost__ + 1 < state_rec->cost[2])
            {   _state_rec->cost[2] = cost__ + 1;
                _state_rec->rule._exp = 4;
               _s_p_a_r_c_3co_X1_exp_closure(redex, cost__ + 1);
            }} break;
         case a_Inst::tag_SUB: {
            // Inst (3)
            if (cost__ + 1 < state_rec->cost[2])
            {   _state_rec->cost[2] = cost__ + 1;
                _state_rec->rule._exp = 3;
               _s_p_a_r_c_3co_X1_exp_closure(redex, cost__ + 1);
            }} break;
         case a_Inst::tag_DIV: {
            // Inst (4)
            int _X3 = notarget(a);
            if (cost__ + _X3 < state_rec->cost[2])
            {   _state_rec->cost[2] = cost__ + _X3;
                _state_rec->rule._exp = 1;
               _s_p_a_r_c_3co_X1_exp_closure(redex, cost__ + _X3);
            }} break;
         default: {
            // Inst (5)
            if (cost__ + 2 < state_rec->cost[2])
            {   _state_rec->cost[2] = cost__ + 2;
                _state_rec->rule._exp = 2;
               _s_p_a_r_c_3co_X1_exp_closure(redex, cost__ + 2);
            }} break;
      }
   }
   
}

void _s_p_a_r_c_3co_X1::reduce(Inst redex)
{
   int r__ = (_s_p_a_r_c_3co_X1_StateRec *)(redex->get_state_rec());
   switch (r__) {
      case 8: { // DIV (exp, exp)
         reduce(_DIV(redex)->_1);
         reduce(_DIV(redex)->_2);
         } break;
      case 7: { // MUL (exp, exp)
         reduce(_MUL(redex)->_1);
         reduce(_MUL(redex)->_2);
         } break;
      case 6: { // SUB (exp, exp)
         reduce(_SUB(redex)->_1);
         reduce(_SUB(redex)->_2);
         } break;
      case 5: { // ADD (exp, exp)
         reduce(_ADD(redex)->_1);
         reduce(_ADD(redex)->_2);
         } break;
      case 4: { // reg
         reduce(redex);
         } break;
      case 3: { // LOAD reg
         reduce(_LOAD(redex)->LOAD);
         } break;
      case 2: { // LOAD ADD (reg, reg)
         reduce(_ADD(_LOAD(redex)->LOAD)->_1);
         reduce(_ADD(_LOAD(redex)->LOAD)->_2);
         } break;
      case 1: { // LOAD INT addr
         } break;
      case 0: { // INT i
         } break;
   }
}

/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 4
Number of ifs generated      = 0
Number of switches generated = 2
Number of labels             = 0
Number of gotos              = 0
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
