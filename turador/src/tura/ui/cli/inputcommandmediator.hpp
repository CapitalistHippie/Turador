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
  typedef helpers::Array<CommandHandlerInvoker*, 32>::size_type CommandHandlerHandle;

  ~InputCommandMediator()
  {
    for (auto invoker : commandHandlerInvokers)
    {
      delete invoker;
    }
  }

  void HandleCommand(const InputCommand& command) const
  {
    for (unsigned int i = 0; i < commandHandlerCommandNames.size(); ++i)
    {
      if (command.command.array == commandHandlerCommandNames[i])
      {
        commandHandlerInvokers[i]->Invoke(command);
      }
    }
  }

  template<typename CommandHandler>
  CommandHandlerHandle RegisterCommandHandler(helpers::CharArray<64> commandName, CommandHandler commandHandler)
  {
    CommandHandlerInvoker* commandHandlerInvoker = new CommandHandlerInvokerImpl<CommandHandler>(commandHandler);

    try
    {
      auto index = commandHandlerCommandNames.size();

      commandHandlerCommandNames.Add(commandName);
      commandHandlerInvokers.Add(commandHandlerInvoker);

      return index;
    }
    catch (...)
    {
      delete commandHandlerInvoker;

      throw;
    }
  }

  void UnregisterCommandHandler(CommandHandlerHandle commandHandlerHandle)
  {
    delete commandHandlerInvokers[commandHandlerHandle];
    commandHandlerInvokers.Remove(commandHandlerHandle);
    commandHandlerCommandNames.Remove(commandHandlerHandle);
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
