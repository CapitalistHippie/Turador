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
  Noncopyable(Noncopyable&& other) = default;
  Noncopyable& operator=(Noncopyable&& other) = default;
};

#endif // LIBTURADOR_NONCOPYABLE_HPP_INCLUDED
