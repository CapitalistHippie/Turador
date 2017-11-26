#ifndef LIBTURADOR_TURA_HELPERS_ARRAY_HPP_INCLUDED
#define LIBTURADOR_TURA_HELPERS_ARRAY_HPP_INCLUDED

#include <algorithm>
#include <ctype.h>
#include <system_error>
#include <utility>

#include "tura/error.h"

namespace tura
{
namespace helpers
{
template<typename T, unsigned int length>
class Array
{
public:
  typedef T value_type;
  typedef T& reference;
  typedef const T& const_reference;
  typedef T* pointer;
  typedef const T* const_pointer;
  typedef unsigned int size_type;

private:
  T data[length];

  size_type size_;

public:
  class iterator
  {
  public:
    typedef iterator self_type;
    typedef std::forward_iterator_tag iterator_category;
    iterator(pointer ptr)
      : ptr_(ptr)
    {
    }
    self_type operator++()
    {
      self_type i = *this;
      ptr_++;
      return i;
    }
    self_type operator++(int junk)
    {
      ptr_++;
      return *this;
    }
    reference operator*() { return *ptr_; }
    pointer operator->() { return ptr_; }
    bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
    bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }

  private:
    pointer ptr_;
  };

  class const_iterator
  {
  public:
    typedef const_iterator self_type;
    typedef unsigned int difference_type;
    typedef std::forward_iterator_tag iterator_category;
    const_iterator(const_pointer ptr)
      : ptr_(ptr)
    {
    }
    self_type operator++()
    {
      self_type i = *this;
      ptr_++;
      return i;
    }
    self_type operator++(int junk)
    {
      ptr_++;
      return *this;
    }
    const const_reference operator*() { return *ptr_; }
    const const_pointer operator->() { return ptr_; }
    bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
    bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }

  private:
    const_pointer ptr_;
  };

  iterator begin() { return iterator(data); }

  iterator end() { return iterator(data + size()); }

  const_iterator begin() const { return const_iterator(data); }

  const_iterator end() const { return const_iterator(data + size()); }

  T& operator[](size_type index)
  {
    if (index >= size())
    {
      throw std::system_error(std::make_error_code(Error::OutOfRange), "Index is out of range.");
    }

    return data[index];
  }

  const T& operator[](size_type index) const
  {
    if (index >= size())
    {
      throw std::system_error(std::make_error_code(Error::OutOfRange), "Index is out of range.");
    }

    return data[index];
  }

  size_type size() const { return size_; }

  Array()
    : size_(0)
  {
  }

  Array(size_type n)
    : size_(0)
  {
    if (n > length)
    {
      throw std::system_error(std::make_error_code(Error::OutOfRange), "Not enough space in array.");
    }

    size_ = n;
  }

  void Add(T item)
  {
    if (size() >= length)
    {
      throw std::system_error(std::make_error_code(Error::OutOfRange), "No more space in array.");
    }

    data[size()] = std::move(item);

    size_++;
  }

  template<typename... Args>
  void Emplace(Args&&... args)
  {
    if (size() >= length)
    {
      throw std::system_error(std::make_error_code(Error::OutOfRange), "No more space in array.");
    }

    data[size()] = T(args);

    size_++;
  }

  T* GetData() { return array; }
  const T* GetData() const { return array; }

  bool HasValue(const T& value) const
  {
    for (const auto& entry : *this)
    {
      if (value == entry)
      {
        return true;
      }
    }

    return false;
  }

  size_type IndexOf(const T& value) const
  {
    for (size_type i = 0; i < size(); ++i)
    {
      if (value == data[i])
      {
        return i;
      }
    }

    // TODO: Throw.
  }

  void Clear() { size_ = 0; }

  void Remove(size_type index)
  {
    if (index >= size() || index < 0)
    {
      // TODO: Throw.
    }

    for (size_type i = index; i < size() - 1; ++i)
    {
      data[i] = data[i + 1];
    }

    size_--;
  }
};
}
}

#endif // LIBTURADOR_TURA_HELPERS_ARRAY_HPP_INCLUDED
