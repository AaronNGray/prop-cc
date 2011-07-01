#ifndef prop_tuple2_h
#define prop_tuple2_h

template <class T1, class T2>
class Tuple2
{
public:
  T1 _1;
  T2 _2;

  inline Tuple2()
  {}
  inline Tuple2(
    const T1& x1,
    const T2& x2
  ) :
      _1(x1),
      _2(x2)
  {}
}
;

template <class T1, class T2>
inline Tuple2<T1, T2> mkTuple2(
  const T1& x1,
  const T2& x2
)
{
  return Tuple2<T1, T2>(x1, x2);
}

#endif
