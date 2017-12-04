#ifndef TURADOR_TURA_UI_CLI_STATEHANDLERS_MAPSTATEHANDLER_HPP_INCLUDED
#define TURADOR_TURA_UI_CLI_STATEHANDLERS_MAPSTATEHANDLER_HPP_INCLUDED

#include <functional>

#include <tura/domain/states/inharborstate.h>

#include "tura/ui/cli/cliui.h"
#include "tura/ui/cli/statehandlers/basestatehandler.hpp"

namespace tura
{
namespace ui
{
namespace cli
{
namespace statehandlers
{
class MapStateHandler : public BaseStateHandler
{
private:
  void SailCommandHandler(const InputCommand& inputCommand)
  {
    auto harborName = inputCommand.GetParameter<helpers::CharArray<64>>(0);

    gameClient.StartSailing(harborName);

    context.SetState(CliUiState::Sailing);
  }

public:
  using BaseStateHandler::BaseStateHandler;

  void EnterState() override
  {
    RegisterCommand("back");
    RegisterCommandHandler("back", [&](const InputCommand& command) { context.SetState(CliUiState::InHarbor); });

    RegisterCommand<helpers::CharArray<64>>("sail");
    RegisterCommandHandler("sail", std::bind(&MapStateHandler::SailCommandHandler, this, std::placeholders::_1));
  }

  void ExitStateFromBase() noexcept override {}

  void RenderConsole() const override
  {
    const auto& gameData = gameClient.GetGameData();

    auto* state = static_cast<domain::states::InHarborState*>(gameData.state);
    auto& harbor = state->harbor;

    outputStream << "Welcome to the map. You can sail to the following harbors:\n"
                 << "(Harbor name - Distance in turns)\n";

    for (const auto& sailRoute : harbor.sailRoutes)
    {
      outputStream << sailRoute.toHarborName << " - " << sailRoute.distanceInTurns << '\n';
    }

    outputStream << '\n';

    outputStream << "The following commands are available:\n"
                 << "back - Go back to the harbor screen.\n"
                 << "sail <harbor name> - Sail to a harbor.\n";
  }
};
}
}
}
}

#endif // TURADOR_TURA_UI_CLI_STATEHANDLERS_MAPSTATEHANDLER_HPP_INCLUDED
