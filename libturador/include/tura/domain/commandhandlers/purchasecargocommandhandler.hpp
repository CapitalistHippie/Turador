#ifndef LIBTURADOR_TURA_DOMAIN_COMMANDS_PURCHASECARGOCOMMANDHANDLER_HPP_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_COMMANDS_PURCHASECARGOCOMMANDHANDLER_HPP_INCLUDED

#include <algorithm>
#include <system_error>

#include "tura/domain/commands/commandbase.h"
#include "tura/domain/commands/purchasecargocommand.h"
#include "tura/domain/functionalerror.h"
#include "tura/domain/functionalerrorcategory.h"
#include "tura/domain/gamehelpers.hpp"
#include "tura/domain/models/game.h"
#include "tura/domain/models/gamestate.h"
#include "tura/domain/states/inharborstate.h"
#include "tura/helpers/commandmediator.hpp"

namespace tura
{
namespace domain
{
namespace commandhandlers
{
class PurchaseCargoCommandHandler
  : public helpers::CommandHandlerBase<commands::CommandBase<commands::PurchaseCargoCommand>>
{
public:
  void HandleCommand(const commands::CommandBase<commands::PurchaseCargoCommand>& command) const override
  {
    auto& gameData = command.gameData;
    auto& ship = gameData.currentShip;

    // Check if we're in the right state.
    if (gameData.gameState != models::GameState::InHarbor)
    {
      throw std::system_error(std::make_error_code(FunctionalError::InsuitableState));
    }

    auto* state = static_cast<states::InHarborState*>(gameData.state);
    auto& harbor = state->harbor;

    // Get the harbor cargo.
    auto harborCargo = std::find_if(harbor.goods.begin(), harbor.goods.end(), [&](const models::HarborCargo& cargo) {
      return cargo.cargo.name == command.command.cargoName.array;
    });
    if (harborCargo == harbor.goods.end())
    {
      throw std::system_error(std::make_error_code(FunctionalError::UnknownCargo), "Unknown cargo type.");
    }

    // Check if the harbor has enough of the cargo that we want to purchase.
    if (harborCargo->cargo.amount < command.command.cargoAmount)
    {
      throw std::system_error(std::make_error_code(FunctionalError::InsufficientCargoInHarbor),
                              "Not enough of that type of cargo in the harbor.");
    }

    // Check if the ship has enough cargo space to hold the cargo.
    if (command.command.cargoAmount + GetShipUsedCargoSpace(gameData.currentShip) >
        gameData.currentShip.shipType.cargoSpaceMax)
    {
      throw std::system_error(std::make_error_code(FunctionalError::InsufficientShipCargoSpace),
                              "You don't have enough cargo space in your ship.");
    }

    // Calculate the total amount of gold we need to spend.
    auto totalGoldToSpend = harborCargo->price * command.command.cargoAmount;

    // Check if the player has enough gold.
    if (gameData.currentGold < totalGoldToSpend)
    {
      throw std::system_error(std::make_error_code(FunctionalError::InsufficientGold), "Not enough gold.");
    }

    // Get the ship cargo.
    auto shipCargo = std::find_if(ship.goods.begin(), ship.goods.end(), [&](const models::Cargo& cargo) {
      return cargo.name == command.command.cargoName.array;
    });

    // If the ship doesn't have the cargo, add it.
    if (shipCargo == ship.goods.end())
    {
      models::Cargo newShipCargo;
      newShipCargo.name = command.command.cargoName;

      shipCargo = ship.goods.end();
      ship.goods.Add(newShipCargo);
    }

    // We good. Let's do this.
    gameData.currentGold -= totalGoldToSpend;
    harborCargo->cargo.amount -= command.command.cargoAmount;
    shipCargo->amount += command.command.cargoAmount;
  }
};
}
}
}

#endif // LIBTURADOR_TURA_DOMAIN_COMMANDS_PURCHASECARGOCOMMANDHANDLER_HPP_INCLUDED
