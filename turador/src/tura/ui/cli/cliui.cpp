#include "tura/ui/cli/cliui.h"

#include "tura/ui/cli/statehandlers/gamenotstartedstatehandler.hpp"

using namespace tura;
using namespace tura::ui;
using namespace tura::ui::cli;

void CliUi::SetState(CliUiState state)
{
  if (activeStateHandler != nullptr)
  {
    activeStateHandler->ExitState();
    delete activeStateHandler;
  }

  switch (state)
  {
    case CliUiState::GameNotStarted:
      activeStateHandler =
        new statehandlers::GameNotStartedStateHandler(*this, gameClient, commandParser, outputStream);
      break;
      // default:
      // TODO: Throw.
  }

  activeStateHandler->EnterState();
}
