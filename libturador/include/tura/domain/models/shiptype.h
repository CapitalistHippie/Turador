#ifndef LIBTURADOR_TURA_DOMAIN_MODELS_SHIPTYPE_H_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_MODELS_SHIPTYPE_H_INCLUDED

#include "tura/domain/models/shipsizeclass.h"
#include "tura/domain/models/shipweightclass.h"

namespace tura
{
namespace domain
{
namespace models
{
struct ShipType
{
  char name[64] = "";
  unsigned int price = 0;
  unsigned int cargoSpaceMax = 0;
  unsigned int cannonSpaceMax = 0;
  unsigned int hitPointsMax = 0;
  ShipWeightClass weightClass = ShipWeightClass::Normal;
  ShipSizeClass sizeClass = ShipSizeClass::Normal;
};
}
}
}

#endif // LIBTURADOR_TURA_DOMAIN_MODELS_SHIPTYPE_H_INCLUDED
