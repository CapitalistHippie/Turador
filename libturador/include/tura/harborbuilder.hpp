#ifndef LIBTURADOR_TURA_HARBORBUILDER_H_INCLUDED
#define LIBTURADOR_TURA_HARBORBUILDER_H_INCLUDED

#include <cstring>

#include "tura/domain/models/harbor.h"

namespace tura
{
class HarborBuilder
{
private:
  domain::models::Harbor harbor;
  unsigned int cargoIndex;

public:
  HarborBuilder()
    : cargoIndex(0)
  {
  }

  HarborBuilder& WithName(const char* const name)
  {
    harbor.name = name;

    return *this;
  }

  HarborBuilder& WithCargo(const char* const cargoName, unsigned int cargoAmount, unsigned int cargoPrice)
  {
    // TODO: Check cargo index count.

    harbor.goods[cargoIndex].cargo.name = cargoName;
    harbor.goods[cargoIndex].cargo.amount = cargoAmount;
    harbor.goods[cargoIndex].price = cargoPrice;

    cargoIndex++;

    return *this;
  }

  domain::models::Harbor Build() const { return harbor; }
};
}

#endif // LIBTURADOR_TURA_HARBORBUILDER_H_INCLUDED
