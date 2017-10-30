#ifndef LIBTURADOR_TURA_COMMANDS_PURCHASECARGOCOMMANDHANDLER_HPP_INCLUDED
#define LIBTURADOR_TURA_COMMANDS_PURCHASECARGOCOMMANDHANDLER_HPP_INCLUDED

#include <system_error>

#include "../../commandmediator.hpp"
#include "../commands/purchasecargocommand.h"
#include "../error.h"
#include "../game.h"
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
    if (command.gameData.gameState != models::GameState::InHarbor)
    {
      throw std::system_error(std::make_error_code(Error::InsuitableState));
    }

    auto totalGoldToSpend =
      command.game.GetCurrentHarborCargoByName(command.command.cargoName).price * command.command.cargoAmount;

    if (command.gameData.currentGold < totalGoldToSpend)
    {
      throw std::system_error(std::make_error_code(Error::InsufficientGold));
    }
  }
};
}
}

#endif // LIBTURADOR_TURA_COMMANDS_PURCHASECARGOCOMMANDHANDLER_HPP_INCLUDED
