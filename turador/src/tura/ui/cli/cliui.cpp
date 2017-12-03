#include "tura/ui/cli/cliui.h"

#include "tura/ui/cli/statehandlers/gamenotstartedstatehandler.hpp"
#include "tura/ui/cli/statehandlers/gameoverstatehandler.hpp"
#include "tura/ui/cli/statehandlers/inharborstatehandler.hpp"

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
        new statehandlers::GameNotStartedStateHandler(*this, gameClient, commandParser, commandMediator, outputStream);
      break;
    case CliUiState::InHarbor:
      activeStateHandler =
        new statehandlers::InHarborStateHandler(*this, gameClient, commandParser, commandMediator, outputStream);
      break;
    case CliUiState::GameOver:
      activeStateHandler =
        new statehandlers::GameOverStateHandler(*this, gameClient, commandParser, commandMediator, outputStream);
      // default:
      // TODO: Throw.
  }

  activeStateHandler->EnterState();
}
