#ifndef LIBTURADOR_TURA_DOMAIN_COMMANDS_SURRENDERCOMMANDHANDLER_HPP_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_COMMANDS_SURRENDERCOMMANDHANDLER_HPP_INCLUDED

#include <system_error>

#include "tura/domain/commands/commandbase.h"
#include "tura/domain/commands/surrendercommand.h"
#include "tura/domain/functionalerror.h"
#include "tura/domain/functionalerrorcategory.h"
#include "tura/domain/gamehelpers.hpp"
#include "tura/domain/models/game.h"
#include "tura/domain/models/gamestate.h"
#include "tura/domain/states/inbattlestate.h"
#include "tura/domain/states/sailingstate.h"
#include "tura/helpers/commandmediator.hpp"

namespace tura
{
namespace domain
{
namespace commandhandlers
{
class SurrenderCommandHandler : public helpers::CommandHandlerBase<commands::CommandBase<commands::SurrenderCommand>>
{
public:
  void HandleCommand(const commands::CommandBase<commands::SurrenderCommand>& command) const override
  {
    auto& gameData = command.gameData;
    auto& ship = gameData.currentShip;

    // Check if we're in the right state.
    if (gameData.gameState != models::GameState::InBattle)
    {
      throw std::system_error(std::make_error_code(FunctionalError::InsuitableState));
    }

    auto* state = static_cast<states::InBattleState*>(gameData.state);
    auto& enemyShip = state->enemyShip;

    auto enemyShipCargoSpaceLeft = enemyShip.shipType.cargoSpaceMax;

    for (auto& cargo : ship.goods)
    {
      if (cargo.amount >= enemyShipCargoSpaceLeft)
      {
        cargo.amount -= enemyShipCargoSpaceLeft;
        break;
      }
      else
      {
        enemyShipCargoSpaceLeft -= cargo.amount;
        cargo.amount = 0;
      }
    }

    auto trip = std::move(state->trip);

    SetGameState(gameData, models::GameState::Sailing);
    auto* sailingState = static_cast<states::SailingState*>(gameData.state);

    sailingState->trip = std::move(trip);
  }
};
}
}
}

#endif // LIBTURADOR_TURA_DOMAIN_COMMANDS_SURRENDERCOMMANDHANDLER_HPP_INCLUDED
