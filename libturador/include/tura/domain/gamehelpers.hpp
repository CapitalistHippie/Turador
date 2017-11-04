#ifndef LIBTURADOR_TURA_DOMAIN_GAMEHELPERS_H_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_GAMEHELPERS_H_INCLUDED

#include <cstring>
#include <system_error>

#include "tura/dal/models/cargo.h"
#include "tura/dal/models/harbor.h"
#include "tura/dal/models/harborcargo.h"
#include "tura/dal/models/ship.h"
#include "tura/error.h"

namespace tura
{
namespace domain
{
inline const dal::models::HarborCargo& GetHarborCargoByName(const dal::models::Harbor& harbor,
                                                            const char* const cargoName)
{
  // TODO: Remove the magic 15.
  for (unsigned int i = 0; i < 15; ++i)
  {
    if (strcmp(cargoName, harbor.goods[i].cargo.name) == 0)
    {
      return harbor.goods[i];
    }
  }

  throw std::system_error(std::make_error_code(Error::UnknownEntityName));
}

inline dal::models::HarborCargo& GetHarborCargoByName(dal::models::Harbor& harbor, const char* const cargoName)
{
  return const_cast<dal::models::HarborCargo&>(
    GetHarborCargoByName(const_cast<const dal::models::Harbor&>(harbor), cargoName));
}

inline const dal::models::Cargo& GetShipCargoByName(const dal::models::Ship& ship, const char* const cargoName)
{
  // TODO: Remove the magic 15.
  for (unsigned int i = 0; i < 15; ++i)
  {
    if (strcmp(cargoName, ship.goods[i].name) == 0)
    {
      return ship.goods[i];
    }
  }

  throw std::system_error(std::make_error_code(Error::UnknownEntityName));
}

inline dal::models::Cargo& GetShipCargoByName(dal::models::Ship& ship, const char* const cargoName)
{
  return const_cast<dal::models::Cargo&>(GetShipCargoByName(const_cast<const dal::models::Ship&>(ship), cargoName));
}

inline unsigned int GetShipUsedCargoSpace(const dal::models::Ship& ship)
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
