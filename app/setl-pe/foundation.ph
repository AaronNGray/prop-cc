#ifndef foundational_stuff_h
#define foundational_stuff_h

datatype List<a>   :: collectable = #[ ] | #[ a ... List<a> ];
datatype Vector<a> :: collectable = [| a |];
datatype Pair<a,b> :: collectable = PAIR { fst : a, snd : b };
datatype Option<a> :: collectable = NONE | SOME(a);
type Id = const char *;

#endif
