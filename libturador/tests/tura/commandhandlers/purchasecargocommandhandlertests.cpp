#include <system_error>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <tura/commandhandlers/purchasecargocommandhandler.hpp>
#include <tura/commands/purchasecargocommand.h>
#include <tura/error.h>
#include <tura/harborbuilder.hpp>
#include <tura/models/harbor.h>

#include "../../helpers/testhelpers.h"

using namespace testing;

tura::commands::PurchaseCargoCommand BuildCommand(const char* const cargoName = nullptr, unsigned int cargoAmount = 0)
{
  tura::commands::PurchaseCargoCommand command;
  if (cargoName != nullptr)
  {
    strncpy(command.cargoName, cargoName, sizeof(command.cargoName));
  }
  command.cargoAmount = cargoAmount;

  return command;
}

TEST(PurchaseCargoCommandHandler, HandleCommand_NotInHarbor_ThrowsInsuitableState)
{
  // Arrange.
  tura::models::Game gameData;
  gameData.gameState = tura::models::GameState::NotStarted;

  tura::commands::PurchaseCargoCommand command;
  tura::commands::CommandBase<tura::commands::PurchaseCargoCommand> wrappedCommand(command, gameData);

  tura::commandhandlers::PurchaseCargoCommandHandler sut;

  // Act and assert.
  ASSERT_THROW_SYSTEM_ERROR(sut.HandleCommand(wrappedCommand), tura::Error::InsuitableState);
}

TEST(PurchaseCargoCommandHandler, HandleCommand_NotEnoughGold_ThrowsInsufficientGold)
{
  // Arrange.
  const char* const harborName = "Test harbor";
  const char* const cargoName = "Test cargo";

  tura::HarborBuilder harborBuilder;
  auto harbor = harborBuilder.WithName(harborName).WithCargo(cargoName, 100, 100).Build();

  tura::models::Game gameData;
  gameData.gameState = tura::models::GameState::InHarbor;
  gameData.currentHarbor = harbor;

  auto command = BuildCommand(cargoName, 1);
  tura::commands::CommandBase<tura::commands::PurchaseCargoCommand> wrappedCommand(command, gameData);

  tura::commandhandlers::PurchaseCargoCommandHandler sut;

  // Act and assert.
  ASSERT_THROW_SYSTEM_ERROR(sut.HandleCommand(wrappedCommand), tura::Error::InsufficientGold);
}
