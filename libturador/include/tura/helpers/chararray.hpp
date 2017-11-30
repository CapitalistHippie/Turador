#ifndef LIBTURADOR_TURA_HELPERS_CHARARRAY_HPP_INCLUDED
#define LIBTURADOR_TURA_HELPERS_CHARARRAY_HPP_INCLUDED

#include <cstring>
#include <istream>
#include <ostream>

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

  CharArray(const char* const other) { CopyFrom(other); }

  CharArray& operator=(const char* const other)
  {
    CopyFrom(other);

    return *this;
  }

  void CopyFrom(const char* const other) { strncpy(array, other, length); }

  unsigned int MaxLength() const { return length; }

  void ToLower() { std::transform(data[0], data[size()], tolower()); }
};

template<unsigned int length, unsigned int length2>
bool operator==(const CharArray<length>& left, const CharArray<length2>& right)
{
  return strcmp(left.array, right.array) == 0;
}

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

template<unsigned int length, unsigned int length2>
bool operator!=(const CharArray<length>& left, const CharArray<length2>& right)
{
  return strcmp(left.array, right.array) != 0;
}

template<unsigned int length>
bool operator!=(const CharArray<length>& left, const char* const right)
{
  return strcmp(left.array, right) != 0;
}

template<unsigned int length>
bool operator!=(const char* const right, const CharArray<length>& left)
{
  return left != right;
}

template<unsigned int length>
std::istream& operator>>(std::istream& stream, CharArray<length>& array)
{
  stream.getline(array.array, length, ' ');

  return stream;
}

template<unsigned int length>
std::ostream& operator<<(std::ostream& stream, const CharArray<length>& array)
{
  stream << array.array;

  return stream;
}
}
}

#endif // LIBTURADOR_TURA_HELPERS_CHARARRAY_HPP_INCLUDED
