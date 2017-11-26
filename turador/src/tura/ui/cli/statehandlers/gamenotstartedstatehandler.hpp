#ifndef TURADOR_TURA_UI_CLI_STATEHANDLERS_GAMENOTSTARTEDSTATEHANDLER_HPP_INCLUDED
#define TURADOR_TURA_UI_CLI_STATEHANDLERS_GAMENOTSTARTEDSTATEHANDLER_HPP_INCLUDED

#include "tura/ui/cli/statehandlers/basestatehandler.hpp"

namespace tura
{
namespace ui
{
namespace cli
{
namespace statehandlers
{
class GameNotStartedStateHandler : public BaseStateHandler
{
public:
  using BaseStateHandler::BaseStateHandler;

  void EnterState() override {}

  void ExitStateFromBase() noexcept override {}

  void RenderConsole() const override {}
};
}
}
}
}

#endif // TURADOR_TURA_UI_CLI_STATEHANDLERS_GAMENOTSTARTEDSTATEHANDLER_HPP_INCLUDED
