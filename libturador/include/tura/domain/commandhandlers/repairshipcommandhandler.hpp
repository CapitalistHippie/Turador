#ifndef LIBTURADOR_TURA_DOMAIN_COMMANDS_REPAIRSHIPCOMMANDHANDLER_HPP_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_COMMANDS_REPAIRSHIPCOMMANDHANDLER_HPP_INCLUDED

#include <system_error>

#include "tura/domain/commands/commandbase.h"
#include "tura/domain/commands/repairshipcommand.h"
#include "tura/domain/functionalerror.h"
#include "tura/domain/functionalerrorcategory.h"
#include "tura/domain/gamehelpers.hpp"
#include "tura/domain/models/game.h"
#include "tura/domain/models/gamestate.h"
#include "tura/helpers/commandmediator.hpp"

namespace tura
{
namespace domain
{
namespace commandhandlers
{
class RepairShipCommandHandler : public helpers::CommandHandlerBase<commands::CommandBase<commands::RepairShipCommand>>
{
public:
  void HandleCommand(const commands::CommandBase<commands::RepairShipCommand>& command) const override
  {
    auto& gameData = command.gameData;

    // Check if we're in the right state.
    if (gameData.gameState != models::GameState::InHarbor)
    {
      throw std::system_error(std::make_error_code(FunctionalError::InsuitableState));
    }

    // Calculate the total gold we need to spend and the hit points to repair.
    auto maxHitPointsToRepair = gameData.currentShip.shipType.hitPointsMax - gameData.currentShip.hitPoints;
    auto hitPointsToRepair = command.command.amount * 10;
    unsigned int totalGoldToSpend = 0;
    if (hitPointsToRepair < maxHitPointsToRepair)
    {
      totalGoldToSpend = command.command.amount;
    }
    else
    {
      totalGoldToSpend = maxHitPointsToRepair / 10;
      if (maxHitPointsToRepair % 10 > 0)
      {
        totalGoldToSpend++;
      }

      hitPointsToRepair = maxHitPointsToRepair;
    }

    // Check if we got enough money.
    if (gameData.currentGold < totalGoldToSpend)
    {
      throw std::system_error(std::make_error_code(FunctionalError::InsufficientGold), "Not enough gold.");
    }

    // We got this.
    gameData.currentShip.hitPoints += hitPointsToRepair;
    gameData.currentGold -= totalGoldToSpend;
  }
};
}
}
}

#endif // LIBTURADOR_TURA_DOMAIN_COMMANDS_REPAIRSHIPCOMMANDHANDLER_HPP_INCLUDED
