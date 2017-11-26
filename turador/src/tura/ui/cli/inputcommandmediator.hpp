#ifndef TURADOR_TURA_UI_CLI_INPUTCOMMANDMEDIATOR_HPP_INCLUDED
#define TURADOR_TURA_UI_CLI_INPUTCOMMANDMEDIATOR_HPP_INCLUDED

#include <system_error>

#include <tura/helpers/array.hpp>
#include <tura/helpers/chararray.hpp>
#include <tura/helpers/noncopyable.h>

#include "tura/ui/cli/inputcommand.hpp"

namespace tura
{
namespace ui
{
namespace cli
{
class CommandHandlerInvoker
{
public:
  ~CommandHandlerInvoker() = default;

  virtual void Invoke(const InputCommand& command) const = 0;
};

template<typename CommandHandler>
class CommandHandlerInvokerImpl : public CommandHandlerInvoker
{
  CommandHandler commandHandler;

public:
  CommandHandlerInvokerImpl(CommandHandler commandHandler)
    : commandHandler(commandHandler)
  {
  }

  void Invoke(const InputCommand& command) const override { commandHandler(command); }
};

class InputCommandMediator : helpers::Noncopyable
{
private:
  helpers::Array<CommandHandlerInvoker*, 32> commandHandlerInvokers;
  helpers::Array<helpers::CharArray<64>, 32> commandHandlerCommandNames;

public:
  ~InputCommandMediator()
  {
    for (auto invoker : commandHandlerInvokers)
    {
      delete invoker;
    }
  }

  void HandleCommand(const InputCommand& command) const
  {
    if (!commandHandlerCommandNames.HasValue(command.command))
    {
      // TODO: Throw.
    }

    commandHandlerInvokers[commandHandlerCommandNames.IndexOf(command.command)]->Invoke(command);
  }

  template<typename CommandHandler>
  void RegisterCommandHandler(helpers::CharArray<64> commandName, CommandHandler commandHandler)
  {
    CommandHandlerInvoker* commandHandlerInvoker = new CommandHandlerInvokerImpl<CommandHandler>(commandHandler);

    try
    {
      commandHandlerCommandNames.Add(commandName);
      commandHandlerInvokers.Add(commandHandlerInvoker);
    }
    catch (...)
    {
      delete commandHandlerInvoker;

      throw;
    }
  }

  void Clear()
  {
    for (auto invoker : commandHandlerInvokers)
    {
      delete invoker;
    }

    commandHandlerInvokers.Clear();
    commandHandlerCommandNames.Clear();
  }
};
}
}
}

#endif // #ifndef TURADOR_TURA_UI_CLI_INPUTCOMMANDMEDIATOR_HPP_INCLUDED
