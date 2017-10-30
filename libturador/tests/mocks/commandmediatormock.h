#ifndef LIBTURADOR_TESTS_MOCKS_COMMANDMEDIATORMOCK_H_INCLUDED
#define LIBTURADOR_TESTS_MOCKS_COMMANDMEDIATORMOCK_H_INCLUDED

#include <gmock/gmock.h>

#include <commandmediator.hpp>
#include <tura/commands/commandbase.h>
#include <tura/commands/purchasecargocommand.h>

class CommandMediatorMock : public CommandMediator
{
public:
  MOCK_CONST_METHOD1(HandleCommandPurchaseCargoCommand,
                     void(const tura::commands::CommandBase<tura::commands::PurchaseCargoCommand>& command));

  template<typename Command>
  void HandleCommand(const Command& command) const;

  template<>
  void HandleCommand(const tura::commands::CommandBase<tura::commands::PurchaseCargoCommand>& command) const
  {
    HandleCommandPurchaseCargoCommand(command);
  }
};

#endif // LIBTURADOR_TESTS_MOCKS_COMMANDMEDIATORMOCK_H_INCLUDED
