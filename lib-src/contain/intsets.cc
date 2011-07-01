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

#include <string.h>
#include <AD/contain/intsets.h>

//
// The size allocated for each set is rounded up to a power of 2 so that
// index calculation can be performed with only a shift.
// The bit array is stored preshifted so that index calculation can be
// simplified.
//

void IntSetArray::create(int i, int j, int a, int b)
{
  min_index   = i;
  byte_offset = (a + 7) / 8;

  register int set_size = (b - a + 16) / 8;
  for (shift = 1; set_size > 0; shift++)
    set_size >>= 1;
  int size = (j - i + 1) << shift;
  sets = new Byte [ size ];
  memset(sets,0,size * sizeof(Byte));
  sets -= (min_index << shift) + byte_offset;
}

void IntSetArray::destroy()
{
  if (sets)
    delete (sets + (min_index << shift) + byte_offset);
  sets = 0;
}

IntSetArray::~IntSetArray()
{
  destroy();
}
