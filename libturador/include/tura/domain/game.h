#ifndef LIBTURADOR_TURA_DOMAIN_GAME_H_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_GAME_H_INCLUDED

#include "tura/domain/commands/commandbase.h"
#include "tura/domain/models/game.h"
#include "tura/helpers/commandmediator.hpp"

namespace tura
{
namespace domain
{
class Game
{
private:
  helpers::CommandMediator commandMediatorInstance;
  helpers::CommandMediator* commandMediator;

  models::Game gameData;

  void RegisterCommandHandlers();

public:
  Game();
  Game(helpers::CommandMediator* commandMediator);

  template<typename Command>
  void HandleCommand(const Command& command)
  {
    commands::CommandBase<Command> commandHandlerCommand(command, gameData);

    commandMediator->HandleCommand(commandHandlerCommand);

    // Check if the player reached 1.000.000 gold or if the ship has 0 hitpoints. Those are the winning and losing
    // conditions respectfully.
    if (gameData.currentGold >= 1000000)
    {
      gameData.gameState = models::GameState::Won;
    }
    else if (gameData.currentShip.hitPoints <= 0)
    {
      gameData.gameState = models::GameState::Lost;
    }
  }

  const models::Game& GetGameData() const;
};
}
}

#endif // LIBTURADOR_TURA_DOMAIN_GAME_H_INCLUDED
