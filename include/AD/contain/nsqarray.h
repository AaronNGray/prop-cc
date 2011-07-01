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

#ifndef n_dimensional_square_arrays_h
#define n_dimensional_square_arrays_h

///////////////////////////////////////////////////////////////////////
//  NSqArray<T> is a very simple n-dimension array indexed by natural
//  numbers that have the same bounds on each dimension.
///////////////////////////////////////////////////////////////////////

template <class T>
class NSqArray
{
  NSqArray(const NSqArray&);          // no copying constructor
  void operator = (const NSqArray&);  // no assignment

  int n;             // dimension
  int capacities;    // actual capacities of each dimension
  T * table;         // the table in one dimensional form

public:
  const int Max_dimensions = 256;

  NSqArray() : n(0), capacities(0), table(0)
  {}
  ~NSqArray()
  {
    delete [] table;
  }

  void create( int N, int bounds);

  int dimensions() const
  {
    return n;
  }
  int capacity() const
  {
    return capacites;
  }
  operator T* () const
  {
    return table;
  }

  T& operator [] (const int indices[]) const  // indexing
  {
    register int i, offset;
    for (offset = indices[0], i = 1; i < dimensions(); i++)
      offset = indices[i] + offset * capacities;
    return table[offset];
  };
  void grow(int size);                        // growth
};

///////////////////////////////////////////////////////////////////////
//  Template methods
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
//  Create a new table
///////////////////////////////////////////////////////////////////////

template <class T>
void NSqArray<T>::create( int N, int bounds)
{
  n         = N;
  capacites = bounds;
  int total = 1;
  for (int i = 0; i < N; i++)
    total *= bounds;
  table = new T [total];
}

///////////////////////////////////////////////////////////////////////
// Growth in one dimension
///////////////////////////////////////////////////////////////////////

template <class T>
void NSqArray<T>::grow(int size)
{
  if (size > capacities)
  {
    int new_size, old_size, i;
    int diffs[Max_dimensions];
    int indices[Max_dimensions];
    for (i = 0, old_size = capacities, new_size = size; i < n; i++)
    {
      diffs[i]  = new_size - old_size;
      new_size *= size;
      old_size *= capacities;
      indices[i] = 0;
    }
    T * new_table = new T [new_size];

    register T * p = table, * q = new_table;
    do
    {
      *q++ = *p++;
      for (i = n - 1; i >= 0; i--)
      {
        if (++indices[i] < capacities)
          break;
        q += diffs[i];
        indices[i] = 0;
      }
    }
    while (i >= 0);

    delete [] table;
    table = new_table;
    capacities = size;
  }
}

#endif
