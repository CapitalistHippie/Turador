#ifndef LIBTURADOR_TURA_GAMEHELPERS_H_INCLUDED
#define LIBTURADOR_TURA_GAMEHELPERS_H_INCLUDED

#include <cstring>

#include "models/cargo.h"
#include "models/game.h"
#include "models/harborcargo.h"
#include "models/ship.h"

namespace tura
{
inline const models::HarborCargo& GetCurrentHarborCargoByName(const models::Game& gameData, const char* const cargoName)
{
  // TODO: Remove the magic 15.
  for (unsigned int i = 0; i < 15; ++i)
  {
    if (strcmp(cargoName, gameData.currentHarbor.goods[i].cargo.name) == 0)
    {
      return gameData.currentHarbor.goods[i];
    }
  }

  // TODO: Throw.
}

inline models::HarborCargo& GetCurrentHarborCargoByName(models::Game& gameData, const char* const cargoName)
{
  return const_cast<models::HarborCargo&>(
    GetCurrentHarborCargoByName(const_cast<const models::Game&>(gameData), cargoName));
}

inline const models::Cargo& GetCurrentShipCargoByName(const models::Game& gameData, const char* const cargoName)
{
  // TODO: Remove the magic 15.
  for (unsigned int i = 0; i < 15; ++i)
  {
    if (strcmp(cargoName, gameData.currentShip.goods[i].name) == 0)
    {
      return gameData.currentShip.goods[i];
    }
  }

  // TODO: Throw.
}

inline models::Cargo& GetCurrentShipCargoByName(models::Game& gameData, const char* const cargoName)
{
  return const_cast<models::Cargo&>(GetCurrentShipCargoByName(const_cast<const models::Game&>(gameData), cargoName));
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

#endif // LIBTURADOR_TURA_GAMEHELPERS_H_INCLUDED
