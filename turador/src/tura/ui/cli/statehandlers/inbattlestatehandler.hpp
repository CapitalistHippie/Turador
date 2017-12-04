#ifndef TURADOR_TURA_UI_CLI_STATEHANDLERS_INBATTLESTATEHANDLER_HPP_INCLUDED
#define TURADOR_TURA_UI_CLI_STATEHANDLERS_INBATTLESTATEHANDLER_HPP_INCLUDED

#include <functional>

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
class InBattleStateHandler : public BaseStateHandler
{
private:
  void FireCommandHandler(const InputCommand& inputCommand)
  {
    gameClient.Fire();
    CheckState();
  }

  void RunCommandHandler(const InputCommand& inputCommand)
  {
    gameClient.Run();
    CheckState();
  }

  void SurrenderCommandHandler(const InputCommand& inputCommand)
  {
    gameClient.Surrender();
    CheckState();
  }

  void CheckState()
  {
    if (gameClient.GetGameData().gameState == domain::models::GameState::Sailing)
    {
      context.SetState(CliUiState::Sailing);
    }
  }

public:
  using BaseStateHandler::BaseStateHandler;

  void EnterState() override
  {
    RegisterCommand("fire");
    RegisterCommandHandler("fire", std::bind(&InBattleStateHandler::FireCommandHandler, this, std::placeholders::_1));

    RegisterCommand("run");
    RegisterCommandHandler("run", std::bind(&InBattleStateHandler::RunCommandHandler, this, std::placeholders::_1));

    RegisterCommand("surrender");
    RegisterCommandHandler("surrender",
                           std::bind(&InBattleStateHandler::SurrenderCommandHandler, this, std::placeholders::_1));
  }

  void ExitStateFromBase() noexcept override {}

  void RenderConsole() const override
  {
    const auto& gameData = gameClient.GetGameData();
    const auto& ship = gameData.currentShip;
    const auto& enemyShip = gameData.currentEnemyShip;

    outputStream << "You encounterd a pirate ship and are engaged in battle!\n";
    outputStream << "Your ship has " << ship.hitPoints << " out of " << ship.shipType.hitPointsMax << " hit points.\n";
    outputStream << "The pirate ship has " << enemyShip.hitPoints << " out of " << enemyShip.shipType.hitPointsMax
                 << " hit points.\n";

    outputStream << '\n';

    outputStream << "The following commands are available:\n"
                 << "fire - Fire at the pirates.\n"
                 << "run - Try to run. The pirates will fire on your ship while you're running.\n"
                 << "surrender - Surrender to the pirates.\n";
  }
};
}
}
}
}

#endif // TURADOR_TURA_UI_CLI_STATEHANDLERS_INBATTLESTATEHANDLER_HPP_INCLUDED
