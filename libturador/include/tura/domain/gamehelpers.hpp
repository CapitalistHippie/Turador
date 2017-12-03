#ifndef LIBTURADOR_TURA_DOMAIN_GAMEHELPERS_H_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_GAMEHELPERS_H_INCLUDED

#include "tura/domain/models/ship.h"

namespace tura
{
namespace domain
{
inline unsigned int GetShipUsedCargoSpace(const models::Ship& ship)
{
  unsigned int usedCargoSpace = 0;

  for (const auto& cargo : ship.goods)
  {
    usedCargoSpace += cargo.amount;
  }

  return usedCargoSpace;
}
}
}

#endif // LIBTURADOR_TURA_DOMAIN_GAMEHELPERS_H_INCLUDED
