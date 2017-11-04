#ifndef LIBTURADOR_TURA_HELPERS_NONCOPYABLE_HPP_INCLUDED
#define LIBTURADOR_TURA_HELPERS_NONCOPYABLE_HPP_INCLUDED

namespace tura
{
namespace helpers
{
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
}
}

#endif // LIBTURADOR_TURA_HELPERS_NONCOPYABLE_HPP_INCLUDED
