#include <system_error>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <tura/commandhandlers/purchasecargocommandhandler.hpp>
#include <tura/commands/purchasecargocommand.h>
#include <tura/error.h>
#include <tura/game.h>
#include <tura/gamebuilder.hpp>
#include <tura/harborbuilder.hpp>
#include <tura/models/harbor.h>

#include "../../helpers/testhelpers.h"
#include "../../mocks/harborfactorymock.h"

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
  tura::GameBuilder gameBuilder;
  auto game = gameBuilder.Build();

  tura::commands::PurchaseCargoCommand command;

  // Act and assert.
  ASSERT_THROW_SYSTEM_ERROR(game.HandleCommand(command), tura::Error::InsuitableState);
}

TEST(PurchaseCargoCommandHandler, HandleCommand_NotEnoughGold_ThrowsInsufficientGold)
{
  // Arrange.
  const char* const harborName = "Test harbor";
  const char* const cargoName = "Test cargo";

  tura::HarborBuilder harborBuilder;
  auto harbor = harborBuilder.WithName(harborName).WithCargo(cargoName, 100, 100).Build();

  StrictMock<HarborFactoryMock> harborFactoryMock;
  EXPECT_CALL(harborFactoryMock, GetHarborByIndex(0)).WillOnce(Return(harbor));

  tura::GameBuilder gameBuilder;
  auto game = gameBuilder.WithHarborFactory(&harborFactoryMock).WithStartingGold(0).Build();

  auto command = BuildCommand(cargoName, 1);

  // Act and assert.
  game.Start();
  ASSERT_THROW_SYSTEM_ERROR(game.HandleCommand(command), tura::Error::InsufficientGold);
}