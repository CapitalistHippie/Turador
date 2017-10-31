#ifndef LIBTURADOR_TURA_MODELS_SHIP_H_INCLUDED
#define LIBTURADOR_TURA_MODELS_SHIP_H_INCLUDED

#include "cargo.h"
#include "shiptype.h"

namespace tura
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

#endif // LIBTURADOR_TURA_MODELS_SHIP_H_INCLUDED
