//////////////////////////////////////////////////////////////////////////////
// NOTICE:
//
// ADLib, Prop and their related set of tools and documentation are in the
// public domain.   The author(s) of this software reserve no copyrights on
// the source code and any code generated using the tools.  You are encouraged
// to use ADLib and Prop to develop software, in both academic and commercial
// settings, and are free to incorporate any part of ADLib and Prop into
// your programs.
//
// Although you are under no obligation to do so, we strongly recommend that
// you give away all software developed using our tools.
//
// We also ask that credit be given to us when ADLib and/or Prop are used in
// your programs, and that this notice be preserved intact in all the source
// code.
//
// This software is still under development and we welcome any suggestions
// and help from the users.
//
// Allen Leung
// 1994
//////////////////////////////////////////////////////////////////////////////

#ifndef n_dimensional_dense_array_h
#define n_dimensional_dense_array_h

#include <assert.h>
#include <AD/generic/generic.h> // generic definitions

///////////////////////////////////////////////////////////////////////
//  NOTE:
//
//  MultiArray<T> is a very simple n-dimension array indexed by
//  natural numbers.   The tables are collasped into a one dimensional
//  form internally.   The dimension of the array is fixed at creation,
//  but its bounds can grow.
//
//  This is a concrete type.
///////////////////////////////////////////////////////////////////////

template <class T>
class MultiArray
{
public:

  /////////////////////////////////////////////////////////////////
  //  Some manifest constants.  We can't use
  // `const int Max_Dimension = 256;' here since ANSI/ISO disallows
  //  such a usage(even though g++ supports this extension.)
  /////////////////////////////////////////////////////////////////

  enum MultiArray_constants
  {  Max_Dimension = 256, // we allow up to 256 dimensions
     // (an arbitrary limit, really)
     Min_Capacity  = 4    // minimum capacity per-dimension
  };

  /////////////////////////////////////////////////////////////////
  //  Internal representation.
  /////////////////////////////////////////////////////////////////

protected:
  int   dim;       // dimension
  int * bounds;    // actual bounds of each dimension
  int   capacity;  // product of the bounds
  T *   table;     // the array collasped into one dimensional form
  T     def_val;   // default value.

  /////////////////////////////////////////////////////////////////
  //  Auxiliary method to create a table.
  /////////////////////////////////////////////////////////////////

private:
  void create_table(const int initial_bounds[]);

  /////////////////////////////////////////////////////////////////
  //  Constructors and destructor
  /////////////////////////////////////////////////////////////////

public:
  MultiArray(int dimensions);
  MultiArray(int dimensions, const T& default_value);
  MultiArray(int dimensions, const int []);
  MultiArray(int dimensions, const int [], const T&);
  MultiArray(int dimensions, const int [], const T&, const T[]);
  MultiArray(const MultiArray&);
  virtual ~MultiArray();

  /////////////////////////////////////////////////////////////////
  //  Assignment and other mutators.
  /////////////////////////////////////////////////////////////////

  MultiArray& operator = (const MultiArray&);
  MultiArray& clear();

  /////////////////////////////////////////////////////////////////
  //  Conversions.
  /////////////////////////////////////////////////////////////////

  inline operator const T* () const
  {
    return table;
  }

  inline operator T* ()
  {
    return table;
  }

  /////////////////////////////////////////////////////////////////
  //  Selectors on bounds and sizes.
  /////////////////////////////////////////////////////////////////

  inline int dimensions() const
  {
    return dim;
  }

  inline int dimension(int i) const
  {
    return bounds[i];
  }

  inline int size() const
  {
    return capacity;
  }

  inline Bool is_empty() const
  {
    return capacity == 0;
  }

  /////////////////////////////////////////////////////////////////
  //  Default value.
  /////////////////////////////////////////////////////////////////

  inline const T& def_value() const
  {
    return def_val;
  }

  inline T& def_value()
  {
    return def_val;
  }

  /////////////////////////////////////////////////////////////////
  //  Indexing.
  //  Methods to index the array.  The const version perform no
  //  checking for valid indices!   These methods are inlined for
  //  efficiency.
  /////////////////////////////////////////////////////////////////

  inline const T& operator [] (const int I[]) const
  {
    register int i, j;
    for (j = I[0], i = 1; i < dim; i++)
      j = I[i] + j * bounds[i];
    return table[j];
  }

  inline T& operator [] (const int I[])
  {
    grow(I);
    register int i, j;
    for (j = I[0], i = 1; i < dim; i++)
      j = I[i] + j * bounds[i];
    return table[j];
  }

  /////////////////////////////////////////////////////////////////
  //  Growth
  /////////////////////////////////////////////////////////////////

  virtual MultiArray& grow( const int indices[]);
  virtual int new_bound( int i, int current, int indexed) const;

  /////////////////////////////////////////////////////////////////
  //  Iterators.
  /////////////////////////////////////////////////////////////////

  inline Ix first() const
  {
    return Ix(capacity ? 1 : 0);
  }

  inline Ix last() const
  {
    return Ix(capacity);
  }

  inline Ix next(Ix i) const
  {
    return Ix(int(i) + 1 >= capacity ? 0 : int(i) + 1);
  }

  inline Ix prev(Ix i) const
  {
    return Ix(int(i) - 1);
  }

  inline const T& operator () (Ix i) const
  {
    return table[int(i) - 1];
  }

  inline T& operator () (Ix i)
  {
    return table[int(i) - 1];
  }
};

///////////////////////////////////////////////////////////////////////
//
//  Implementation of the template methods follows.
//
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
//  Initialization constructor.
///////////////////////////////////////////////////////////////////////

template <class T>
MultiArray<T>::MultiArray(int dimensions)
    : dim      (dimensions),
    bounds   (new int [dimensions]),
    capacity (0),
    table    (0)
{
  for (int i = dimensions - 1; i >= 0; i--)
    bounds[i] = 0;
}

///////////////////////////////////////////////////////////////////////
//  Initialization constructor (with default value)
///////////////////////////////////////////////////////////////////////

template <class T>
MultiArray<T>::MultiArray(int dimensions, const T& default_value)
    : dim       (dimensions),
    bounds    (new int [dimensions]),
    capacity  (0),
    table     (0),
    def_val   (default_value)
{
  for (int i = dimensions - 1; i >= 0; i--)
    bounds[i] = 0;
}

///////////////////////////////////////////////////////////////////////
//  Copy constructor.
///////////////////////////////////////////////////////////////////////

template <class T>
MultiArray<T>::MultiArray(const MultiArray<T>& A)
    : bounds(0), table(0)
{
  *this = A;
}

///////////////////////////////////////////////////////////////////////
//  Constructor to create a multiarray with some initial bounds.
///////////////////////////////////////////////////////////////////////

template <class T>
MultiArray<T>::MultiArray(int dimensions, const int initial_bounds[])
    : dim (dimensions), bounds(new int [dimensions])
{
  create_table(initial_bounds);
}

///////////////////////////////////////////////////////////////////////
//  Constructor to create a multiarray with some initial bounds,
//  with a default value.
///////////////////////////////////////////////////////////////////////

template <class T>
MultiArray<T>::MultiArray
(int dimensions, const int initial_bounds[], const T& def)
    : dim (dimensions), bounds(new int [dimensions]), def_val(def)
{
  create_table(initial_bounds);
}

///////////////////////////////////////////////////////////////////////
//  Constructor to create a multiarray with some initial bounds,
//  with a default value, initialized by a one-dimensional array
//  (with the some row/column orientation!) supplied by the client.
///////////////////////////////////////////////////////////////////////

template <class T>
MultiArray<T>::MultiArray
(int dimensions, const int initial_bounds[], const T& def, const T A[])
    : dim (dimensions), bounds(new int [dimensions]), def_val(def)
{
  create_table(initial_bounds);
  for (int i = capacity - 1; i >= 0; i--)
    table[i] = A[i];
}

///////////////////////////////////////////////////////////////////////
//  Destructor.
///////////////////////////////////////////////////////////////////////

template <class T>
MultiArray<T>::~MultiArray()
{
  delete [] bounds;
  delete [] table;
}

///////////////////////////////////////////////////////////////////////
//  Assignment method.
///////////////////////////////////////////////////////////////////////

template <class T>
MultiArray<T>& MultiArray<T>::operator = (const MultiArray<T>& A)
{
  if (this != &A)
  {
    delete [] bounds;
    delete [] table;
    dim       = A.dim;
    capacity  = A.capacity;
    def_val   = A.def_val;
    bounds    = new int [dim];
    table     = new T   [capacity];
    for (int i = dim - 1;      i >= 0; i--)
      bounds[i] = A.bounds[i];
    for (int j = capacity - 1; j >= 0; j--)
      table[j]  = A.table[j];
  }
  return *this;
}

///////////////////////////////////////////////////////////////////////
//  Method to empty the table but leave the dimension alone.
///////////////////////////////////////////////////////////////////////

template <class T>
MultiArray<T>& MultiArray<T>::clear()
{
  delete [] table;
  table    = 0;
  capacity = 0;
  for (int i = dim - 1; i >= 0; i--)
    bounds[i] = 0;
}

///////////////////////////////////////////////////////////////////////
//  Auxiliary method to create a new table with some initial bounds.
//  The table is assumed to be empty initially.
///////////////////////////////////////////////////////////////////////

template <class T>
void MultiArray<T>::create_table(const int initial_bounds[])
{
  capacity = 1;
  for (int i = dim - 1; i >= 0; i--)
    capacity *= (bounds[i] = initial_bounds[i]);
  table = new T [capacity];
  for (int j = capacity - 1; j >= 0; j--)
    table[j] = def_val;
}

///////////////////////////////////////////////////////////////////////
//  Method to grow in all dimensions if necessary.
///////////////////////////////////////////////////////////////////////

template <class T>
MultiArray<T>& MultiArray<T>::grow(const int indices[])
{
  //////////////////////////////////////////////////////////////////
  // Step (1).  A quick check to determine whether the new sizes
  // exceed the boundaries at any of the dimension.  If so, we'll have
  // to expand the array.
  //////////////////////////////////////////////////////////////////
  Bool expansion = false;            // do we have to expand?
  {  for (int i = dim - 1; i >= 0; i--)
      if (bounds[i] <= indices[i])
      {
        expansion = true;
        break;
      }
  }

  //////////////////////////////////////////////////////////////////
  // Step (2). Do the rest only if we have to expand.
  //////////////////////////////////////////////////////////////////
  if (expansion)
  {
    ///////////////////////////////////////////////////////////////
    // Step (2a). Calculate the amount to expand and to shift
    // during the expansion.
    ///////////////////////////////////////////////////////////////
    int diffs      [ Max_Dimension ];  // difference in boundaries between old and new (scaled).
    int new_bounds [ Max_Dimension ];  // the new boundaries
    int counters   [ Max_Dimension ];  // indices for looping
    int new_capacity = 1, old_capacity = 1;
    {
      for (int i = dim - 1; i >= 0; i--)
      {
        counters[i] = 0;
        if (indices[i] >= bounds[i])
        {
          new_bounds[i] = new_bound(i, bounds[i], indices[i]);
          diffs[i]      = (new_bounds[i] - bounds[i]) * new_capacity;
        }
        else
        {
          new_bounds[i] = bounds[i];
          diffs[i]      = 0;
        }
        new_capacity *= new_bounds[i];
        old_capacity *= bounds[i];
      }
    }

    ///////////////////////////////////////////////////////////////
    //  Step (2b).  Allocate the new array and perform the
    //  copying and shifting.  Existing elements are copied to
    //  the (hopefully) correctly position in the new table.
    //  Gaps within the table are filled with the default value.
    ///////////////////////////////////////////////////////////////
    T * new_table = new T [ new_capacity ];
    if (capacity == 0)
    {
      for (int i = new_capacity - 1; i >= 0; i--)
        new_table[i] = def_val;
    }
    else
    {
      register T * p = table, * q = new_table;
      int i;
      do
      {
        *q++ = *p++;
        for (i = dim - 1; i >= 0; i--)
        {
          if (++counters[i] < bounds[i])
            break;
          for (int j = diffs[i]; j > 0; j--)
            *q++ = def_val;
          counters[i] = 0;
        }
      }
      while (i >= 0);
      assert(p == table     + capacity);
      assert(q == new_table + new_capacity);
    }

    ///////////////////////////////////////////////////////////////
    //  Step (2c) Move things to the right place and clean up.
    ///////////////////////////////////////////////////////////////
    delete [] table;
    table = new_table;
    {
      for (int i = dim - 1; i >= 0; i--)
        bounds[i] = new_bounds[i];
      capacity = new_capacity;
    }
  }

  //////////////////////////////////////////////////////////////////
  //  Finally, exit.
  //////////////////////////////////////////////////////////////////
  return *this;
}

///////////////////////////////////////////////////////////////////////
//  Method to calculate the size of a new dimension.
//  This method is overridable by subclasses.
//  The default heuristic just doubles the available space.
///////////////////////////////////////////////////////////////////////

template <class T>
int MultiArray<T>::new_bound
( int i,       // dimension
  int current, // current bounds
  int indexed  // indexed
) const
{
  indexed++;
  if (indexed > current * 2)
    if (indexed < Min_Capacity)
      return Min_Capacity;
    else
      return indexed;
  else
    return current * 2;
}

#endif
