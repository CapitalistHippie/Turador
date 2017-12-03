#ifndef TURADOR_TURA_UI_CLI_STATEHANDLERS_GAMEOVERSTATEHANDLER_HPP_INCLUDED
#define TURADOR_TURA_UI_CLI_STATEHANDLERS_GAMEOVERSTATEHANDLER_HPP_INCLUDED

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
class GameOverStateHandler : public BaseStateHandler
{
public:
  using BaseStateHandler::BaseStateHandler;

  void EnterState() override {}

  void ExitStateFromBase() noexcept override {}

  void RenderConsole() const override
  {
    auto gameState = gameClient.GetGameData().gameState;
    if (gameState == domain::models::GameState::Won)
    {
      outputStream << "You won! Congratulations!\n";
    }
    else if (gameState == domain::models::GameState::Lost)
    {
      outputStream << "You lost.\n";
    }
  }
};
}
}
}
}

#endif // TURADOR_TURA_UI_CLI_STATEHANDLERS_GAMEOVERSTATEHANDLER_HPP_INCLUDED
