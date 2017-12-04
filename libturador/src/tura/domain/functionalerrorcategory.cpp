#include "tura/domain/functionalerrorcategory.h"

using namespace tura;
using namespace tura::domain;

const char* FunctionalErrorCategory::name() const noexcept
{
  return "Tura Domain Functional Error Category";
}

std::string FunctionalErrorCategory::message(int ev) const
{
  return "";
}

const std::error_category& tura::domain::GetFunctionalErrorCategory()
{
  static FunctionalErrorCategory instance;
  return instance;
}

std::error_code std::make_error_code(FunctionalError error)
{
  return std::error_code(static_cast<int>(error), tura::domain::GetFunctionalErrorCategory());
}
