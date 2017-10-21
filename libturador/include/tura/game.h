#ifndef LIBTURADOR_TURA_GAME_H_INCLUDED
#define LIBTURADOR_TURA_GAME_H_INCLUDED

#include "gameconfiguration.h"
#include "models/gamestate.h"

namespace tura
{
class Game
{
private:
  GameConfiguration gameConfiguration;

  models::GameState gameState;

public:
  Game(GameConfiguration gameConfiguration)
    : gameConfiguration(gameConfiguration)
    , gameState(models::GameState::NotStarted)
  {
  }

  void Start();

  models::GameState GetState() const;
};
}

#endif // LIBTURADOR_TURA_GAME_H_INCLUDED
