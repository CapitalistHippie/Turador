#ifndef LIBTURADOR_TURA_MODELS_GAME_H_INCLUDED
#define LIBTURADOR_TURA_MODELS_GAME_H_INCLUDED

#include "gamestate.h"
#include "harbor.h"
#include "ship.h"

namespace tura
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

#endif // LIBTURADOR_TURA_MODELS_GAME_H_INCLUDED
