#ifndef LIBTURADOR_TURA_GAMEHELPERS_H_INCLUDED
#define LIBTURADOR_TURA_GAMEHELPERS_H_INCLUDED

#include <cstring>

#include "models/game.h"
#include "models/harborcargo.h"

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
}

#endif // LIBTURADOR_TURA_GAMEHELPERS_H_INCLUDED
