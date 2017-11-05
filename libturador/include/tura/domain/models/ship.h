#ifndef LIBTURADOR_TURA_DOMAIN_MODELS_SHIP_H_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_MODELS_SHIP_H_INCLUDED

#include "tura/domain/models/cargo.h"
#include "tura/domain/models/shiptype.h"

namespace tura
{
namespace domain
{
namespace models
{
struct Ship
{
  ShipType shipType;
  Cargo goods[15]; // TODO: Remove magic 15.
};
}
}
}

#endif // LIBTURADOR_TURA_DOMAIN_MODELS_SHIP_H_INCLUDED
