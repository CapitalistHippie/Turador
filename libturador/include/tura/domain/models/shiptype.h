#ifndef LIBTURADOR_TURA_DOMAIN_MODELS_SHIPTYPE_H_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_MODELS_SHIPTYPE_H_INCLUDED

#include "tura/domain/models/shipsizeclass.h"
#include "tura/domain/models/shipweightclass.h"
#include "tura/helpers/chararray.hpp"

namespace tura
{
namespace domain
{
namespace models
{
struct ShipType
{
  helpers::CharArray<64> name;
  unsigned int price = 0;
  unsigned int cargoSpaceMax = 0;
  unsigned int cannonSpaceMax = 0;
  unsigned int hitPointsMax = 0;
  ShipWeightClass weightClass = ShipWeightClass::Light;
  ShipSizeClass sizeClass = ShipSizeClass::Small;
};
}
}
}

#endif // LIBTURADOR_TURA_DOMAIN_MODELS_SHIPTYPE_H_INCLUDED
