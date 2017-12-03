#ifndef TURADOR_TURA_UI_CLI_STATEHANDLERS_SAILINGSTATEHANDLER_HPP_INCLUDED
#define TURADOR_TURA_UI_CLI_STATEHANDLERS_SAILINGSTATEHANDLER_HPP_INCLUDED

#include <functional>

#include <tura/domain/models/gamestate.h>
#include <tura/domain/models/sailroute.h>
#include <tura/domain/models/sailtrip.h>

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
    const auto& trip = gameData.currentSailTrip;

    outputStream << "You are sailing from " << trip.route.fromHarborName << " to " << trip.route.toHarborName << ".\n";

    auto turnsToGo = trip.route.distanceInTurns - trip.turnsSailed;

    outputStream << "You have " << turnsToGo << " turns to go until you arrive.\n";

    outputStream << '\n';

    outputStream << "The following commands are available:\n"
                 << "sail - Sail for a turn.\n";
  }
};
}
}
}
}

#endif // TURADOR_TURA_UI_CLI_STATEHANDLERS_SAILINGSTATEHANDLER_HPP_INCLUDED
