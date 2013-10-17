So far
======

So far, `main.cpp` contains code which disproves my general hypothesis that if f(a<sup>n</sup>) = f<sup>n</sup>(a) where f : G -> G then f is a homomorphism. However, it does not disprove this hypothesis for cyclic groups. In fact, I have proved it true for cyclic groups (by hand, of course).

Class structure
===============

`ANGroup.h` provides a template for an algebraic group. In this case, a group is just an array of elements of the templated type. For example, `ANGroup<float>` would represent a group containing floating point elements. The type used for the group template should support a product operator, `*`. In the future, it will probably also require inversion through the `!` operator.

In addition to `ANGroup`, the `ANGroup.h` header provides an abstract map between a group and itself. The type `ANGroupMap<T>` contains a mapping of some `T` to some `T`. That is, a map from T -> T. For convenience, `ANGroupMap` orders its elements.

`ANModNumber.h` provides the classes `ANModNumber`, `ANModNumberPlus`, and `ANModNumberMult`. The base class, `ANModNumber`, should not be used externally. The other two classes represent elements of the integers modulo n.

`ANPermutation.h` represents a permutation (i.e. an element of S<sub>n</sub>). These permutations work with the product operator and thus can be used as group elements.