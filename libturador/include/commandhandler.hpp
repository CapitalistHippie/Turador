#ifndef LIBTURADOR_COMMANDHANDLER_HPP_INCLUDED
#define LIBTURADOR_COMMANDHANDLER_HPP_INCLUDED

#include <typeindex>

#include "noncopyable.h"

struct CommandInterface
{
};

class CommandHandlerInterface
{
public:
  virtual ~CommandHandlerInterface() {}

  virtual void HandleCommand(const CommandInterface& command) = 0;
};

template<typename Command>
class CommandHandlerBase : public CommandHandlerInterface
{
public:
  virtual ~CommandHandlerBase() {}

  void HandleCommand(const CommandInterface& command) override { HandleCommand(command); }

  virtual void HandleCommand(const Command& command) = 0;
};

class CommandHandler
{
public:
  static const unsigned int COMMAND_HANDLERS_COUNT_MAX = 64;

private:
  class CommandCommandHandlerInterface
  {
  public:
    CommandCommandHandlerInterface(std::type_index commandTypeIndex)
      : commandTypeIndex(commandTypeIndex)
    {
    }

    virtual ~CommandCommandHandlerInterface() {}

    std::type_index commandTypeIndex;
    virtual CommandHandlerInterface& GetCommandHandler() = 0;
  };

  template<typename Command, typename CommandHandler>
  class CommandCommandHandler
    : public CommandCommandHandlerInterface
    , public Noncopyable
  {
  public:
    CommandHandler commandHandler;

    CommandCommandHandler()
      : CommandCommandHandlerInterface(typeid(Command))
    {
    }

    CommandHandlerInterface& GetCommandHandler() override { return commandHandler; }
  };

  unsigned int commandHandlersCount;
  CommandCommandHandlerInterface* commandHandlers[COMMAND_HANDLERS_COUNT_MAX];

public:
  CommandHandler()
    : commandHandlersCount(0)
  {
  }

  ~CommandHandler()
  {
    for (unsigned int i = 0; i < commandHandlersCount; ++i)
    {
      delete commandHandlers[i];
    }
  }

  template<typename Command>
  void HandCommand(const Command& command)
  {
    for (unsigned int i = 0; i < commandHandlersCount; ++i)
    {
      if (commandHandlers[i]->commandTypeIndex == typeid(Command))
      {
        commandHandlers[i]->GetCommandHandler().HandleCommand(command);
      }
    }
  }

  template<typename Command, typename CommandHandler>
  void RegisterCommandHandler()
  {
    if (commandHandlersCount >= COMMAND_HANDLERS_COUNT_MAX)
    {
      // TODO: Throw.
    }

    CommandCommandHandlerInterface* commandHandler = new CommandCommandHandler<Command, CommandHandler>;

    try
    {
      commandHandlers[commandHandlersCount] = commandHandler;
    }
    catch (...)
    {
      delete commandHandler;

      throw;
    }

    commandHandlersCount++;
  }
};

#endif // LIBTURADOR_COMMANDHANDLER_HPP_INCLUDED
