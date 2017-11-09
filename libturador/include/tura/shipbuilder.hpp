#ifndef LIBTURADOR_TURA_SHIPBUILDER_H_INCLUDED
#define LIBTURADOR_TURA_SHIPBUILDER_H_INCLUDED

#include <cstring>

#include "tura/domain/models/ship.h"
#include "tura/domain/models/shiptype.h"

namespace tura
{
class ShipBuilder
{
private:
  domain::models::Ship ship;
  unsigned int cargoIndex;

public:
  ShipBuilder()
    : cargoIndex(0)
  {
  }

  ShipBuilder& WithShipType(domain::models::ShipType shipType)
  {
    ship.shipType = shipType;

    return *this;
  }

  ShipBuilder& WithCargo(const char* const cargoName, unsigned int cargoAmount)
  {
    // TODO: Check cargo index count.

    ship.goods[cargoIndex].name = cargoName;
    ship.goods[cargoIndex].amount = cargoAmount;

    cargoIndex++;

    return *this;
  }

  domain::models::Ship Build() const { return ship; }
};
}

#endif // LIBTURADOR_TURA_SHIPBUILDER_H_INCLUDED
