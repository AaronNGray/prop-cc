#ifndef prop_tuple12_h
#define prop_tuple12_h

template <class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12>
class Tuple12
{
public:
  T1 _1;
  T2 _2;
  T3 _3;
  T4 _4;
  T5 _5;
  T6 _6;
  T7 _7;
  T8 _8;
  T9 _9;
  T10 _10;
  T11 _11;
  T12 _12;

  inline Tuple12()
  {}
  inline Tuple12(
    const T1& x1,
    const T2& x2,
    const T3& x3,
    const T4& x4,
    const T5& x5,
    const T6& x6,
    const T7& x7,
    const T8& x8,
    const T9& x9,
    const T10& x10,
    const T11& x11,
    const T12& x12
  ) :
      _1(x1),
      _2(x2),
      _3(x3),
      _4(x4),
      _5(x5),
      _6(x6),
      _7(x7),
      _8(x8),
      _9(x9),
      _10(x10),
      _11(x11),
      _12(x12)
  {}
}
;

template <class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12>
inline Tuple12<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12> mkTuple12(
  const T1& x1,
  const T2& x2,
  const T3& x3,
  const T4& x4,
  const T5& x5,
  const T6& x6,
  const T7& x7,
  const T8& x8,
  const T9& x9,
  const T10& x10,
  const T11& x11,
  const T12& x12
)
{
  return Tuple12<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12>(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12);
}

#endif
