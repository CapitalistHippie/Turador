#ifndef LIBTURADOR_TURA_SHIPBUILDER_H_INCLUDED
#define LIBTURADOR_TURA_SHIPBUILDER_H_INCLUDED

#include <cstring>

#include "tura/domain/models/cargo.h"
#include "tura/domain/models/ship.h"
#include "tura/domain/models/shiptype.h"

namespace tura
{
class ShipBuilder
{
private:
  domain::models::Ship ship;

public:
  ShipBuilder& WithShipType(domain::models::ShipType shipType)
  {
    ship.shipType = shipType;

    return *this;
  }

  ShipBuilder& WithCargo(const char* const cargoName, unsigned int cargoAmount)
  {
    domain::models::Cargo cargo;
    cargo.name = cargoName;
    cargo.amount = cargoAmount;

    ship.goods.Add(cargo);

    return *this;
  }

  domain::models::Ship Build() const { return ship; }
};
}

#endif // LIBTURADOR_TURA_SHIPBUILDER_H_INCLUDED
