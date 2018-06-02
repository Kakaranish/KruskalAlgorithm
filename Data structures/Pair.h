#ifndef _PAIR_H
#define _PAIR_H

template <typename T, typename U>
struct Pair
{
  public:
    T first;
    U second;

    Pair(T _first, U _second) : first(_first), second(_second) {}
};

#endif