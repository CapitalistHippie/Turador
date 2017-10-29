#ifndef LIBTURADOR_TURA_GAME_H_INCLUDED
#define LIBTURADOR_TURA_GAME_H_INCLUDED

#include "../commandhandler.hpp"
#include "commands/commandbase.h"
#include "gameconfiguration.h"
#include "harborfactoryinterface.h"
#include "models/game.h"
#include "models/gamestate.h"
#include "models/harborcargo.h"

namespace tura
{
class Game : private CommandHandler
{
private:
  HarborFactoryInterface* harborFactory;
  GameConfiguration gameConfiguration;

  models::Game gameData;

public:
  Game(GameConfiguration gameConfiguration);

  void Start();

  template<typename Command>
  void HandleCommand(const Command& command)
  {
    commands::CommandBase<Command> commandHandlerCommand(command, *this, gameData);

    CommandHandler::HandleCommand(commandHandlerCommand);
  }

  const models::Game& GetGameData() const;
  const models::HarborCargo& GetCurrentHarborCargoByName(const char* const cargoName) const;
};
}

#endif // LIBTURADOR_TURA_GAME_H_INCLUDED
