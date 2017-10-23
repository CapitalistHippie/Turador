#include "tura/error.h"

namespace
{
class TuraErrorCategory : public std::error_category
{
public:
  const char* name() const noexcept override;
  std::string message(int ev) const override;
};

const char* TuraErrorCategory::name() const noexcept
{
  return "flights";
}

std::string TuraErrorCategory::message(int ev) const
{
  switch (static_cast<tura::Error>(ev))
  {
    default:
      return "Unrecognized error.";
  }
}

const TuraErrorCategory turaErrorCategory{};
}

namespace std
{
error_code make_error_code(tura::Error e)
{
  return { static_cast<int>(e), turaErrorCategory };
}
}
