#ifndef LIBTURADOR_TURA_DOMAIN_COMMANDS_RUNCOMMANDHANDLER_HPP_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_COMMANDS_RUNCOMMANDHANDLER_HPP_INCLUDED

#include <system_error>

#include "tura/domain/commands/commandbase.h"
#include "tura/domain/commands/runcommand.h"
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
class RunCommandHandler : public helpers::CommandHandlerBase<commands::CommandBase<commands::RunCommand>>
{
public:
  void HandleCommand(const commands::CommandBase<commands::RunCommand>& command) const override
  {
    auto& gameData = command.gameData;

    // Check if we're in the right state.
    if (gameData.gameState != models::GameState::InBattle)
    {
      throw std::system_error(std::make_error_code(FunctionalError::InsuitableState));
    }
  }
};
}
}
}

#endif // LIBTURADOR_TURA_DOMAIN_COMMANDS_RUNCOMMANDHANDLER_HPP_INCLUDED
