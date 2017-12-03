#ifndef LIBTURADOR_TURA_DOMAIN_COMMANDS_PURCHASESHIPCOMMANDHANDLER_HPP_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_COMMANDS_PURCHASESHIPCOMMANDHANDLER_HPP_INCLUDED

#include <algorithm>
#include <system_error>

#include "tura/domain/commands/commandbase.h"
#include "tura/domain/commands/purchaseshipcommand.h"
#include "tura/domain/functionalerror.h"
#include "tura/domain/functionalerrorcategory.h"
#include "tura/domain/gamehelpers.hpp"
#include "tura/domain/models/game.h"
#include "tura/domain/models/gamestate.h"
#include "tura/domain/shipgenerator.hpp"
#include "tura/domain/shipgeneratorinterface.h"
#include "tura/helpers/commandmediator.hpp"

namespace tura
{
namespace domain
{
namespace commandhandlers
{
class PurchaseShipCommandHandler
  : public helpers::CommandHandlerBase<commands::CommandBase<commands::PurchaseShipCommand>>
{
private:
  ShipGenerator shipGeneratorInstance;
  ShipGeneratorInterface* shipGenerator;

public:
  PurchaseShipCommandHandler()
    : shipGenerator(&shipGeneratorInstance)
  {
  }

  PurchaseShipCommandHandler(ShipGeneratorInterface* shipGenerator)
    : shipGenerator(shipGenerator)
  {
  }

  void HandleCommand(const commands::CommandBase<commands::PurchaseShipCommand>& command) const override
  {
    auto& gameData = command.gameData;
    auto& harbor = gameData.currentHarbor;
    auto& ship = gameData.currentShip;

    // Check if we're in the right state.
    if (gameData.gameState != models::GameState::InHarbor)
    {
      throw std::system_error(std::make_error_code(FunctionalError::InsuitableState));
    }

    // Get the type of the ship the player is purchasing.
    auto shipTypeToPurchase =
      std::find_if(harbor.shipsForSale.begin(), harbor.shipsForSale.end(), [&](const models::ShipType& shipType) {
        return shipType.name == command.command.shipType;
      });
    if (shipTypeToPurchase == harbor.shipsForSale.end())
    {
      throw std::system_error(std::make_error_code(FunctionalError::ShipNotForSaleInHarbor),
                              "This ship is not for sale in this harbor.");
    }

    // Calculate the total amount of gold we need to spend.
    auto totalGoldToSpend = shipTypeToPurchase->price - (ship.shipType.price / 2);

    // Check if the player has enough gold.
    if (gameData.currentGold < totalGoldToSpend)
    {
      throw std::system_error(std::make_error_code(FunctionalError::InsufficientGold), "Not enough gold.");
    }

    // Let's do it.
    auto oldShip = std::move(ship);
    auto newShip = shipGenerator->GenerateShipByShipType(*shipTypeToPurchase);
    newShip.cannons = std::move(oldShip.cannons);
    newShip.goods = std::move(oldShip.goods);
    gameData.currentShip = std::move(newShip);

    gameData.currentGold -= totalGoldToSpend;
  }
};
}
}
}

#endif // #ifndef LIBTURADOR_TURA_DOMAIN_COMMANDS_PURCHASESHIPCOMMANDHANDLER_HPP_INCLUDED
