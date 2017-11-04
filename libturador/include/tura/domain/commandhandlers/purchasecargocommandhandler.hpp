#ifndef LIBTURADOR_TURA_DOMAIN_COMMANDS_PURCHASECARGOCOMMANDHANDLER_HPP_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_COMMANDS_PURCHASECARGOCOMMANDHANDLER_HPP_INCLUDED

#include <system_error>

#include "tura/dal/models/game.h"
#include "tura/dal/models/gamestate.h"
#include "tura/domain/commandmediator.hpp"
#include "tura/domain/commands/commandbase.h"
#include "tura/domain/commands/purchasecargocommand.h"
#include "tura/domain/gamehelpers.hpp"
#include "tura/error.h"

namespace tura
{
namespace domain
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
    if (gameData.gameState != dal::models::GameState::InHarbor)
    {
      throw std::system_error(std::make_error_code(Error::InsuitableState));
    }

    // Get the harbor cargo.
    auto& harborCargo = GetHarborCargoByName(gameData.currentHarbor, command.command.cargoName);

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
    GetShipCargoByName(gameData.currentShip, command.command.cargoName).amount += command.command.cargoAmount;
  }
};
}
}
}

#endif // LIBTURADOR_TURA_DOMAIN_COMMANDS_PURCHASECARGOCOMMANDHANDLER_HPP_INCLUDED
