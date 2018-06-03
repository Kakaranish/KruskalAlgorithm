#ifndef _PAIR_H
#define _PAIR_H
#include <fstream>

template <typename T, typename U>
struct Pair
{
public:
  T first;
  U second;

  friend std::ostream &operator<<(std::ostream &s, const Pair<T, U> &pair)
  {
    s << pair.first << "\t" << pair.second;
    return s;
  }
  Pair() = default;
  Pair(T _first, U _second) : first(_first), second(_second) {}
};

#endif