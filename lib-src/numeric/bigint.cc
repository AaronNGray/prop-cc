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

//////////////////////////////////////////////////////////////////////////////
// Variable length integers are represented using a sign/magnitude format.
// Arithmetic is done using 16bit unsigned integers.  The machine is
// assumed to implement unsigned 32 bit arithmetic as arithmetic modulo 2^32.
//
// This version is inspired by various ``bignum'' code, including G++'s
// Integer class and SmallTalk's LargeInteger class.
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <stdlib.h>
#include <string>
#include <new>
#include <ctype.h>
#include <AD/generic/generic.h>
#include <AD/numeric/bigint.h>


//////////////////////////////////////////////////////////////////////////////
//  Make hidden types available
//////////////////////////////////////////////////////////////////////////////

typedef BigInt::a_BigInt a_BigInt;
typedef a_BigInt::Digit  Digit;
typedef a_BigInt::Unit   Unit;

//////////////////////////////////////////////////////////////////////////////
//  Some manifest constants: assume 8 bits in a byte
//////////////////////////////////////////////////////////////////////////////

#define Bits_per_digit  (8 * sizeof(Digit))
#define Max_digit       (1 << Bits_per_digit)
#define Max_Unit        (~(Unit)0)
#define LOW(n)          ((n) & (Max_digit - 1))
#define HIGH(n)         ((n) >> Bits_per_digit)

//////////////////////////////////////////////////////////////////////////////
//  Auxiliary routines
//////////////////////////////////////////////////////////////////////////////

inline int min(int a, int b)
{
  return a < b ? a : b;
}

inline int max(int a, int b)
{
  return a > b ? a : b;
}
//inline unsigned long abs(long a) { return a > 0 ? a : -a; }

//////////////////////////////////////////////////////////////////////////////
//  Default error handler
//////////////////////////////////////////////////////////////////////////////

static void bigint_error(const char message[])
{
  std::cerr << "BigInt error: " << message << '\n';
  exit(1);
}

//////////////////////////////////////////////////////////////////////////////
//  Error handler
//////////////////////////////////////////////////////////////////////////////

void (*BigInt::error_handler)(const char []) = bigint_error;

//////////////////////////////////////////////////////////////////////////////
//  Representation for common values; these have capacity of 0 so that
//  they won't be erroneously deallocated.
//////////////////////////////////////////////////////////////////////////////

static a_BigInt zero_rep = { 0,  0, 0, { 0 } };
a_BigInt * BigInt::zero  = &zero_rep;

//////////////////////////////////////////////////////////////////////////////
// Memory management
//////////////////////////////////////////////////////////////////////////////

inline void * a_BigInt::operator new( size_t size, int capacity)
{
  register int count = 2;
  while (count < capacity)
    count <<= 1;
  a_BigInt * x = (a_BigInt*)malloc(size + (count - 1) * sizeof(Digit));
  x->capacity = count;
  return x;
}

void a_BigInt::operator delete(void * x)
{
  if (((a_BigInt*)x)->capacity > 0)
    free(x);
}

//////////////////////////////////////////////////////////////////////////////
//  Normalize a number by eliminating leading zeros
//////////////////////////////////////////////////////////////////////////////

inline void normalize( a_BigInt * r)
{
  register int i;
  for (i = r->len-1; i >= 0; i--)
    if (r->digits[i] != 0)
      break;
  if ((r->len = i+1) == 0)
    r->sign = 0;
}

//////////////////////////////////////////////////////////////////////////////
// Delete a BigInt
//////////////////////////////////////////////////////////////////////////////

inline void kill( a_BigInt * r)
{
  if (r && r->capacity > 0)
    free(r);
}

//////////////////////////////////////////////////////////////////////////////
// Make zero, one, or minus one
//////////////////////////////////////////////////////////////////////////////

inline a_BigInt * make_zero( a_BigInt * r)
{
  kill(r);
  return &zero_rep;
}

//////////////////////////////////////////////////////////////////////////////
//  Copy a bigint; reallocate if necessary
//////////////////////////////////////////////////////////////////////////////

a_BigInt* copy( a_BigInt* r, const a_BigInt* a)
{
  if (r == a)
    return r;
  if (r == 0)
  {
    r = new (a->len) BigInt::a_BigInt;
  }
  else
  {
    if ((r->capacity) < (a->len))
    {
      kill(r);
      r = new (a->len) BigInt::a_BigInt;
    }
  }
  r->len = a->len;
  r->sign = a->sign;
  memcpy(r->digits,a->digits,a->len * sizeof(Digit));
  return r;
}

//////////////////////////////////////////////////////////////////////////////
//  Copy a bigint and negate; reallocate if necessary
//////////////////////////////////////////////////////////////////////////////

a_BigInt* neg( a_BigInt* r, const a_BigInt* a)
{
  if (r == 0 || (r->capacity) < (a->len))
  {
    kill(r);
    r = new(a->len) a_BigInt;
  }
  r->len = a->len;
  r->sign = - a->sign;
  memcpy(r->digits,a->digits,a->len * sizeof(Digit));
  return r;
}

//////////////////////////////////////////////////////////////////////////////
//  Copy a long
//////////////////////////////////////////////////////////////////////////////

a_BigInt* copy( a_BigInt* r, long a, int sign)
{
  if (a == 0)
    return make_zero(r);
  if (r == 0 || r->capacity == 0)
    r = new (2) a_BigInt;
  Unit mag;
  if (a > 0)
  {
    r->sign = sign;
    mag = a;
  }
  else
  {
    r->sign = -sign;
    mag = -a;
  }
  r->len       = mag >= Max_digit ? 2 : 1;
  r->digits[0] = LOW(mag);
  r->digits[1] = HIGH(mag);
  return r;
}

//////////////////////////////////////////////////////////////////////////////
//  Allocate a BigInt
//////////////////////////////////////////////////////////////////////////////

inline a_BigInt* alloc( a_BigInt* r, int len)
{
  if (r == 0 || (r->capacity) < len)
    return new(len) a_BigInt;
  else
    return r;
}

//////////////////////////////////////////////////////////////////////////////
//  Reallocate a BigInt
//////////////////////////////////////////////////////////////////////////////

inline a_BigInt* realloc( a_BigInt* r, int len)
{
  if (r == 0 || (r->capacity) < len)
  {
    a_BigInt * new_r = new(len) a_BigInt;
    register Digit * p, * q, * limit;
    for (p = r->digits, q = new_r->digits, limit = p + r->len; p < limit;)
      *q++ = *p++;
    return new_r;
  }
  else
    return r;
}

//////////////////////////////////////////////////////////////////////////////
//  Clear the upper digits
//////////////////////////////////////////////////////////////////////////////

inline void clear( register Digit* p, int start, int stop)
{
  register Digit * limit = p + stop;
  for (p += start; p < limit; )
    *p++ = 0;
}

//////////////////////////////////////////////////////////////////////////////
//  Comparisions
//////////////////////////////////////////////////////////////////////////////

inline int ucmp( const a_BigInt* a, const a_BigInt* b)
{
  int r = a->len - b->len;
  if (r == 0)
  {
    register const Digit * x;
    register const Digit * y;
    register int len;
    for (x = a->digits + a->len - 1, y = b->digits + b->len - 1,
         len = a->len; len > 0; len--, x--, y--)
      if ((r = ((long)*x - (long)*y)))
        return r;
  }
  return r;
}

//////////////////////////////////////////////////////////////////////////////
//  Signed comparison between two BigInt's
//////////////////////////////////////////////////////////////////////////////

int cmp( const a_BigInt* a, const a_BigInt* b)
{
  if (a->sign > b->sign)
    return 1;
  if (a->sign < b->sign)
    return -1;
  if (a->sign == 0 && b->sign == 0)
    return 0;
  int r = a->len - b->len;
  if (r == 0)
    r = ucmp(a,b);
  return a->sign == 1 ? r : -r;
}

//////////////////////////////////////////////////////////////////////////////
//  Signed comparison between a BigInt and a long
//////////////////////////////////////////////////////////////////////////////

int cmp( const a_BigInt* a, long b)
{
  if (a->sign == 0  && b == 0)
    return 0;
  if (a->sign == 1  && b <= 0)
    return 1;
  if (a->sign == -1 && b >= 0)
    return -1;
  int b_sign;
  unsigned long b_mag;
  if (b > 0)
  {
    b_sign = 1;
    b_mag = b;
  }
  else
  {
    b_sign = -1;
    b_mag = -b;
  }
  int b_len = b_mag >= Max_digit ? 2 : 1;
  int r = a->len - b_len;
  if (r == 0)
  {
    if (b_len == 2)
      r = (long)(a->digits[1] * Max_digit + a->digits[0]) - (long)b_mag;
    else
      r = (long)a->digits[0] - (long)b_mag;
  }
  return a->sign ? r : -r;
}

//////////////////////////////////////////////////////////////////////////////
//  Compute the estimated length of an unsigned addition
//  taking into account of possible carry.
//////////////////////////////////////////////////////////////////////////////

inline int uaddlen( const a_BigInt* a, const a_BigInt* b)
{
  if (a->len > b->len)
    if (a->digits[a->len-1] == Max_digit-1)
      return a->len + 1;
    else
      return a->len;
  if (a->len < b->len)
    if (b->digits[b->len-1] == Max_digit-1)
      return b->len + 1;
    else
      return b->len;
  if ((Unit)a->digits[a->len-1] + (Unit)b->digits[b->len-1] >= Max_digit-1)
    return a->len + 1;
  else
    return a->len;
}

//////////////////////////////////////////////////////////////////////////////
//  Unsigned addition
//////////////////////////////////////////////////////////////////////////////

inline void uadd( a_BigInt* r, const a_BigInt* a, const a_BigInt* b)
{
  register Unit sum;
  register const Digit * x, * y;
  register Digit * z;
  register int len = min(a->len,b->len);
  for (x=a->digits, y=b->digits, z=r->digits, sum = 0; len > 0; len--)
  {
    sum   +=  (Unit)*x++ + (Unit)*y++;
    *z++  =   LOW(sum);
    sum   =   HIGH(sum);
  }
  len = a->len - b->len;
  if (len < 0)
  {
    len = -len;
    x = y;
  }
  for ( ; len > 0; len--)
  {
    sum   +=  (Unit)*x++;
    *z++  =   LOW(sum);
    sum   =   HIGH(sum);
  }
  if (sum)
    *z = sum;
  r->len = z - r->digits;
}

//////////////////////////////////////////////////////////////////////////////
//  Unsigned substraction; assume abs(a) >= abs(b)
//////////////////////////////////////////////////////////////////////////////

inline void usub( a_BigInt* r, const a_BigInt* a, const a_BigInt* b)
{
  register Unit diff;
  register const Digit * x, * y;
  register Digit * z;
  register int len = b->len;
  for (x=a->digits, y=b->digits, z=r->digits, diff = 1; len > 0; len--)
  {
    diff += (Unit)*x++ - (Unit)*y++ + Max_digit - 1;
    *z++  = LOW(diff);
    diff  = HIGH(diff);
  }
  for (len = a->len - b->len; diff != 1 && len > 0; len--)
  {
    diff += (Unit)*x++ + Max_digit - 1;
    *z++  = LOW(diff);
    diff  = HIGH(diff);
  }
  for ( ;len > 0; len--)
    *z++ = *x++;
  r->len = a->len;
  normalize(r);
}

////////////////////////////////////////////////////////////////
//  Performs signed addition/subtraction
////////////////////////////////////////////////////////////////

a_BigInt* addsub
(a_BigInt *r, const a_BigInt* a, const a_BigInt* b, Bool sub)
{
  a_BigInt * result;

  ////////////////////////////////////////////////////////////////
  // Check for zero in one of its arguments
  ////////////////////////////////////////////////////////////////
  if (a->sign == 0 && b->sign == 0 || a == b && sub)
    return make_zero(r);
  if (a->sign == 0)
    return sub ? neg(r,b) : copy(r,b);
  if (b->sign == 0)
    return copy(r,a);

  ////////////////////////////////////////////////////////////////
  // If the signs are different, we'll do a subtraction instead
  ////////////////////////////////////////////////////////////////
  if (sub ? (a->sign == b->sign) : (a->sign != b->sign))
  {
    int relative = ucmp(a,b);
    if (relative == 0)
      return make_zero(r);
    result = alloc(r,max(a->len,b->len));
    if (relative < 0)
    {
      const a_BigInt * swap = a;
      a = b;
      b = swap;
    }
    usub(result,a,b);
    result->sign =
      sub ? (relative > 0 ? 1 : -1) :
          (relative > 0 ? a->sign : b->sign);
  }
  else
{
    result = alloc(r,uaddlen(a,b));
    uadd(result,a,b);
    result->sign = a->sign;
  }
  if (result != r)
    kill(r);
  return result;
}

//////////////////////////////////////////////////////////////////////////////
//  Signed addition/subtraction with a long
//////////////////////////////////////////////////////////////////////////////

a_BigInt* addsub( a_BigInt* r, const a_BigInt* a, long b, Bool sub)
{
  struct
  {
    a_BigInt n;
    Digit    d;
  }
  c;
  if (b == 0)
    return copy(r,a);
  if (b > 0)
  {
    c.n.sign = 1;
  }
  else
  {
    c.n.sign = -1;
    b = -b;
  }
  c.n.len       = 2;
  c.n.digits[0] = LOW(b);
  c.n.digits[1] = HIGH(b);
  return addsub(r,a,&c.n,sub);
}

//////////////////////////////////////////////////////////////////////////////
// Unsigned multiplication by a small constant
//////////////////////////////////////////////////////////////////////////////

static void umul( a_BigInt* r, const a_BigInt* a, Digit b)
{
  if (r != a)
  {
    register const Digit * y, * y_limit;
    register Digit * x;
    x       = r->digits;
    y       = a->digits;
    y_limit = y + a->len;
    register Unit product;
    for ( product = 0; y < y_limit; )
    {
      product += *y++ * b;
      *x++     = LOW(product);
      product  = HIGH(product);
    }
    if (product)
      *x++ = product;
    r->len = x - r->digits;
  }
  else
  {  // r == a!!!
    register Digit * x, * y_limit;
    register Digit * y;
    x = r->digits + r->len - 1;
    y_limit = r->digits + r->len;
    *y_limit = 0;
    register Unit product;
    for (; x >= a->digits; x--)
    {
      product  = *x * b;
      *x       = LOW(product);
      product  = HIGH(product);
      for (y = x+1; product && y <= y_limit; y++)
      {
        product += *y;
        *y       = LOW(product);
        product  = HIGH(product);
      }
    }
    r->len = a->len + 1;
    normalize(r);
  }
}

//////////////////////////////////////////////////////////////////////////////
// Unsigned division by a small constant
//////////////////////////////////////////////////////////////////////////////

inline Digit udiv( a_BigInt* r, const a_BigInt* a, Digit b)
{
  register Digit * x;
  register const Digit * y;
  x = r ? r->digits + a->len - 1 : 0;
  y = a->digits + a->len - 1;
  register Unit remainder;
  for (remainder = 0; y >= a->digits; )
  {
    remainder += *y--;
    Digit quotient = remainder / b;
    if (x)
      *x-- = quotient;
    remainder = (remainder - b * quotient) << Bits_per_digit;
  }
  if (r)
  {
    r->len = a->len;
    normalize(r);
  }
  return HIGH(remainder);
}

//////////////////////////////////////////////////////////////////////////////
//  Signed multiplication
//////////////////////////////////////////////////////////////////////////////

a_BigInt* mul( a_BigInt* r, const a_BigInt* a, const a_BigInt* b)
{
  //////////////////////////////////////////////////////////////
  // Check for zeros and ones first
  //////////////////////////////////////////////////////////////
  if (a->sign == 0 || b->sign == 0)
    return make_zero(r);
  int result_sign = a->sign == 1 ? b->sign : -b->sign;
  a_BigInt * result;
  if (a->len == 1 && a->digits[0] == 1)
    result = copy(r,b);
  else if (b->len == 1 && b->digits[0] == 1)
    result = copy(r,a);
  else
  {
    int result_len = a->len + b->len;

    //////////////////////////////////////////////////////////////
    //  Reorder the multiplicants so that abs(a) < abs(b)
    //  The larger multiplicant will be used as the inner
    //  loop argument if possible to minimize looping overhead.
    //  This is probably insignificant compared to the actual
    //  cost of doing the multiplications.
    //////////////////////////////////////////////////////////////
    if (a->len > b->len)
    {
      const a_BigInt * swap = a;
      a = b;
      b = swap;
    }

    //////////////////////////////////////////////////////////////
    //  Check for duplicated arguments
    //////////////////////////////////////////////////////////////
    const Digit * x, * x_limit, * y, * y_start, * y_limit;
    Digit * z, * z_start;

    if (a == r && b == r)
    {  // r = r * r
      //////////////////////////////////////////////////////////////
      // This is a special case where the arguments and
      // the result are all the same thing.
      // We compute the product of the most significant digit
      // of the product first and work our way down one by one.
      //////////////////////////////////////////////////////////////
      result  = realloc(r, result_len);
      x_limit = y_limit = a->digits + a->len - 1;
      z_start = result->digits + result_len - 2;
      clear(result->digits, a->len, result_len);
      for ( ; z_start >= result->digits; z_start--)
      {
        Unit sum = 0;
        for (x=x_limit, y=y_limit; x <= y_limit; x++, y--)
        {
          Unit product = sum;
          product  += (Unit)*x * (Unit)*y;
          sum       = LOW(product);
          product   = HIGH(product);
          for (z = z_start; product; )
          {    // Propagate carry
            product  += *++z;
            *z        = LOW(product);
            product   = HIGH(product);
          }
        }
        *z_start = sum;
        if (x_limit > a->digits)
          x_limit--;
        else
          y_limit--;
      }
    }
    else
    {
      //////////////////////////////////////////////////////////////
      // The argument in the inner loop must not be the result.
      // However, it is okay to have the outer argument to be the same as
      // the result.
      //////////////////////////////////////////////////////////////
      if (b == r)
      {     // r = a * r
        result  = realloc(r, result_len);
        x       = b->digits + b->len - 1;
        x_limit = b->digits;
        y_start = a->digits;
        y_limit = a->digits + a->len;
        z_start = result->digits + b->len;
        clear(result->digits, b->len, result_len);
      }
      else
      {                 // r = a * b   or  r = r * b
        if (a == r)
          result = realloc(r, result_len);
        else
          result = alloc(r, result_len);
        x       = a->digits + a->len - 1;
        x_limit = a->digits;
        y_start = b->digits;
        y_limit = b->digits + b->len;
        z_start = result->digits + a->len;
        clear(result->digits, a->len, result_len);
      }

      //////////////////////////////////////////////////////////////
      // Now perform unsigned multiplication the traditional way
      //////////////////////////////////////////////////////////////
      for ( ;x >= x_limit; x--)
      {
        Unit  product;
        z = --z_start;
        Unit p = *x;
        *z = 0;
        if (p != 0)
        {  // Skip unnecessary mulitiplication if possible
          for (y = y_start, product = 0; y < y_limit; )
          {
            product  += (Unit)*z + (Unit)p * (Unit)*y++;
            *z++      = LOW(product);
            product   = HIGH(product);
          }
          while (product)
          { // propagate carry
            product  += *z;
            *z++      = LOW(product);
            product   = HIGH(product);
          }
        }
      }
    }
    if (result != r)
      kill(r);
    result->len = result_len;
    normalize(result);
  }
  result->sign = result_sign;
  return result;
}

//////////////////////////////////////////////////////////////////////////////
//  Signed multiplication with a long
//////////////////////////////////////////////////////////////////////////////

a_BigInt* mul( a_BigInt* r, const a_BigInt* a, long b)
{
  if (b == 0)
    return make_zero(r);
  if (b == 1)
    return copy(r,a);
  if (b == -1)
    return neg(r,a);
  if (a->sign == 0)
    return make_zero(r);
  if (a->len == 1 && a->digits[0] == 1)  // a == 1 or a == -1
    return copy(r,b,a->sign);

  struct
  {
    a_BigInt n;
    Digit    d;
  }
  c;

  Unit mag;
  if (b > 0)
  {
    c.n.sign = 1;
    mag = b;
  }
  else
  {
    c.n.sign = -1;
    mag = -b;
  }
  if ((c.n.digits[1] = HIGH(mag)))
  {
    c.n.len = 2;
    c.n.digits[0] = LOW(mag);
    return mul(r,a,&c.n);
  }
  else
  {
    a_BigInt * result = alloc(r,a->len+1);
    umul(result,a,mag);
    result->sign = a->sign == 1 ? c.n.sign : -c.n.sign;
    if (result != r)
      kill(r);
    return result;
  }
}

//////////////////////////////////////////////////////////////////////////////
//  Unsigned division and modulo arithmetic.
//  Assume a > b.
//////////////////////////////////////////////////////////////////////////////

static a_BigInt* udiv_mod( a_BigInt* r, a_BigInt* a, const a_BigInt* b)
{
  Digit * x, * x_hi, * x_lo;
  const Digit * y, * y_hi, * y_lo;
  Digit * z;

  Bool need_quotient = r != 0;
  /////////////////////////////////////////////////////////////
  //  Set up the indices
  /////////////////////////////////////////////////////////////
  z    = r->digits + a->len - b->len;
  x_hi = a->digits + a->len - 1;
  x_lo = a->digits + a->len - b->len;
  y_hi = b->digits + b->len - 1;
  y_lo = b->digits;

  Digit m1, m2, m3;
  m1    = y_hi[0];   // The most significant digit of denominator
  m2    = b->len == 1 ? 0 : y_hi[-1];  // The next most significant digit
  m3    = m1 + 1;

  Unit top = 0, quotient_min, quotient_max, quotient;
  for (  ;z >= r->digits; z--, x_hi--, x_lo--)
  {
    top = (top << Bits_per_digit) + *x_hi;

    /////////////////////////////////////////////////////////////
    //  Compute the range of the quotient.  We'll have to very
    //  careful to avoid overflow here.
    /////////////////////////////////////////////////////////////
    quotient_max = (top + 1) / m1;
    quotient_min = top / m3;

    /////////////////////////////////////////////////////////////
    //  Narrow down the quotient value using a binary search
    /////////////////////////////////////////////////////////////
    Digit x_low = x_hi == a->digits ? 0 : x_hi[-1];
    while ( quotient_min < quotient_max )
    {
      quotient = (quotient_min + quotient_max) / 2;
      if (quotient == quotient_min)
        break;
      Digit low;
      Unit product;
      product = quotient * m2;
      low     = LOW(product);
      product = HIGH(product) + quotient * m1;
      if (top > product)
        quotient_min = quotient;
      else if (top < product)
        quotient_max = quotient;
      else if (x_low > low)
        quotient_min = quotient;
      else if (x_low < low)
        quotient_max = quotient;
      else
        break;
    }

    /////////////////////////////////////////////////////////////
    //  Now we know the range of the quotient within 1
    /////////////////////////////////////////////////////////////
    quotient = (quotient_min + quotient_max + 1) / 2;

    /////////////////////////////////////////////////////////////
    //  Compute a -= quotient * b
    /////////////////////////////////////////////////////////////
    if (quotient != 0)
    {
      Unit borrow;
      for (x = x_lo, y = y_lo, borrow = 0; x <= x_hi; x++, y++)
      {
        borrow  = *x - *y * quotient - borrow;
        *x      = LOW(borrow);
        borrow  = HIGH(borrow);
        if (borrow)
          borrow = Max_digit - borrow;
      }
      if (borrow)
      { // If we have missed by 1, add back one copy
        if (x < a->digits + a->len && *x >= borrow)
          *x -= borrow;
        else
        {
          quotient--;
          Unit carry;
          for (x = x_lo, y = y_lo, carry = 0; x <= x_hi; x++, y++)
          {
            carry += *x + *y;
            *x     = LOW(carry);
            carry  = HIGH(carry);
          }
        }
      }
    }

    if (need_quotient)
      *z = quotient;
    top = *x_hi;
  }
  if (need_quotient)
  {
    r->len = a->len - b->len + 1;
    normalize(r);
  }
  normalize(a);
  return r;
}

//////////////////////////////////////////////////////////////////////////////
//  Signed division
//////////////////////////////////////////////////////////////////////////////
a_BigInt* div( a_BigInt* r, const a_BigInt* a, const a_BigInt* b)
{
  //////////////////////////////////////////////////////////////
  // Check for zeros and ones first
  //////////////////////////////////////////////////////////////
  if (a->sign == 0)
    return make_zero(r);
  if (b->sign == 0)
  {
    BigInt::error_handler("Division by zero");
    return make_zero(r);
  }
  a_BigInt * result;
  int result_sign = a->sign ? b->sign : -b->sign;
  if (b->len == 1 && b->digits[0] == 1)
    result = copy(r,a);
  else if (b->len == 1)
  {
    //////////////////////////////////////////////////////////////
    // fast division for small values
    //////////////////////////////////////////////////////////////
    result = alloc(r,a->len);
    udiv(result,a,b->digits[0]);
    if (result != r)
      kill(r);
  }
  else
  {
    //////////////////////////////////////////////////////////////
    // If the magnitude of a is smaller than that of b, the result
    // is zero.  If the magnitude is the same, its either 1 or -1
    //////////////////////////////////////////////////////////////
    int mag_diff = ucmp(a,b);
    if (mag_diff == 0)
      return copy(r,1,result_sign);
    if (mag_diff < 0)
      return make_zero(r);

    //////////////////////////////////////////////////////////////
    //  Allocate space for the divisor and result
    //////////////////////////////////////////////////////////////
    int divisor_len = a->len - b->len + 1;
    if (r == a || r == b)
    {  // Allocate space for the result
      result = new (divisor_len) a_BigInt;
    }
    else
    {
      result = alloc(r,divisor_len);
    }
    a_BigInt * divisor = copy(0,a);
    //////////////////////////////////////////////////////////////
    // Now perform unsigned division.
    //////////////////////////////////////////////////////////////
    result = udiv_mod(result,divisor,b);
    delete divisor;
    if (result != r)
      kill(r);
  }
  result->sign = result_sign;
  return result;
}

//////////////////////////////////////////////////////////////////////////////
//  Signed division
//////////////////////////////////////////////////////////////////////////////

a_BigInt* div( a_BigInt* r, const a_BigInt* a, long b)
{
  //////////////////////////////////////////////////////////////
  // Check for zeros and ones first
  //////////////////////////////////////////////////////////////
  if (a->sign == 0)
    return make_zero(r);
  if (b == 0)
  {
    BigInt::error_handler("Division by zero");
    return make_zero(r);
  }
  a_BigInt* result;
  int result_sign = a->sign ? b > 0 : b < 0;
  if (b == 1 || b == -1)
    result = copy(r,a);
  else
  {
    result = alloc(r,a->len);
    Unit mag = abs(b);
    if (b >= Max_digit)
    {
      struct
      {
        a_BigInt n;
        Digit    d;
      }
      c;
      c.n.len = 2;
      c.n.digits[0] = LOW(mag);
      c.n.digits[1] = HIGH(mag);
      a_BigInt* divisor = copy(0,a);
      udiv_mod(result,divisor,&c.n);
      delete divisor;
    }
    else
    {
      udiv(result,a,mag);
    }
    if (result != r)
      kill(r);
  }
  result->sign = result_sign;
  return result;
}

//////////////////////////////////////////////////////////////////////////////
// Signed modulo
//////////////////////////////////////////////////////////////////////////////

a_BigInt* mod( a_BigInt* r, const a_BigInt* a, const a_BigInt* b)
{
  //////////////////////////////////////////////////////////////
  // Check for zeros and ones first
  //////////////////////////////////////////////////////////////
  if (a->sign == 0)
    return make_zero(r);
  if (b->sign == 0)
  {
    BigInt::error_handler("Modulo by zero");
    return make_zero(r);
  }
  if (b->len == 1 && b->digits[0] == 1)
    return make_zero(r);
  int result_sign = a->sign == 1 ? b->sign : -b->sign;
  if (b->len == 1)
  {
    Digit m = udiv(0,a,b->digits[0]);
    if (m == 0)
      return make_zero(r);
    else
      return copy(r,m,result_sign);
  }
  a_BigInt* result;
  int mag_diff = ucmp(a,b);
  if (mag_diff == 0)
    return make_zero(r);
  if (mag_diff < 0)
    result = copy(r,a);
  else
  {
    //////////////////////////////////////////////////////////////
    //  Allocate space for the divisor and result
    //////////////////////////////////////////////////////////////
    if (r == a && r != b)
      result = copy(r,a);
    else
      result = copy(0,a);
    udiv_mod(0,result,b);
    if (result != r)
      kill(r);
  }
  result->sign = result_sign;
  return result;
}

//////////////////////////////////////////////////////////////////////////////
//  Signed modulo
//////////////////////////////////////////////////////////////////////////////

a_BigInt* mod( a_BigInt* r, const a_BigInt* a, long b)
{
  //////////////////////////////////////////////////////////////
  // Check for zeros and ones first
  //////////////////////////////////////////////////////////////
  if (a->sign == 0)
    return make_zero(r);
  if (b == 0)
  {
    BigInt::error_handler("Modulo by zero");
    return make_zero(r);
  }
  a_BigInt* result = 0;
  int result_sign = a->sign ? b > 0 : b < 0;
  if (b == 1 || b == -1)
    return make_zero(r);
  else
  {
    Unit mag = abs(b);
    if (b >= Max_digit)
    {
      struct
      {
        a_BigInt n;
        Digit    d;
      }
      c;
      if (r != a)
        result = copy(r,a);
      c.n.len = 2;
      c.n.digits[0] = LOW(mag);
      c.n.digits[1] = HIGH(mag);
      udiv_mod(0,result,&c.n);
      if (result != r)
        kill(r);
    }
    else
    {
      Digit mod = udiv(0,a,mag);
      if (mod == 0)
        return make_zero(r);
      else
        return copy(r,mod,result_sign);
    }
  }
  result->sign = result_sign;
  return result;
}

//////////////////////////////////////////////////////////////////////////////
//  Bit and/or/xor
//////////////////////////////////////////////////////////////////////////////

a_BigInt* andor( a_BigInt* r, const a_BigInt* a, const a_BigInt* b, char op)
{
  a_BigInt* result;
  if (a->len < b->len)
  {
    const a_BigInt* swap = a;
    a = b;
    b = swap;
  }
  int len = op == '&' ? b->len : a->len;
  result = alloc(r, len);
  result->sign = a->sign >= 0 ? b->sign : -b->sign;
  result->len = len;
  register const Digit * x, * y, * limit;
  register Digit * z;
  x = a->digits;
  y = b->digits;
  z = result->digits;
  limit = y + b->len;
  switch (op)
  {
  case '&':
    while (y < limit)
      *z++ = *x++ & *y++;
    break;
  case '|':
    while (y < limit)
      *z++ = *x++ | *y++;
    for (limit = x + len; x < limit; )
      *z++ = *x++;
    break;
  case '^':
    while (y < limit)
      *z++ = *x++ ^ *y++;
    for (limit = x + len; x < limit; )
      *z++ = *x++;
    break;
  }
  normalize(result);
  if (result != r)
    kill(r);
  return result;
}

//////////////////////////////////////////////////////////////////////////////
//  Bit and/or/xor with a long
//////////////////////////////////////////////////////////////////////////////

a_BigInt* andor( a_BigInt* r, const a_BigInt* a, long b, char op)
{
  struct
  {
    a_BigInt n;
    Digit    d;
  }
  c;
  c.n.sign      = 0;
  c.n.digits[0] = b % Max_digit;
  c.n.digits[1] = b / Max_digit;
  c.n.len       = 2;
  return andor(r,a,&c.n,op);
}

//////////////////////////////////////////////////////////////////////////////
//  Bit one's complement
//////////////////////////////////////////////////////////////////////////////
//a_BigInt* not( a_BigInt* r, const a_BigInt* a)

a_BigInt* complement( a_BigInt* r, const a_BigInt* a)
{
  if (a->sign == 0)
    return make_zero(r);
  a_BigInt* result = alloc(r,a->len);
  register const Digit * x, * limit;
  register Digit * y;
  for (x = a->digits, y = result->digits, limit = x + a->len; x < limit; )
    *y++ = ~ *x++;
  result->len  = a->len;
  result->sign = a->sign;
  normalize(result);
  if (result != r)
    kill(r);
  return result;
}

//////////////////////////////////////////////////////////////////////////////
//  Left/right shift
//////////////////////////////////////////////////////////////////////////////

a_BigInt* shift( a_BigInt* r, const a_BigInt* a, const a_BigInt* b, int sign)
{
  if (b->sign == 0)
    return copy(r,a);   // a shift 0 == a
  int len = b->len == 1 ? b->digits[0] : b->digits[0] + b->digits[1] * Max_digit;
  if (b->sign == -1)
    len = -len;
  return shift(r,a,len,sign);
}

//////////////////////////////////////////////////////////////////////////////
//  Left/right shift with a long
//////////////////////////////////////////////////////////////////////////////

a_BigInt* shift( a_BigInt* r, const a_BigInt* a, long len, int sign)
{
  if (a->sign == 0)
    return make_zero(r);
  if (sign < 0)
    len = -len;
  int result_len = a->len + (len + Bits_per_digit + 1) / Bits_per_digit;
  a_BigInt* result = alloc(r,result_len);
  if (result != r)
    kill(r);

  return result;
}

//////////////////////////////////////////////////////////////////////////////
//  Type conversion to a double
//////////////////////////////////////////////////////////////////////////////

BigInt::operator double () const
{
  register double r = 0.0;
  register Digit * p, * limit;
  for (p = D->digits + D->len - 1, limit = D->digits; p >= limit; )
    r = r * Max_digit + *p--;
  if (D->sign == -1)
    r = -r;
  return r;
}

//////////////////////////////////////////////////////////////////////////////
//  Return the length (bit number of highest order) in the number
//////////////////////////////////////////////////////////////////////////////

int BigInt::length() const
{
  int l;
  for (l = D->len * sizeof(Digit) * 8; l > 0; l--)
    if ((*this)[l] != 0)
      break;
  return l;
}

//////////////////////////////////////////////////////////////////////////////
//  Miscellaneous
//////////////////////////////////////////////////////////////////////////////

void div_mod( const BigInt&, const BigInt&, BigInt&, BigInt&)
{
  /* unimplemented */
}

BigInt pow( const BigInt& a, const BigInt& b)
{
  if (a.sign() == 0)
    return a;
  if (b.sign() == 0)
    return 1;
  if (b.sign() < 0)
  {
    BigInt::error_handler("negative pow() unsupported");
    return 0;
  }
  BigInt n;
  int i;
  for (n = 1, i = b.length(); i > 0; i--)
  {
    n *= n;
    if (b[i])
      n *= a;
  }
  return n;
}


BigInt pow_mod( const BigInt& a, const BigInt& b, const BigInt& c)
{
  if (a.sign() == 0)
    return a;
  if (b.sign() == 0)
    return 1;
  if (b.sign() < 0)
  {
    BigInt::error_handler("negative pow_mod() unsupported");
    return 0;
  }
  BigInt n;
  int i;
  for (n = 1, i = b.length(); i > 0; i--)
  {
    n *= n;
    if (b[i])
      n *= a;
    n %= c;
  }
  return n;
}

BigInt gcd( BigInt a, BigInt b)
{
  for (;;)
  {
    if (a == (int)1)
      return b;
    if (b == (int)1)
      return a;
    if (a > b)
      a %= b;
    else
      b %= a;
  }
}

//////////////////////////////////////////////////////////////////////////////
//  Hashing
//////////////////////////////////////////////////////////////////////////////

unsigned int hash( const BigInt& a)
{
  unsigned int h = 0;
  for (int i = a.D->len - 1; i >= 0; i--)
    h += h + a.D->digits[i];
  return h;
}

//////////////////////////////////////////////////////////////////////////////
//  String conversion
//////////////////////////////////////////////////////////////////////////////

char * BigInt::makeString(char buf[], size_t length, unsigned int base) const
{
  char * cursor = buf;
  char * limit  = buf + length;

  if (D->sign == 0)
  {       // Check for zero
    if (length >= 2)
    {
      buf[0] = '0';
      buf[1] = '\0';
      return buf+2;
    }
    else
      return buf;
  }

  a_BigInt* a = copy(0,D);
  while (a->len > 0)
  {
    int digit = udiv(a,a,base);
    digit += digit >= 10 ? 'a' - 10 : '0';
    if (cursor == limit)
      break;
    *cursor++ = digit;
  }
  kill(a);

  if (D->sign == -1 && cursor < limit)
  {    // Insert sign
    *cursor++ = '-';
  }

  //////////////////////////////////////////////////////
  // Now swap characters within the buffer
  //////////////////////////////////////////////////////
  register char * p, * q;
  for (p = buf, q = cursor - 1; p < q; p++, q--)
  {
    char c = *p;
    *p = *q;
    *q = c;
  }
  if (cursor < limit)
    *cursor = '\0';
  return cursor;
}

//////////////////////////////////////////////////////////////////////////////
// Print a BigInt
//////////////////////////////////////////////////////////////////////////////

std::ostream& operator << (std::ostream& out, const BigInt& n)
{
  char buffer[256];
  char * buf;
  size_t len = n.D->len * 5 + 3;
  if (len > sizeof(buffer))
    buf = new char [len];
  else
    buf = buffer;
  n.makeString(buf,len,10);
  out << buf;
  if (buf != buffer)
    delete [] buf;
  return out;
}

//////////////////////////////////////////////////////////////////////////////
// Construct a BigInt
//////////////////////////////////////////////////////////////////////////////

BigInt::BigInt( const char * number) : D(0)
{
  operator = (number);
}

//////////////////////////////////////////////////////////////////////////////
//  Make a BigInt from a string
//////////////////////////////////////////////////////////////////////////////

BigInt& BigInt::operator = (const char * number)
{
  parseString(number);
  return *this;
}

//////////////////////////////////////////////////////////////////////////////
//  Make a BigInt from a string
//////////////////////////////////////////////////////////////////////////////

int BigInt::parseString( const char * number, unsigned int base)
{
  BigInt n = 0;
  Bool negative = false;
  const char * p;
  char c;

  for (p = number; (c = *p); p++)
  {
    if (c == '-')
      negative = ! negative;
    else
      break;
  }

  for (  ; (c = *p); p++)
  {
    unsigned int digit;
    if (isdigit(c))
      digit = c - '0';
    else if (islower(c))
      digit = (c - 'a') + 10;
    else if (isupper(c))
      digit = (c - 'A') + 10;
    else if (isspace(c))
      continue;
    else
      break;
    if (digit >= base)
      break;
    n = n * 10 + (long)digit;
  }
  if (negative)
    n = -n;
  *this = n;
  return number - p;
}
