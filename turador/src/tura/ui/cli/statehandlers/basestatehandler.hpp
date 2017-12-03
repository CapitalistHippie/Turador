#ifndef TURADOR_TURA_UI_CLI_STATEHANDLERS_BASESTATEHANDLER_HPP_INCLUDED
#define TURADOR_TURA_UI_CLI_STATEHANDLERS_BASESTATEHANDLER_HPP_INCLUDED

#include <istream>
#include <ostream>

#include <tura/helpers/array.hpp>
#include <tura/helpers/chararray.hpp>

#include "tura/ui/cli/inputcommandmediator.hpp"
#include "tura/ui/cli/inputcommandparser.hpp"
#include "tura/ui/cli/statehandlers/statehandler.h"

namespace tura
{
namespace ui
{
namespace cli
{
class CliUi;

namespace statehandlers
{
class BaseStateHandler : public StateHandler
{
private:
  helpers::Array<helpers::CharArray<64>, 32> commandNamesToUnregister;
  helpers::Array<InputCommandMediator::CommandHandlerHandle, 32> commandHandlerHandlesToUnregister;

protected:
  CliUi& context;
  app::GameClient& gameClient;
  InputCommandParser& commandParser;
  InputCommandMediator& commandMediator;
  std::ostream& outputStream;

public:
  BaseStateHandler(CliUi& context,
                   app::GameClient& gameClient,
                   InputCommandParser& commandParser,
                   InputCommandMediator& commandMediator,
                   std::ostream& outputStream)
    : context(context)
    , gameClient(gameClient)
    , commandParser(commandParser)
    , commandMediator(commandMediator)
    , outputStream(outputStream)
  {
  }
  virtual ~BaseStateHandler() = default;

  virtual void ExitStateFromBase() noexcept = 0;

  void ExitState() noexcept override
  {
    for (const auto& commandName : commandNamesToUnregister)
    {
      commandParser.UnregisterCommand(commandName);
    }

    for (int i = commandHandlerHandlesToUnregister.size() - 1; i >= 0; --i)
    {
      commandMediator.UnregisterCommandHandler(commandHandlerHandlesToUnregister[i]);
    }

    ExitStateFromBase();
  }

  template<typename... Parameters>
  void RegisterCommand(helpers::CharArray<64> commandName)
  {
    commandParser.RegisterCommand<Parameters...>(commandName);

    commandNamesToUnregister.Add(commandName);
  }

  template<typename CommandHandler>
  void RegisterCommandHandler(helpers::CharArray<64> commandName, CommandHandler commandHandler)
  {
    auto commandHandlerHandle = commandMediator.RegisterCommandHandler(commandName, commandHandler);

    commandHandlerHandlesToUnregister.Add(commandHandlerHandle);
  }
};
}
}
}
}

#endif // TURADOR_TURA_UI_CLI_STATEHANDLERS_BASESTATEHANDLER_HPP_INCLUDED
