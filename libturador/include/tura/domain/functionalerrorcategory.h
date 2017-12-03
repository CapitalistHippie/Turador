#ifndef LIBTURADOR_TURA_DOMAIN_FUNCTIONALERRORCATEGORY_H_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_FUNCTIONALERRORCATEGORY_H_INCLUDED

#include <system_error>

#include "functionalerror.h"

namespace tura
{
namespace domain
{
class FunctionalErrorCategory : public std::error_category
{
public:
  virtual const char* name() const noexcept;
  virtual std::string message(int ev) const;
}; // class FunctionalErrorCategory

const std::error_category& GetFunctionalErrorCategory();
} // namespace domain
} // namespace tura

namespace std
{
template<>
struct is_error_code_enum<tura::domain::FunctionalError> : true_type
{
};

error_code make_error_code(tura::domain::FunctionalError);
} // namespace std

#endif // LIBTURADOR_TURA_DOMAIN_FUNCTIONALERRORCATEGORY_H_INCLUDED
