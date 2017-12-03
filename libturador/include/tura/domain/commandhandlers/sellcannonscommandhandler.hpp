#ifndef LIBTURADOR_TURA_DOMAIN_COMMANDS_SELLCANNONSCOMMANDHANDLER_HPP_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_COMMANDS_SELLCANNONSCOMMANDHANDLER_HPP_INCLUDED

#include <system_error>

#include "tura/domain/commands/commandbase.h"
#include "tura/domain/commands/sellcannonscommand.h"
#include "tura/domain/constants.h"
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
class SellCannonsCommandHandler
  : public helpers::CommandHandlerBase<commands::CommandBase<commands::SellCannonsCommand>>
{
private:
  unsigned int GetCannonCountWithClass(const helpers::Array<domain::models::Cannon, 32>& cannons,
                                       domain::models::CannonClass cannonClass) const
  {
    return std::count_if(
      cannons.begin(), cannons.end(), [=](const models::Cannon& cannon) { return cannon.cannonClass == cannonClass; });
  }

public:
  void HandleCommand(const commands::CommandBase<commands::SellCannonsCommand>& command) const override
  {
    auto& gameData = command.gameData;
    auto& harbor = gameData.currentHarbor;
    auto& ship = gameData.currentShip;

    // Check if we're in the right state.
    if (gameData.gameState != models::GameState::InHarbor)
    {
      throw std::system_error(std::make_error_code(FunctionalError::InsuitableState));
    }

    // Check if the ship has enough of the type of cannons to sell.
    if (GetCannonCountWithClass(ship.cannons, command.command.cannonClass) < command.command.amount)
    {
      throw std::system_error(std::make_error_code(FunctionalError::InsufficientCannonsInShip),
                              "Not enough of those type of cannons on your ship to sell.");
    }

    // Calculate the total the player will receive.
    unsigned int cannonPrice = 0;
    switch (command.command.cannonClass)
    {
      case models::CannonClass::Light:
        cannonPrice = Constants::LightCannonPrice / 2;
        break;
      case models::CannonClass::Medium:
        cannonPrice = Constants::MediumCannonPrice / 2;
        break;
      case models::CannonClass::Heavy:
        cannonPrice = Constants::HeavyCannonPrice / 2;
        break;
    }
    auto totalGoldToReceive = command.command.amount * cannonPrice;

    // Let's do this.
    models::Cannon cannon;
    cannon.cannonClass = command.command.cannonClass;
    for (unsigned int i = 0; i < command.command.amount; ++i)
    {
      for (unsigned int ii = 0; ii < ship.cannons.size(); ++ii)
      {
        if (ship.cannons[ii].cannonClass == command.command.cannonClass)
        {
          ship.cannons.Remove(ii);
          break;
        }
      }

      harbor.cannonsForSale.Add(cannon);
    }
    gameData.currentGold += totalGoldToReceive;
  }
};
}
}
}

#endif // LIBTURADOR_TURA_DOMAIN_COMMANDS_SELLCANNONSCOMMANDHANDLER_HPP_INCLUDED
