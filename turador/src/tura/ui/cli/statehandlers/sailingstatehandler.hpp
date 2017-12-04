#ifndef TURADOR_TURA_UI_CLI_STATEHANDLERS_SAILINGSTATEHANDLER_HPP_INCLUDED
#define TURADOR_TURA_UI_CLI_STATEHANDLERS_SAILINGSTATEHANDLER_HPP_INCLUDED

#include <functional>

#include <tura/domain/models/gamestate.h>
#include <tura/domain/models/sailroute.h>
#include <tura/domain/models/sailtrip.h>
#include <tura/domain/states/sailingstate.h>

#include "tura/ui/cli/statehandlers/basestatehandler.hpp"

namespace tura
{
namespace ui
{
namespace cli
{
namespace statehandlers
{
class SailingStateHandler : public BaseStateHandler
{
private:
  void SailCommandHandler(const InputCommand& inputCommand)
  {
    gameClient.Sail();

    if (gameClient.GetGameData().gameState == domain::models::GameState::InHarbor)
    {
      context.SetState(CliUiState::InHarbor);
    }
    else if (gameClient.GetGameData().gameState == domain::models::GameState::InBattle)
    {
      context.SetState(CliUiState::InBattle);
    }
  }

public:
  using BaseStateHandler::BaseStateHandler;

  void EnterState() override
  {
    RegisterCommand("sail");
    RegisterCommandHandler("sail", std::bind(&SailingStateHandler::SailCommandHandler, this, std::placeholders::_1));
  }

  void ExitStateFromBase() noexcept override {}

  void RenderConsole() const override
  {
    const auto& gameData = gameClient.GetGameData();
    const auto& ship = gameData.currentShip;
    auto* state = static_cast<domain::states::SailingState*>(gameData.state);
    const auto& trip = state->trip;

    outputStream << "You are sailing from " << trip.route.fromHarborName << " to " << trip.route.toHarborName << ".\n";

    auto turnsToGo = trip.route.distanceInTurns - trip.turnsSailed;

    outputStream << "You have " << turnsToGo << " turns to go until you arrive.\n";
    outputStream << "Your ship has " << ship.hitPoints << " out of " << ship.shipType.hitPointsMax << " hit points.\n";

    outputStream << '\n';

    outputStream << "The following commands are available:\n"
                 << "sail - Sail for a turn.\n";

    switch (trip.lastWindStrength)
    {
      case domain::models::WindStrength::None:
        outputStream << "There was no wind.\n";
        break;
      case domain::models::WindStrength::Breeze:
        outputStream << "There was breeze.\n";
        break;
      case domain::models::WindStrength::Weak:
        outputStream << "There was a weak wind.\n";
        break;
      case domain::models::WindStrength::Normal:
        outputStream << "There was a normal wind.\n";
        break;
      case domain::models::WindStrength::Strong:
        outputStream << "There was a strong wind.\n";
        break;
      case domain::models::WindStrength::Storm:
        outputStream << "You sailed into a storm. Your ship took damage.\n";
    }
  }
};
}
}
}
}

#endif // TURADOR_TURA_UI_CLI_STATEHANDLERS_SAILINGSTATEHANDLER_HPP_INCLUDED
