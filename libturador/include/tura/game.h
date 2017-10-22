#ifndef LIBTURADOR_TURA_GAME_H_INCLUDED
#define LIBTURADOR_TURA_GAME_H_INCLUDED

#include "../commandhandler.hpp"
#include "gameconfiguration.h"
#include "models/gamestate.h"

namespace tura
{
class Game : public CommandHandler
{
private:
  GameConfiguration gameConfiguration;

  models::GameState gameState;

public:
  Game(GameConfiguration gameConfiguration);

  void Start();

  models::GameState GetState() const;
};
}

#endif // LIBTURADOR_TURA_GAME_H_INCLUDED
