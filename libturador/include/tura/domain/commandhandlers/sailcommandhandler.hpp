#ifndef LIBTURADOR_TURA_DOMAIN_COMMANDHANDLERS_SAILCOMMANDHANDLER_HPP_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_COMMANDHANDLERS_SAILCOMMANDHANDLER_HPP_INCLUDED

#include <algorithm>
#include <system_error>

#include "tura/domain/commands/commandbase.h"
#include "tura/domain/commands/sailcommand.h"
#include "tura/domain/constants.h"
#include "tura/domain/functionalerror.h"
#include "tura/domain/functionalerrorcategory.h"
#include "tura/domain/models/gamestate.h"
#include "tura/domain/models/sailroute.h"
#include "tura/domain/models/sailtrip.h"
#include "tura/helpers/commandmediator.hpp"

namespace tura
{
namespace domain
{
namespace commandhandlers
{
class SailCommandHandler : public helpers::CommandHandlerBase<commands::CommandBase<commands::SailCommand>>
{
public:
  void HandleCommand(const commands::CommandBase<commands::SailCommand>& command) const override
  {
    auto& gameData = command.gameData;
    auto& harbor = gameData.currentHarbor;
    auto& ship = gameData.currentShip;

    // Check if we're in the right state.
    if (gameData.gameState != models::GameState::InHarbor)
    {
      throw std::system_error(std::make_error_code(FunctionalError::InsuitableState));
    }

    // Get the sail route.
    auto sailRoute =
      std::find_if(harbor.sailRoutes.begin(), harbor.sailRoutes.end(), [&](const domain::models::SailRoute& sailRoute) {
        return sailRoute.toHarborName == command.command.harborName;
      });
    if (sailRoute == harbor.sailRoutes.end())
    {
      throw std::system_error(std::make_error_code(FunctionalError::UnknownSailRoute), "Unknown sail route.");
    }

    // Let's do it.
    gameData.gameState = models::GameState::Sailing;
    models::SailTrip sailTrip;
    sailTrip.route = *sailRoute;
    gameData.currentSailTrip = sailTrip;
  }
};
}
}
}

#endif // #ifndef LIBTURADOR_TURA_DOMAIN_COMMANDHANDLERS_SAILCOMMANDHANDLER_HPP_INCLUDED
