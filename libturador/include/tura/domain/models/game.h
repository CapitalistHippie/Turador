#ifndef LIBTURADOR_TURA_DOMAIN_MODELS_GAME_H_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_MODELS_GAME_H_INCLUDED

#include "tura/domain/models/gamestate.h"
#include "tura/domain/models/harbor.h"
#include "tura/domain/models/sailtrip.h"
#include "tura/domain/models/ship.h"

namespace tura
{
namespace domain
{
namespace models
{
struct Game
{
  models::GameState gameState = GameState::NotStarted;

  models::Harbor currentHarbor;
  models::Ship currentShip;
  models::SailTrip currentSailTrip;

  unsigned int currentGold = 0;
};
}
}
}

#endif // LIBTURADOR_TURA_DOMAIN_MODELS_GAME_H_INCLUDED
