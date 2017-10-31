#include <system_error>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <tura/commandhandlers/purchasecargocommandhandler.hpp>
#include <tura/commands/purchasecargocommand.h>
#include <tura/error.h>
#include <tura/harborbuilder.hpp>
#include <tura/models/harbor.h>
#include <tura/models/ship.h>
#include <tura/models/shiptype.h>
#include <tura/shipbuilder.hpp>

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
  const char* const cargoName = "Test cargo";

  tura::HarborBuilder harborBuilder;
  auto harbor = harborBuilder.WithName("Test harbor").WithCargo(cargoName, 100, 100).Build();

  tura::models::ShipType shipType;
  shipType.cargoSpaceMax = 10000;

  tura::ShipBuilder shipBuilder;
  auto ship = shipBuilder.WithShipType(shipType).WithCargo(cargoName, 0).Build();

  tura::models::Game gameData;
  gameData.gameState = tura::models::GameState::InHarbor;
  gameData.currentGold = 0;
  gameData.currentHarbor = harbor;
  gameData.currentShip = ship;

  auto command = BuildCommand(cargoName, 1);
  tura::commands::CommandBase<tura::commands::PurchaseCargoCommand> wrappedCommand(command, gameData);

  tura::commandhandlers::PurchaseCargoCommandHandler sut;

  // Act and assert.
  ASSERT_THROW_SYSTEM_ERROR(sut.HandleCommand(wrappedCommand), tura::Error::InsufficientGold);
}

TEST(PurchaseCargoCommandHandler, HandleCommand_NotEnoughCargoInHarbor_ThrowsInsufficientCargoInHarbor)
{
  // Arrange.
  const char* const cargoName = "Test cargo";

  tura::HarborBuilder harborBuilder;
  auto harbor = harborBuilder.WithName("Test harbor").WithCargo(cargoName, 1, 100).Build();

  tura::models::Game gameData;
  gameData.gameState = tura::models::GameState::InHarbor;
  gameData.currentGold = 10000;
  gameData.currentHarbor = harbor;

  auto command = BuildCommand(cargoName, 100);
  tura::commands::CommandBase<tura::commands::PurchaseCargoCommand> wrappedCommand(command, gameData);

  tura::commandhandlers::PurchaseCargoCommandHandler sut;

  // Act and assert.
  ASSERT_THROW_SYSTEM_ERROR(sut.HandleCommand(wrappedCommand), tura::Error::InsufficientCargoInHarbor);
}

TEST(PurchaseCargoCommandHandler, HandleCommand_NotEnoughCargoSpaceInShip_ThrowsInsufficientShipCargoSpace)
{
  // Arrange.
  const char* const cargoName = "Test cargo";

  tura::HarborBuilder harborBuilder;
  auto harbor = harborBuilder.WithName("Test harbor").WithCargo(cargoName, 10000, 10).Build();

  tura::models::ShipType shipType;
  shipType.cargoSpaceMax = 100;

  tura::ShipBuilder shipBuilder;
  auto ship = shipBuilder.WithShipType(shipType).WithCargo(cargoName, 10).Build();

  tura::models::Game gameData;
  gameData.gameState = tura::models::GameState::InHarbor;
  gameData.currentGold = 10000;
  gameData.currentHarbor = harbor;
  gameData.currentShip = ship;

  auto command = BuildCommand(cargoName, 100);
  tura::commands::CommandBase<tura::commands::PurchaseCargoCommand> wrappedCommand(command, gameData);

  tura::commandhandlers::PurchaseCargoCommandHandler sut;

  // Act and assert.
  ASSERT_THROW_SYSTEM_ERROR(sut.HandleCommand(wrappedCommand), tura::Error::InsufficientShipCargoSpace);
}

TEST(PurchaseCargoCommandHandler, HandleCommand_DecreasesHarborCargoAmountByRequestedAmount)
{
  // Arrange.
  const char* const cargoName = "Test cargo";
  const int harborCargoAmount = 10000;
  const int purchaseAmount = 10;

  tura::HarborBuilder harborBuilder;
  auto harbor = harborBuilder.WithName("Test harbor").WithCargo(cargoName, harborCargoAmount, 10).Build();

  tura::models::ShipType shipType;
  shipType.cargoSpaceMax = 10000;

  tura::ShipBuilder shipBuilder;
  auto ship = shipBuilder.WithShipType(shipType).WithCargo(cargoName, 0).Build();

  tura::models::Game gameData;
  gameData.gameState = tura::models::GameState::InHarbor;
  gameData.currentGold = 10000;
  gameData.currentHarbor = harbor;
  gameData.currentShip = ship;

  auto command = BuildCommand(cargoName, purchaseAmount);
  tura::commands::CommandBase<tura::commands::PurchaseCargoCommand> wrappedCommand(command, gameData);

  tura::commandhandlers::PurchaseCargoCommandHandler sut;

  // Act.
  sut.HandleCommand(wrappedCommand);

  // Assert.
  EXPECT_EQ(harborCargoAmount - purchaseAmount, gameData.currentHarbor.goods[0].cargo.amount);
}

TEST(PurchaseCargoCommandHandler, HandleCommand_DecreasesCurrentGoldByGoldSpent)
{
  // Arrange.
  const char* const cargoName = "Test cargo";
  const int harborCargoAmount = 10000;
  const int purchaseAmount = 10;
  const int harborCargoPrice = 10;
  const int startingGold = 10000;
  const int goldSpent = purchaseAmount * harborCargoPrice;
  const int expectedGold = startingGold - goldSpent;

  tura::HarborBuilder harborBuilder;
  auto harbor = harborBuilder.WithName("Test harbor").WithCargo(cargoName, harborCargoAmount, harborCargoPrice).Build();

  tura::models::ShipType shipType;
  shipType.cargoSpaceMax = 10000;

  tura::ShipBuilder shipBuilder;
  auto ship = shipBuilder.WithShipType(shipType).WithCargo(cargoName, 0).Build();

  tura::models::Game gameData;
  gameData.gameState = tura::models::GameState::InHarbor;
  gameData.currentGold = startingGold;
  gameData.currentHarbor = harbor;
  gameData.currentShip = ship;

  auto command = BuildCommand(cargoName, purchaseAmount);
  tura::commands::CommandBase<tura::commands::PurchaseCargoCommand> wrappedCommand(command, gameData);

  tura::commandhandlers::PurchaseCargoCommandHandler sut;

  // Act.
  sut.HandleCommand(wrappedCommand);

  // Assert.
  EXPECT_EQ(expectedGold, gameData.currentGold);
}

TEST(PurchaseCargoCommandHandler, HandleCommand_IncreasesShipCargoByAmountPurchased)
{
  // Arrange.
  const char* const cargoName = "Test cargo";
  const int purchaseAmount = 10;
  const int currentCargoAmountInShip = 10;
  const int expectedCargoAmountInShip = purchaseAmount + currentCargoAmountInShip;

  tura::HarborBuilder harborBuilder;
  auto harbor = harborBuilder.WithName("Test harbor").WithCargo(cargoName, 10000, 10).Build();

  tura::models::ShipType shipType;
  shipType.cargoSpaceMax = 10000;

  tura::ShipBuilder shipBuilder;
  auto ship = shipBuilder.WithShipType(shipType).WithCargo(cargoName, currentCargoAmountInShip).Build();

  tura::models::Game gameData;
  gameData.gameState = tura::models::GameState::InHarbor;
  gameData.currentGold = 10000;
  gameData.currentHarbor = harbor;
  gameData.currentShip = ship;

  auto command = BuildCommand(cargoName, purchaseAmount);
  tura::commands::CommandBase<tura::commands::PurchaseCargoCommand> wrappedCommand(command, gameData);

  tura::commandhandlers::PurchaseCargoCommandHandler sut;

  // Act.
  sut.HandleCommand(wrappedCommand);

  // Assert.
  EXPECT_EQ(expectedCargoAmountInShip, gameData.currentShip.goods[0].amount);
}
