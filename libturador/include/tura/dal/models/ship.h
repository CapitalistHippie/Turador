#ifndef LIBTURADOR_TURA_DAL_MODELS_SHIP_H_INCLUDED
#define LIBTURADOR_TURA_DAL_MODELS_SHIP_H_INCLUDED

#include "tura/dal/models/cargo.h"
#include "tura/dal/models/shiptype.h"

namespace tura
{
namespace dal
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

#endif // LIBTURADOR_TURA_DAL_MODELS_SHIP_H_INCLUDED
