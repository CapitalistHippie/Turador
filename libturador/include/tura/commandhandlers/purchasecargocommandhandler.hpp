#ifndef LIBTURADOR_TURA_COMMANDS_PURCHASECARGOCOMMANDHANDLER_HPP_INCLUDED
#define LIBTURADOR_TURA_COMMANDS_PURCHASECARGOCOMMANDHANDLER_HPP_INCLUDED

#include <system_error>

#include "../../commandmediator.hpp"
#include "../commands/commandbase.h"
#include "../commands/purchasecargocommand.h"
#include "../error.h"
#include "../gamehelpers.hpp"
#include "../models/game.h"
#include "../models/gamestate.h"

namespace tura
{
namespace commandhandlers
{
class PurchaseCargoCommandHandler : public CommandHandlerBase<commands::CommandBase<commands::PurchaseCargoCommand>>
{
public:
  void HandleCommand(const commands::CommandBase<commands::PurchaseCargoCommand>& command) const override
  {
    auto& gameData = command.gameData;

    // Check if we're in the right state.
    if (gameData.gameState != models::GameState::InHarbor)
    {
      throw std::system_error(std::make_error_code(Error::InsuitableState));
    }

    // Get the harbor cargo.
    auto& harborCargo = GetCurrentHarborCargoByName(gameData, command.command.cargoName);

    // Check if the harbor has enough of the cargo that we want to purchase.
    if (harborCargo.cargo.amount < command.command.cargoAmount)
    {
      throw std::system_error(std::make_error_code(Error::InsufficientCargoInHarbor));
    }

    // Check if the ship has enough cargo space to hold the cargo.
    if (command.command.cargoAmount + GetShipUsedCargoSpace(gameData.currentShip) >
        gameData.currentShip.shipType.cargoSpaceMax)
    {
      throw std::system_error(std::make_error_code(Error::InsufficientShipCargoSpace));
    }

    // Calculate the total gold we need to spend.
    auto totalGoldToSpend = harborCargo.price * command.command.cargoAmount;

    // Check if we got enough money.
    if (gameData.currentGold < totalGoldToSpend)
    {
      throw std::system_error(std::make_error_code(Error::InsufficientGold));
    }

    // We good. Let's do this.
    gameData.currentGold -= totalGoldToSpend;
    harborCargo.cargo.amount -= command.command.cargoAmount;
    GetCurrentShipCargoByName(gameData, command.command.cargoName).amount += command.command.cargoAmount;
  }
};
}
}

#endif // LIBTURADOR_TURA_COMMANDS_PURCHASECARGOCOMMANDHANDLER_HPP_INCLUDED
