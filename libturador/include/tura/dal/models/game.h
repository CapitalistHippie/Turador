#ifndef LIBTURADOR_TURA_DAL_MODELS_GAME_H_INCLUDED
#define LIBTURADOR_TURA_DAL_MODELS_GAME_H_INCLUDED

#include "tura/dal/models/gamestate.h"
#include "tura/dal/models/harbor.h"
#include "tura/dal/models/ship.h"

namespace tura
{
namespace dal
{
namespace models
{
struct Game
{
  models::GameState gameState = GameState::NotStarted;

  models::Harbor currentHarbor;
  models::Ship currentShip;

  unsigned int currentGold = 0;
};
}
}
}

#endif // LIBTURADOR_TURA_DAL_MODELS_GAME_H_INCLUDED
