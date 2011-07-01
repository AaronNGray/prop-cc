#ifndef prop_tuple4_h
#define prop_tuple4_h

template <class T1, class T2, class T3, class T4>
class Tuple4
{
public:
  T1 _1;
  T2 _2;
  T3 _3;
  T4 _4;

  inline Tuple4()
  {}
  inline Tuple4(
    const T1& x1,
    const T2& x2,
    const T3& x3,
    const T4& x4
  ) :
      _1(x1),
      _2(x2),
      _3(x3),
      _4(x4)
  {}
}
;

template <class T1, class T2, class T3, class T4>
inline Tuple4<T1, T2, T3, T4> mkTuple4(
  const T1& x1,
  const T2& x2,
  const T3& x3,
  const T4& x4
)
{
  return Tuple4<T1, T2, T3, T4>(x1, x2, x3, x4);
}

#endif
