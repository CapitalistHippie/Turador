#ifndef LIBTURADOR_TURA_DOMAIN_MODELS_SHIP_H_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_MODELS_SHIP_H_INCLUDED

#include "tura/domain/models/cargo.h"
#include "tura/domain/models/shiptype.h"
#include "tura/helpers/array.hpp"

namespace tura
{
namespace domain
{
namespace models
{
struct Ship
{
  ShipType shipType;
  helpers::Array<Cargo, 32> goods;
  int hitPoints = 0;
  helpers::Array<Cannon, 64> cannons;
};
}
}
}

#endif // LIBTURADOR_TURA_DOMAIN_MODELS_SHIP_H_INCLUDED
