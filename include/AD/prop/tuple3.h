#ifndef prop_tuple3_h
#define prop_tuple3_h

template <class T1, class T2, class T3>
class Tuple3
{
public:
  T1 _1;
  T2 _2;
  T3 _3;

  inline Tuple3()
  {}
  inline Tuple3(
    const T1& x1,
    const T2& x2,
    const T3& x3
  ) :
      _1(x1),
      _2(x2),
      _3(x3)
  {}
}
;

template <class T1, class T2, class T3>
inline Tuple3<T1, T2, T3> mkTuple3(
  const T1& x1,
  const T2& x2,
  const T3& x3
)
{
  return Tuple3<T1, T2, T3>(x1, x2, x3);
}

#endif
