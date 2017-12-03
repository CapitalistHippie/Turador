#ifndef LIBTURADOR_TURA_DOMAIN_COMMANDS_SELLCARGOCOMMANDHANDLER_HPP_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_COMMANDS_SELLCARGOCOMMANDHANDLER_HPP_INCLUDED

#include <system_error>

#include "tura/domain/commands/commandbase.h"
#include "tura/domain/commands/sellcargocommand.h"
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
class SellCargoCommandHandler : public helpers::CommandHandlerBase<commands::CommandBase<commands::SellCargoCommand>>
{
public:
  void HandleCommand(const commands::CommandBase<commands::SellCargoCommand>& command) const override
  {
    auto& gameData = command.gameData;
    auto& harbor = gameData.currentHarbor;
    auto& ship = gameData.currentShip;

    // Check if we're in the right state.
    if (gameData.gameState != models::GameState::InHarbor)
    {
      throw std::system_error(std::make_error_code(FunctionalError::InsuitableState));
    }

    // Get the ship cargo.
    auto shipCargo = std::find_if(ship.goods.begin(), ship.goods.end(), [&](const models::Cargo& cargo) {
      return cargo.name == command.command.cargoName.array;
    });
    if (shipCargo == ship.goods.end())
    {
      throw std::system_error(std::make_error_code(FunctionalError::CargoNotInShip));
    }

    // Check if the ship has enough of the cargo that we want to sell.
    if (shipCargo->amount < command.command.cargoAmount)
    {
      throw std::system_error(std::make_error_code(FunctionalError::InsufficientCargoInShip));
    }

    // Get the harbor cargo.
    auto harborCargo = std::find_if(harbor.goods.begin(), harbor.goods.end(), [&](const models::HarborCargo& cargo) {
      return cargo.cargo.name == command.command.cargoName.array;
    });
    if (harborCargo == harbor.goods.end())
    {
      throw std::system_error(std::make_error_code(FunctionalError::UnknownCargo));
    }

    // Calculate the total gold we are going to earn.
    auto totalGoldToEarn = harborCargo->price * command.command.cargoAmount;

    // We good. Let's do this.
    gameData.currentGold += totalGoldToEarn;
    harborCargo->cargo.amount += command.command.cargoAmount;
    shipCargo->amount -= command.command.cargoAmount;
  }
};
}
}
}

#endif // LIBTURADOR_TURA_DOMAIN_COMMANDS_SELLCARGOCOMMANDHANDLER_HPP_INCLUDED
