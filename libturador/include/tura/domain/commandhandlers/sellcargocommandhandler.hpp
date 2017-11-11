#ifndef LIBTURADOR_TURA_DOMAIN_COMMANDS_SELLCARGOCOMMANDHANDLER_HPP_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_COMMANDS_SELLCARGOCOMMANDHANDLER_HPP_INCLUDED

#include <system_error>

#include "tura/domain/commandmediator.hpp"
#include "tura/domain/commands/commandbase.h"
#include "tura/domain/commands/sellcargocommand.h"
#include "tura/domain/gamehelpers.hpp"
#include "tura/domain/models/game.h"
#include "tura/domain/models/gamestate.h"
#include "tura/error.h"

namespace tura
{
namespace domain
{
namespace commandhandlers
{
class SellCargoCommandHandler : public CommandHandlerBase<commands::CommandBase<commands::SellCargoCommand>>
{
public:
  void HandleCommand(const commands::CommandBase<commands::SellCargoCommand>& command) const override
  {
    auto& gameData = command.gameData;

    // Check if we're in the right state.
    if (gameData.gameState != models::GameState::InHarbor)
    {
      throw std::system_error(std::make_error_code(Error::InsuitableState));
    }

    // Get the ship cargo.
    auto& shipCargo = GetShipCargoByName(gameData.currentShip, command.command.cargoName.array);

    // Check if the ship has enough of the cargo that we want to sell.
    if (shipCargo.amount < command.command.cargoAmount)
    {
      throw std::system_error(std::make_error_code(Error::InsufficientCargoInShip));
    }

    // Get the harbor cargo.
    auto& harborCargo = GetHarborCargoByName(gameData.currentHarbor, command.command.cargoName.array);

    // Calculate the total gold we are going to earn.
    auto totalGoldToEarn = harborCargo.price * command.command.cargoAmount;

    // We good. Let's do this.
    gameData.currentGold += totalGoldToEarn;
    harborCargo.cargo.amount += command.command.cargoAmount;
    shipCargo.amount -= command.command.cargoAmount;
  }
};
}
}
}

#endif // LIBTURADOR_TURA_DOMAIN_COMMANDS_SELLCARGOCOMMANDHANDLER_HPP_INCLUDED
