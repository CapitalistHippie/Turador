#ifndef LIBTURADOR_COMMANDMEDIATOR_HPP_INCLUDED
#define LIBTURADOR_COMMANDMEDIATOR_HPP_INCLUDED

#include <typeindex>

#include "noncopyable.h"

class CommandInterface
{
public:
  virtual ~CommandInterface() = default;
};

class CommandHandlerInterface
{
public:
  virtual ~CommandHandlerInterface() = default;

  virtual void HandleCommand(const CommandInterface& command) const = 0;
};

template<typename Command>
class CommandHandlerBase : public CommandHandlerInterface
{
public:
  virtual ~CommandHandlerBase() = default;

  void HandleCommand(const CommandInterface& command) const override
  {
    HandleCommand(static_cast<const Command&>(command));
  }

  virtual void HandleCommand(const Command& command) const = 0;
};

class CommandMediator : public Noncopyable
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

    virtual ~CommandCommandHandlerInterface() = default;

    std::type_index commandTypeIndex;
    virtual const CommandHandlerInterface& GetCommandHandler() const = 0;
  };

  template<typename Command, typename CommandHandler>
  class CommandCommandHandler : public CommandCommandHandlerInterface
  {
  public:
    CommandHandler commandHandler;

    CommandCommandHandler()
      : CommandCommandHandlerInterface(typeid(Command))
    {
    }

    const CommandHandlerInterface& GetCommandHandler() const override { return commandHandler; }
  };

  unsigned int commandHandlersCount;
  CommandCommandHandlerInterface* commandHandlers[COMMAND_HANDLERS_COUNT_MAX];

public:
  CommandMediator()
    : commandHandlersCount(0)
  {
  }

  CommandMediator(CommandMediator&& other) = default;
  CommandMediator& operator=(CommandMediator&& other) = default;

  virtual ~CommandMediator()
  {
    for (unsigned int i = 0; i < commandHandlersCount; ++i)
    {
      delete commandHandlers[i];
    }
  }

  template<typename Command>
  void HandleCommand(const Command& command) const
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

#endif // LIBTURADOR_COMMANDMEDIATOR_HPP_INCLUDED
