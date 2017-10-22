#ifndef LIBTURADOR_TURA_COMMANDS_PURCHASECARGOCOMMANDHANDLER_HPP_INCLUDED
#define LIBTURADOR_TURA_COMMANDS_PURCHASECARGOCOMMANDHANDLER_HPP_INCLUDED

#include "../../commandhandler.hpp"
#include "../commands/purchasecargocommand.h"

namespace tura
{
namespace commandhandlers
{
class PurchaseCargoCommandHandler : public CommandHandlerBase<commands::PurchaseCargoCommand>
{
public:
  void HandleCommand(const commands::PurchaseCargoCommand& command) override {}
};
}
}

#endif // LIBTURADOR_TURA_COMMANDS_PURCHASECARGOCOMMANDHANDLER_HPP_INCLUDED
