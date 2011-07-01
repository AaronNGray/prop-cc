///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.5),
//  last updated on Jun 18, 1997.
//  The original source file is "test_gc17.pcc".
///////////////////////////////////////////////////////////////////////////////

#define PROP_GARBAGE_COLLECTION_USED
#include <propdefs.h>
#line 1 "test_gc17.pcc"
//
//  Testing garbage collection with polymorphic datatypes
//

#include <iostream.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <AD/gc/gcheaps.h>

#define NODES (256 * 1024) 
#define TRIALS 10
#define SHARING

//////////////////////////////////////////////////////////////////////////////
//  Datatype TREE is just a simple binary tree (actually a dag in our case).
//////////////////////////////////////////////////////////////////////////////
#line 18 "test_gc17.pcc"
#line 22 "test_gc17.pcc"
///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for TREE<T>
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_TREE_defined
#define datatype_TREE_defined
template <class T> class a_TREE;
#define TREE(T) a_TREE<T> *
#endif

#  define empty 0

///////////////////////////////////////////////////////////////////////////////
//
// Base class for datatype TREE<T>
//
///////////////////////////////////////////////////////////////////////////////
template <class T> class a_TREE : public GCObject {
public:
   enum Tag_TREE {
      tag_leaf = 0, tag_node = 1
   };

public:
   const Tag_TREE tag__; // variant tag
protected:
   inline a_TREE(Tag_TREE t__) : tag__(t__) {}
public:
   inline virtual ~a_TREE()
   {
   }
   ////////////////////////////////////////////////////////////////////////////
   //
   // Method for garbage collection tracing
   //
   ////////////////////////////////////////////////////////////////////////////
protected:
   virtual void trace(GC *);
public:
};
template <class T> inline int boxed(const a_TREE<T> * x) { return x != 0; }
template <class T> inline int untag(const a_TREE<T> * x) { return x ? (x->tag__+1) : 0; }
///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor TREE<T>::leaf
//
///////////////////////////////////////////////////////////////////////////////
template <class T> class TREE_leaf : public a_TREE<T>  {
public:
#line 20 "test_gc17.pcc"
   T leaf; 
   inline TREE_leaf (T const & x_leaf)
    : a_TREE<T>(tag_leaf), leaf(x_leaf)
   {
   }
   inline ~TREE_leaf()
   {
   }
   ////////////////////////////////////////////////////////////////////////////
   //
   // Method for garbage collection tracing
   //
   ////////////////////////////////////////////////////////////////////////////
protected:
   virtual void trace(GC *);
public:
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor TREE<T>::node
//
///////////////////////////////////////////////////////////////////////////////
template <class T> class TREE_node : public a_TREE<T>  {
public:
#line 21 "test_gc17.pcc"
   a_TREE<T> *  _1; T _2; a_TREE<T> *  _3; 
   inline TREE_node (a_TREE<T> *  x_1, T const & x_2, a_TREE<T> *  x_3)
    : a_TREE<T>(tag_node), _1(x_1), _2(x_2), _3(x_3)
   {
   }
   inline ~TREE_node()
   {
   }
   ////////////////////////////////////////////////////////////////////////////
   //
   // Method for garbage collection tracing
   //
   ////////////////////////////////////////////////////////////////////////////
protected:
   virtual void trace(GC *);
public:
};

///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for TREE<T>
//
///////////////////////////////////////////////////////////////////////////////
template <class T> inline a_TREE<T> * leaf (T const & x_leaf)
{
   return new TREE_leaf<T> (x_leaf);
}
template <class T> inline a_TREE<T> * node (a_TREE<T> *  x_1, T const & x_2, a_TREE<T> *  x_3)
{
   return new TREE_node<T> (x_1, x_2, x_3);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for TREE<T>
//
///////////////////////////////////////////////////////////////////////////////
template <class T> inline TREE_leaf<T> * _leaf(const a_TREE<T> * _x_) { return (TREE_leaf<T> *)_x_; }
template <class T> inline TREE_node<T> * _node(const a_TREE<T> * _x_) { return (TREE_node<T> *)_x_; }

#line 22 "test_gc17.pcc"
#line 22 "test_gc17.pcc"


#line 24 "test_gc17.pcc"
#line 24 "test_gc17.pcc"
///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype TREE<int>
//
///////////////////////////////////////////////////////////////////////////////
#line 24 "test_gc17.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype TREE<char const *>
//
///////////////////////////////////////////////////////////////////////////////
#line 24 "test_gc17.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype TREE<int>
//
///////////////////////////////////////////////////////////////////////////////
#line 24 "test_gc17.pcc"
#ifdef PROP_EXPLICIT_TEMPLATE_INSTANTIATION
template class a_TREE<int>;
template class TREE_leaf<int>;
template a_TREE<int> * leaf(char const * const & x_leaf);
template class TREE_node<int>;
template a_TREE<int> * node(a_TREE<char const *> *  x_1, char const * const & x_2, a_TREE<char const *> *  x_3);
template int boxed(const a_TREE<int> *);
template int untag(const a_TREE<int> *);
template a_TREE<int> * _leaf(const a_TREE<int> *);
template a_TREE<int> * _node(const a_TREE<int> *);
#endif /* PROP_EXPLICIT_TEMPLATE_INSTANTIATION */
void a_TREE<int>::trace(GC * gc__)
{
}

void TREE_leaf<int>::trace(GC * gc__)
{
   // call to method a_TREE<int>::trace() has been optimized out
   // omitted int const &
}

void TREE_node<int>::trace(GC * gc__)
{
   // call to method a_TREE<int>::trace() has been optimized out
   this->_1 = (a_TREE<int> *  )gc__->trace(this->_1); // TREE<int> 
   // omitted int const &
   this->_3 = (a_TREE<int> *  )gc__->trace(this->_3); // TREE<int> 
}



///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype TREE<char const *>
//
///////////////////////////////////////////////////////////////////////////////
#line 24 "test_gc17.pcc"
#ifdef PROP_EXPLICIT_TEMPLATE_INSTANTIATION
template class a_TREE<char const *>;
template class TREE_leaf<char const *>;
template a_TREE<char const *> * leaf(int const & x_leaf);
template class TREE_node<char const *>;
template a_TREE<char const *> * node(a_TREE<int> *  x_1, int const & x_2, a_TREE<int> *  x_3);
template int boxed(const a_TREE<char const *> *);
template int untag(const a_TREE<char const *> *);
template a_TREE<char const *> * _leaf(const a_TREE<char const *> *);
template a_TREE<char const *> * _node(const a_TREE<char const *> *);
#endif /* PROP_EXPLICIT_TEMPLATE_INSTANTIATION */
void a_TREE<char const *>::trace(GC * gc__)
{
}

void TREE_leaf<char const *>::trace(GC * gc__)
{
   // call to method a_TREE<char const *>::trace() has been optimized out
   // omitted char const * const &
}

void TREE_node<char const *>::trace(GC * gc__)
{
   // call to method a_TREE<char const *>::trace() has been optimized out
   this->_1 = (a_TREE<char const *> *  )gc__->trace(this->_1); // TREE<char const *> 
   // omitted char const * const &
   this->_3 = (a_TREE<char const *> *  )gc__->trace(this->_3); // TREE<char const *> 
}



#line 24 "test_gc17.pcc"
#line 24 "test_gc17.pcc"


//////////////////////////////////////////////////////////////////////////////
//  Compute the sum of all nodes of a tree
//////////////////////////////////////////////////////////////////////////////
int sum (
#line 29 "test_gc17.pcc"
a_TREE<int> *  
#line 29 "test_gc17.pcc"
 t)
{  
#line 34 "test_gc17.pcc"
{
   if (t) {
      if (t->tag__) {
         
#line 33 "test_gc17.pcc"
       return sum(_node(t)->_1) + _node(t)->_2 + sum(_node(t)->_3);
         
#line 34 "test_gc17.pcc"
      } else {
         
#line 32 "test_gc17.pcc"
  return _leaf(t)->leaf;
         
#line 33 "test_gc17.pcc"
      }
   } else {
#line 31 "test_gc17.pcc"
  return 0;
      
#line 32 "test_gc17.pcc"
   }
}
#line 34 "test_gc17.pcc"
#line 34 "test_gc17.pcc"

}

//////////////////////////////////////////////////////////////////////////////
//  Count the number of pointer sharings. 
//////////////////////////////////////////////////////////////////////////////
int sharing (
#line 40 "test_gc17.pcc"
a_TREE<int> *  
#line 40 "test_gc17.pcc"
 t)
{  
#line 46 "test_gc17.pcc"
{
   if (t) {
      if (t->tag__) {
         
#line 44 "test_gc17.pcc"
       return sharing(_node(t)->_1) + sharing(_node(t)->_3) 
         + ((_node(t)->_1 != empty && _node(t)->_1 == _node(t)->_3) ? 1 : 0);
         
#line 46 "test_gc17.pcc"
      } else {
         
#line 43 "test_gc17.pcc"
  return 0;
         
#line 44 "test_gc17.pcc"
      }
   } else {
#line 42 "test_gc17.pcc"
  return 0;
      
#line 43 "test_gc17.pcc"
   }
}
#line 46 "test_gc17.pcc"
#line 46 "test_gc17.pcc"

}

//////////////////////////////////////////////////////////////////////////////
//  Compute the size of a tree
//////////////////////////////////////////////////////////////////////////////
template <class T>
   int size (
#line 53 "test_gc17.pcc"
a_TREE<T> *  
#line 53 "test_gc17.pcc"
 t)
   {  
#line 58 "test_gc17.pcc"
{
   if (t) {
      if (t->tag__) {
         
#line 57 "test_gc17.pcc"
       return size(_node(t)->_1) + 1 + size(_node(t)->_3);
         
#line 58 "test_gc17.pcc"
      } else {
         
#line 56 "test_gc17.pcc"
  return 1;
         
#line 57 "test_gc17.pcc"
      }
   } else {
#line 55 "test_gc17.pcc"
  return 0;
      
#line 56 "test_gc17.pcc"
   }
}
#line 58 "test_gc17.pcc"
#line 58 "test_gc17.pcc"

   }

//////////////////////////////////////////////////////////////////////////////
//  Check a tree for correctness.
//////////////////////////////////////////////////////////////////////////////
template <class T>
   void check (
#line 65 "test_gc17.pcc"
a_TREE<T> *  
#line 65 "test_gc17.pcc"
 t)
   {  
#line 74 "test_gc17.pcc"
{
   if (t) {
      if (t->tag__) {
         
#line 69 "test_gc17.pcc"
     
         assert (HM::is_mapped(t) && 
                 HM::page_gc(t) == GC::get_default_gc().gc_id());
         assert (HM::get_object_map().is_marked(t));
         check(_node(t)->_1); check(_node(t)->_3); 
         
#line 74 "test_gc17.pcc"
      } else {
         
#line 68 "test_gc17.pcc"
  return;
         
#line 69 "test_gc17.pcc"
      }
   } else {
#line 67 "test_gc17.pcc"
  return;
      
#line 68 "test_gc17.pcc"
   }
}
#line 74 "test_gc17.pcc"
#line 74 "test_gc17.pcc"

   }

//////////////////////////////////////////////////////////////////////////////
//  Routine to make a random tree of a certain size.
//////////////////////////////////////////////////////////////////////////////
#line 80 "test_gc17.pcc"
a_TREE<int> *  
#line 80 "test_gc17.pcc"
 make_tree(int n)
{  if (n == 0) return empty;
   int split = rand() % n;
   int data  = rand() % n;
#ifdef SHARING
   if ((n % 2 == 1) && (rand() % 2 == 1)) {
      a_TREE<int> *  
#line 86 "test_gc17.pcc"
 t = make_tree(n/2);
      return node(t, data, t);
   }
#endif
   return node(make_tree(split), data, make_tree(n - split - 1));
}

void testing()
{  
   for (int trial = 1; trial <= TRIALS; trial++) {
       cout << "Trial number " << trial << '\n' << flush;
       a_TREE<int> *  
#line 97 "test_gc17.pcc"
 tree1    = make_tree(NODES);
       int       size1    = size(tree1);
       int       sum1     = sum(tree1);
       int       sharing1 = sharing (tree1);
       check(tree1);

       cout << "Size = " << size1 << " check sum = " << sum1 
            << " pointer sharing = " << sharing1 << '\n' << flush;

       make_tree(NODES);              // this just generates a lot of garbage

       // Now traverse the tree check things.
       assert(size(tree1)     == NODES);
       assert(sum(tree1)      == sum1);
       assert(sharing(tree1)  == sharing1);
       check(tree1);
       cout << "Trial number " << trial << " has passed\n";
   }
}

int main()
{  
   cout << 
     "This test generate random dags and try to see if garbage collection\n"
     "works on preserving pointer sharing correctly.  I'll do this " 
      << TRIALS << " times.\n";
   srand(getpid()); 
   testing();
   // force an explicit garbage collection
   cout << "Finished.  Now I'm forcing another garbage collection to clean\n"
           "things up.  There should be very little garbage left at the end.\n";
   GC::garbage_collect();  
   return 0;
}
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 0
Number of ifs generated      = 8
Number of switches generated = 0
Number of labels             = 0
Number of gotos              = 0
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
