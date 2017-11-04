#ifndef LIBTURADOR_TURA_SHIPBUILDER_H_INCLUDED
#define LIBTURADOR_TURA_SHIPBUILDER_H_INCLUDED

#include <cstring>

#include "tura/dal/models/ship.h"
#include "tura/dal/models/shiptype.h"

namespace tura
{
class ShipBuilder
{
private:
  dal::models::Ship ship;
  unsigned int cargoIndex;

public:
  ShipBuilder()
    : cargoIndex(0)
  {
  }

  ShipBuilder& WithShipType(dal::models::ShipType shipType)
  {
    ship.shipType = shipType;

    return *this;
  }

  ShipBuilder& WithCargo(const char* const cargoName, unsigned int cargoAmount)
  {
    // TODO: Check cargo index count.

    strncpy(ship.goods[cargoIndex].name, cargoName, sizeof(ship.goods[cargoIndex].name));
    ship.goods[cargoIndex].amount = cargoAmount;

    cargoIndex++;

    return *this;
  }

  dal::models::Ship Build() const { return ship; }
};
}

#endif // LIBTURADOR_TURA_SHIPBUILDER_H_INCLUDED
