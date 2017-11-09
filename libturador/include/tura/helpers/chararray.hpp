#ifndef LIBTURADOR_TURA_HELPERS_CHARARRAY_HPP_INCLUDED
#define LIBTURADOR_TURA_HELPERS_CHARARRAY_HPP_INCLUDED

#include <cstring>

#include "tura/error.h"

namespace tura
{
namespace helpers
{
template<unsigned int length>
class CharArray
{
public:
  char array[length];

  CharArray()
    : array("")
  {
  }

  CharArray& operator=(const char* const other)
  {
    CopyFrom(other);

    return *this;
  }

  void CopyFrom(const char* const other) { strncpy(array, other, length); }

  unsigned int MaxLength() const { return length; }
};

template<unsigned int length>
bool operator==(const CharArray<length>& left, const char* const right)
{
  return strcmp(left.array, right) == 0;
}

template<unsigned int length>
bool operator==(const char* const right, const CharArray<length>& left)
{
  return left == right;
}
}
}

#endif // LIBTURADOR_TURA_HELPERS_CHARARRAY_HPP_INCLUDED
