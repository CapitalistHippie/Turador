#ifndef LIBTURADOR_TURA_DOMAIN_COMMANDHANDLERS_STARTGAMECOMMANDHANDLER_HPP_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_COMMANDHANDLERS_STARTGAMECOMMANDHANDLER_HPP_INCLUDED

#include <system_error>

#include "tura/domain/commandmediator.hpp"
#include "tura/domain/commands/commandbase.h"
#include "tura/domain/commands/startgamecommand.h"
#include "tura/domain/constants.h"
#include "tura/domain/harborgenerator.hpp"
#include "tura/domain/harborgeneratorinterface.h"
#include "tura/domain/models/game.h"
#include "tura/domain/models/gamestate.h"
#include "tura/domain/models/harbor.h"
#include "tura/domain/shipgenerator.hpp"
#include "tura/domain/shipgeneratorinterface.h"
#include "tura/error.h"

namespace tura
{
namespace domain
{
namespace commandhandlers
{
class StartGameCommandHandler : public CommandHandlerBase<commands::CommandBase<commands::StartGameCommand>>
{
private:
  HarborGenerator harborGeneratorInstance;
  HarborGeneratorInterface* harborGenerator;

  ShipGenerator shipGeneratorInstance;
  ShipGeneratorInterface* shipGenerator;

public:
  StartGameCommandHandler()
    : harborGenerator(&harborGeneratorInstance)
    , shipGenerator(&shipGeneratorInstance)
  {
  }

  StartGameCommandHandler(HarborGeneratorInterface* harborGenerator, ShipGeneratorInterface* shipGenerator)
    : harborGenerator(harborGenerator)
    , shipGenerator(shipGenerator)
  {
  }

  void HandleCommand(const commands::CommandBase<commands::StartGameCommand>& command) const override
  {
    auto& gameData = command.gameData;

    // Check if the game hasn't already started.
    if (gameData.gameState != models::GameState::NotStarted)
    {
      throw std::system_error(std::make_error_code(Error::InsuitableState), "Game is already running.");
    }

    // Reset and set the initial data.
    models::Game freshGameData;
    gameData = std::move(freshGameData);
    gameData.gameState = Constants::GameInitialState;
    gameData.currentHarbor = harborGenerator->GenerateRandomHarbor();
    gameData.currentShip = shipGenerator->GenerateShipByShipTypeName("Pinnace");
    gameData.currentGold = Constants::GameInitialGold;
  }
};
}
}
}

#endif
