#ifndef TURADOR_TURA_UI_CLI_STATEHANDLERS_BASESTATEHANDLER_HPP_INCLUDED
#define TURADOR_TURA_UI_CLI_STATEHANDLERS_BASESTATEHANDLER_HPP_INCLUDED

#include <istream>
#include <ostream>

#include <tura/helpers/array.hpp>
#include <tura/helpers/chararray.hpp>

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

protected:
  CliUi& context;
  app::GameClient& gameClient;
  InputCommandParser& commandParser;
  std::ostream& outputStream;

public:
  BaseStateHandler(CliUi& context,
                   app::GameClient& gameClient,
                   InputCommandParser& commandParser,
                   std::ostream& outputStream)
    : context(context)
    , gameClient(gameClient)
    , commandParser(commandParser)
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

    ExitStateFromBase();
  }

  template<typename... Parameters>
  void RegisterCommand(helpers::CharArray<64> commandName)
  {
    commandParser.RegisterCommand<Parameters...>(commandName);

    commandNamesToUnregister.Add(commandName);
  }
};
}
}
}
}

#endif // TURADOR_TURA_UI_CLI_STATEHANDLERS_BASESTATEHANDLER_HPP_INCLUDED
