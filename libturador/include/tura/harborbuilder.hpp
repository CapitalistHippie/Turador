#ifndef LIBTURADOR_TURA_HARBORBUILDER_H_INCLUDED
#define LIBTURADOR_TURA_HARBORBUILDER_H_INCLUDED

#include <string.h>

#include "models/harbor.h"

namespace tura
{
class HarborBuilder
{
private:
  const char* name;

public:
  HarborBuilder()
    : name("")
  {
  }

  HarborBuilder& WithName(const char* const name)
  {
    this->name = name;

    return *this;
  }

  models::Harbor Build() const
  {
    auto harbor = models::Harbor();
    strncpy(harbor.name, name, sizeof(harbor.name));

    return harbor;
  }
};
}

#endif // LIBTURADOR_TURA_HARBORBUILDER_H_INCLUDED
