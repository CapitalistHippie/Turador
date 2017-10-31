#ifndef LIBTURADOR_TURA_SHIPBUILDER_H_INCLUDED
#define LIBTURADOR_TURA_SHIPBUILDER_H_INCLUDED

#include <string.h>

#include "models/ship.h"
#include "models/shiptype.h"

namespace tura
{
class ShipBuilder
{
private:
  models::Ship ship;
  unsigned int cargoIndex;

public:
  ShipBuilder()
    : cargoIndex(0)
  {
  }

  ShipBuilder& WithShipType(models::ShipType shipType)
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

  models::Ship Build() const { return ship; }
};
}

#endif // LIBTURADOR_TURA_SHIPBUILDER_H_INCLUDED
