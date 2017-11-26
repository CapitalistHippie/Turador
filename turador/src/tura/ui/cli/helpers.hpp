#ifndef TURADOR_TURA_UI_CLI_HELPERS_HPP_INCLUDED
#define TURADOR_TURA_UI_CLI_HELPERS_HPP_INCLUDED

#include <tura/domain/models/gamestate.h>

#include "tura/ui/cli/cliuistate.h"

namespace tura
{
namespace ui
{
namespace cli
{
inline CliUiState GetCliUiStateFromGameState(domain::models::GameState gameState)
{
  switch (gameState)
  {
    case domain::models::GameState::NotStarted:
      return CliUiState::GameNotStarted;
  }

  // TODO: Throw.
}
}
}
}

#endif // #ifndef TURADOR_TURA_UI_CLI_HELPERS_HPP_INCLUDED
