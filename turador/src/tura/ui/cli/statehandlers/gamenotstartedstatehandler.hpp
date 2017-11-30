#ifndef TURADOR_TURA_UI_CLI_STATEHANDLERS_GAMENOTSTARTEDSTATEHANDLER_HPP_INCLUDED
#define TURADOR_TURA_UI_CLI_STATEHANDLERS_GAMENOTSTARTEDSTATEHANDLER_HPP_INCLUDED

#include "tura/ui/cli/helpers.hpp"
#include "tura/ui/cli/statehandlers/basestatehandler.hpp"

namespace tura
{
namespace ui
{
namespace cli
{
namespace statehandlers
{
class GameNotStartedStateHandler : public BaseStateHandler
{
public:
  using BaseStateHandler::BaseStateHandler;

  void EnterState() override
  {
    RegisterCommand("start");
    RegisterCommandHandler("start", [&](const InputCommand& command) {
      gameClient.Start();

      auto state = GetCliUiStateFromGameState(gameClient.GetGameData().gameState);
      context.SetState(state);
    });
  }

  void ExitStateFromBase() noexcept override {}

  void RenderConsole() const override { outputStream << "Enter 'start' to start.\n"; }
};
}
}
}
}

#endif // TURADOR_TURA_UI_CLI_STATEHANDLERS_GAMENOTSTARTEDSTATEHANDLER_HPP_INCLUDED
