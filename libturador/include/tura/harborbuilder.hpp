#ifndef LIBTURADOR_TURA_HARBORBUILDER_H_INCLUDED
#define LIBTURADOR_TURA_HARBORBUILDER_H_INCLUDED

#include <cstring>

#include "tura/domain/models/harbor.h"
#include "tura/domain/models/harborcargo.h"

namespace tura
{
class HarborBuilder
{
private:
  domain::models::Harbor harbor;

public:
  HarborBuilder& WithName(const char* const name)
  {
    harbor.name = name;

    return *this;
  }

  HarborBuilder& WithCargo(const char* const cargoName, unsigned int cargoAmount, unsigned int cargoPrice)
  {
    domain::models::HarborCargo cargo;
    cargo.cargo.name = cargoName;
    cargo.cargo.amount = cargoAmount;
    cargo.price = cargoPrice;

    harbor.goods.Add(cargo);

    return *this;
  }

  domain::models::Harbor Build() const { return harbor; }
};
}

#endif // LIBTURADOR_TURA_HARBORBUILDER_H_INCLUDED
