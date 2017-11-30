#ifndef TURADOR_TURA_UI_CLI_CLIUI_H_INCLUDED
#define TURADOR_TURA_UI_CLI_CLIUI_H_INCLUDED

#include <functional>
#include <istream>
#include <ostream>

#include <tura/app/gameclient.hpp>
#include <tura/error.h>
#include <tura/helpers/noncopyable.h>

#include "tura/ui/cli/cliuistate.h"
#include "tura/ui/cli/consolehelpers.hpp"
#include "tura/ui/cli/helpers.hpp"
#include "tura/ui/cli/inputcommandmediator.hpp"
#include "tura/ui/cli/inputcommandparser.hpp"
#include "tura/ui/cli/statehandlers/statehandler.h"

namespace tura
{
namespace ui
{
namespace cli
{
class CliUi : helpers::Noncopyable
{
private:
  app::GameClient& gameClient;
  std::istream& inputStream;
  std::ostream& outputStream;
  InputCommandParser commandParser;
  InputCommandMediator commandMediator;

  bool started;
  bool shouldStop;

  CliUiState state;

  statehandlers::StateHandler* activeStateHandler;

public:
  CliUi(app::GameClient& gameClient, std::istream& inputStream, std::ostream& outputStream)
    : gameClient(gameClient)
    , inputStream(inputStream)
    , outputStream(outputStream)
    , started(false)
    , shouldStop(false)
    , activeStateHandler(nullptr)
    , state(CliUiState::GameNotStarted)
  {
  }

  ~CliUi()
  {
    if (activeStateHandler != nullptr)
    {
      delete activeStateHandler;
    }
  }

  void Start()
  {
    if (started)
    {
      return;
    }

    commandParser.RegisterCommand("quit");
    commandParser.RegisterCommand("exit");
    commandParser.RegisterCommand("stop");

    auto stopFunction = std::bind(&CliUi::Stop, this);

    commandMediator.RegisterCommandHandler("quit", stopFunction);
    commandMediator.RegisterCommandHandler("exit", stopFunction);
    commandMediator.RegisterCommandHandler("stop", stopFunction);

    auto initialState = GetCliUiStateFromGameState(gameClient.GetGameData().gameState);
    SetState(initialState);

    RenderConsole();

    started = true;

    do
    {
      try
      {
        auto command = commandParser.ParseCommand(inputStream);
        commandMediator.HandleCommand(command);

        RenderConsole();
      }
      catch (const std::system_error& e)
      {
        if (e.code() == Error::CommandNotRegistered)
        {
          RenderConsole();

          outputStream << "\nUnavailable or unknown command. Please try again!\n";
        }
        else
        {
          throw;
        }
      }
    } while (!shouldStop);

    commandParser.Clear();
    commandMediator.Clear();

    started = false;
    shouldStop = false;
  }

  void Stop()
  {
    if (!started)
    {
      return;
    }

    shouldStop = true;
  }

  void SetState(CliUiState state);

  void RenderConsole()
  {
    ClearConsole();

    if (activeStateHandler == nullptr)
    {
      // TODO: Throw.
    }

    activeStateHandler->RenderConsole();
  }
};
}
}
}

#endif // #ifndef TURADOR_TURA_UI_CLI_CLIUI_H_INCLUDED
