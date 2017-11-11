#ifndef LIBTURADOR_TURA_DOMAIN_GAMEHELPERS_H_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_GAMEHELPERS_H_INCLUDED

#include <cstring>
#include <system_error>

#include "tura/domain/models/cargo.h"
#include "tura/domain/models/harbor.h"
#include "tura/domain/models/harborcargo.h"
#include "tura/domain/models/ship.h"
#include "tura/error.h"

namespace tura
{
namespace domain
{
inline const models::HarborCargo& GetHarborCargoByName(const models::Harbor& harbor, const char* const cargoName)
{
  // TODO: Remove the magic 15.
  for (unsigned int i = 0; i < 15; ++i)
  {
    if (cargoName == harbor.goods[i].cargo.name)
    {
      return harbor.goods[i];
    }
  }

  throw std::system_error(std::make_error_code(Error::UnknownCargo));
}

inline models::HarborCargo& GetHarborCargoByName(models::Harbor& harbor, const char* const cargoName)
{
  return const_cast<models::HarborCargo&>(GetHarborCargoByName(const_cast<const models::Harbor&>(harbor), cargoName));
}

inline const models::Cargo& GetShipCargoByName(const models::Ship& ship, const char* const cargoName)
{
  // TODO: Remove the magic 15.
  for (unsigned int i = 0; i < 15; ++i)
  {
    if (cargoName == ship.goods[i].name)
    {
      return ship.goods[i];
    }
  }

  throw std::system_error(std::make_error_code(Error::UnknownCargo));
}

inline models::Cargo& GetShipCargoByName(models::Ship& ship, const char* const cargoName)
{
  return const_cast<models::Cargo&>(GetShipCargoByName(const_cast<const models::Ship&>(ship), cargoName));
}

inline unsigned int GetShipUsedCargoSpace(const models::Ship& ship)
{
  unsigned int usedCargoSpace = 0;

  for (auto cargo : ship.goods)
  {
    usedCargoSpace += cargo.amount;
  }

  return usedCargoSpace;
}
}
}

#endif // LIBTURADOR_TURA_DOMAIN_GAMEHELPERS_H_INCLUDED
