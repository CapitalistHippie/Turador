#ifndef LIBTURADOR_TURA_DOMAIN_MODELS_GAME_H_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_MODELS_GAME_H_INCLUDED

#include "tura/domain/models/gamestate.h"
#include "tura/domain/models/harbor.h"

#include "tura/domain/models/sailtrip.h"
#include "tura/domain/models/ship.h"
#include "tura/domain/states/state.h"

namespace tura
{
namespace domain
{
namespace models
{
struct Game
{
  GameState gameState = GameState::NotStarted;
  states::State* state = nullptr;

  Ship currentShip;

  unsigned int currentGold = 0;
};
}
}
}

#endif // LIBTURADOR_TURA_DOMAIN_MODELS_GAME_H_INCLUDED
