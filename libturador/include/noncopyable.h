#ifndef LIBTURADOR_NONCOPYABLE_HPP_INCLUDED
#define LIBTURADOR_NONCOPYABLE_HPP_INCLUDED

class Noncopyable
{
private:
  Noncopyable(const Noncopyable&) = delete;
  Noncopyable& operator=(const Noncopyable&) = delete;

public:
  Noncopyable() = default;
  ~Noncopyable() = default;
};

#endif // LIBTURADOR_NONCOPYABLE_HPP_INCLUDED
