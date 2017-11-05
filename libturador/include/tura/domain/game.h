#ifndef LIBTURADOR_TURA_DOMAIN_GAME_H_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_GAME_H_INCLUDED

#include "tura/domain/commandmediator.hpp"
#include "tura/domain/commands/commandbase.h"
#include "tura/domain/models/game.h"

namespace tura
{
namespace domain
{
class Game
{
private:
  CommandMediator commandMediatorInstance;
  CommandMediator* commandMediator;

  models::Game gameData;

  void RegisterCommandHandlers();

public:
  Game();
  Game(CommandMediator* commandMediator);

  template<typename Command>
  void HandleCommand(const Command& command)
  {
    commands::CommandBase<Command> commandHandlerCommand(command, gameData);

    commandMediator->HandleCommand(commandHandlerCommand);
  }

  const models::Game& GetGameData() const;
};
}
}

#endif // LIBTURADOR_TURA_DOMAIN_GAME_H_INCLUDED
