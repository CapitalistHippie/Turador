#ifndef LIBTURADOR_TURA_GAME_H_INCLUDED
#define LIBTURADOR_TURA_GAME_H_INCLUDED

#include "../commandmediator.hpp"
#include "commands/commandbase.h"
#include "gameconfiguration.h"
#include "harborfactoryinterface.h"
#include "models/game.h"
#include "models/gamestate.h"
#include "models/harborcargo.h"

namespace tura
{
class Game : private CommandMediator
{
private:
  HarborFactoryInterface* harborFactory;
  CommandMediator* commandMediator;
  GameConfiguration gameConfiguration;

  models::Game gameData;

public:
  Game(GameConfiguration gameConfiguration);

  void Start();

  template<typename Command>
  void HandleCommand(const Command& command)
  {
    commands::CommandBase<Command> commandHandlerCommand(command, gameData);

    commandMediator->HandleCommand(commandHandlerCommand);
  }

  const models::Game& GetGameData() const;
};
}

#endif // LIBTURADOR_TURA_GAME_H_INCLUDED
