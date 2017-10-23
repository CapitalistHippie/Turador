#ifndef LIBTURADOR_TURA_COMMANDS_PURCHASECARGOCOMMANDHANDLER_HPP_INCLUDED
#define LIBTURADOR_TURA_COMMANDS_PURCHASECARGOCOMMANDHANDLER_HPP_INCLUDED

#include <system_error>

#include "../../commandhandler.hpp"
#include "../commands/purchasecargocommand.h"
#include "../error.h"
#include "../game.h"
#include "../models/gamestate.h"

namespace tura
{
namespace commandhandlers
{
class PurchaseCargoCommandHandler : public CommandHandlerBase<commands::PurchaseCargoCommand>
{
public:
  void HandleCommand(const commands::PurchaseCargoCommand& command) override
  {
    if (command.game.GetState() != models::GameState::InHarbor)
    {
      throw std::system_error(std::make_error_code(Error::InsuitableState));
    }
  }
};
}
}

#endif // LIBTURADOR_TURA_COMMANDS_PURCHASECARGOCOMMANDHANDLER_HPP_INCLUDED
