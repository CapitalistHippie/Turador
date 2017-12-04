#ifndef LIBTURADOR_TURA_DOMAIN_COMMANDS_PURCHASECANNONSCOMMANDHANDLER_HPP_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_COMMANDS_PURCHASECANNONSCOMMANDHANDLER_HPP_INCLUDED

#include <system_error>

#include "tura/domain/commands/commandbase.h"
#include "tura/domain/commands/purchasecannonscommand.h"
#include "tura/domain/constants.h"
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
class PurchaseCannonsCommandHandler
  : public helpers::CommandHandlerBase<commands::CommandBase<commands::PurchaseCannonsCommand>>
{
private:
  unsigned int GetCannonCountWithClass(const helpers::Array<domain::models::Cannon, 64>& cannons,
                                       domain::models::CannonClass cannonClass) const
  {
    return std::count_if(
      cannons.begin(), cannons.end(), [=](const models::Cannon& cannon) { return cannon.cannonClass == cannonClass; });
  }

public:
  void HandleCommand(const commands::CommandBase<commands::PurchaseCannonsCommand>& command) const override
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

    // Small ships can't have heavy cannons.
    if (ship.shipType.sizeClass == models::ShipSizeClass::Small &&
        command.command.cannonClass == models::CannonClass::Heavy)
    {
      throw std::system_error(std::make_error_code(FunctionalError::InsuitableShipType),
                              "Small ships can't have large cannons.");
    }

    // Check if we the ship already has the maximum amount of cannons.
    unsigned int cannonCountAfterPurchase = ship.cannons.size() + command.command.amount;
    if (cannonCountAfterPurchase > ship.shipType.cannonSpaceMax)
    {
      throw std::system_error(std::make_error_code(FunctionalError::ShipCannonLimitReached),
                              "Ship already has the maximum amount of cannons.");
    }

    // Check if the harbor has enough of the type of cannons to sell.
    if (GetCannonCountWithClass(harbor.cannonsForSale, command.command.cannonClass) < command.command.amount)
    {
      throw std::system_error(std::make_error_code(FunctionalError::InsufficientCannonsForSaleInHarbor),
                              "Not enough of those type of cannons for sale in the harbor.");
    }

    // Calculate the total gold to spend.
    unsigned int cannonPrice = 0;
    switch (command.command.cannonClass)
    {
      case models::CannonClass::Light:
        cannonPrice = Constants::LightCannonPrice;
        break;
      case models::CannonClass::Medium:
        cannonPrice = Constants::MediumCannonPrice;
        break;
      case models::CannonClass::Heavy:
        cannonPrice = Constants::HeavyCannonPrice;
        break;
    }
    auto totalGoldToSpend = command.command.amount * cannonPrice;

    // Check if the player has enough gold.
    if (gameData.currentGold < totalGoldToSpend)
    {
      throw std::system_error(std::make_error_code(FunctionalError::InsufficientGold), "Not enough gold.");
    }

    // Let's do this.
    models::Cannon cannon;
    cannon.cannonClass = command.command.cannonClass;
    for (unsigned int i = 0; i < command.command.amount; ++i)
    {
      for (unsigned int ii = 0; ii < harbor.cannonsForSale.size(); ++ii)
      {
        if (harbor.cannonsForSale[ii].cannonClass == command.command.cannonClass)
        {
          harbor.cannonsForSale.Remove(ii);
          break;
        }
      }

      ship.cannons.Add(cannon);
    }
    gameData.currentGold -= totalGoldToSpend;
  }
};
}
}
}

#endif // LIBTURADOR_TURA_DOMAIN_COMMANDS_PURCHASECANNONSCOMMANDHANDLER_HPP_INCLUDED
