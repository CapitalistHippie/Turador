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
    const auto& gameData = gameClient.GetGameData();
    auto gameState = gameData.gameState;

    if (gameState == domain::models::GameState::Won)
    {
      outputStream << "You won! Congratulations!\n";
    }
    else if (gameState == domain::models::GameState::Lost)
    {
      auto lostReason = static_cast<domain::states::LostState*>(gameData.state)->lostReason;

      outputStream << "You lost. ";

      if (lostReason == domain::models::LostReason::SunkInStorm)
      {
        outputStream << "You were sunk in a storm.\n";
      }
      else if (lostReason == domain::models::LostReason::SunkByPirates)
      {
        outputStream << "You were sunk by pirates.\n";
      }
    }
  }
};
}
}
}
}

#endif // TURADOR_TURA_UI_CLI_STATEHANDLERS_GAMEOVERSTATEHANDLER_HPP_INCLUDED
