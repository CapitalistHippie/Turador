#include <system_error>

#include <gtest/gtest.h>

#include <tura/domain/commandhandlers/sellcargocommandhandler.hpp>
#include <tura/domain/commands/commandbase.h>
#include <tura/domain/commands/sellcargocommand.h>
#include <tura/domain/models/game.h>
#include <tura/domain/models/harbor.h>
#include <tura/domain/models/ship.h>
#include <tura/domain/models/shiptype.h>
#include <tura/error.h>
#include <tura/harborbuilder.hpp>
#include <tura/shipbuilder.hpp>

#include "helpers/testhelpers.h"

using namespace testing;
using namespace tura;
using namespace tura::domain::commands;
using namespace tura::domain::commandhandlers;
using namespace tura::domain::models;

TEST(SellCargoCommandHandler, HandleCommand_NotInHarbor_ThrowsInsuitableState)
{
  // Arrange.
  Game gameData;
  gameData.gameState = GameState::NotStarted;

  SellCargoCommand command;
  CommandBase<SellCargoCommand> wrappedCommand(command, gameData);

  SellCargoCommandHandler sut;

  // Act and assert.
  ASSERT_THROW_SYSTEM_ERROR(sut.HandleCommand(wrappedCommand), tura::Error::InsuitableState);
}

TEST(SellCargoCommandHandler, HandleCommand_NotEnoughCargoInShip_ThrowsInsufficientCargoInShip)
{
  // Arrange.
  const auto cargoName = "Test cargo";

  HarborBuilder harborBuilder;
  auto harbor = harborBuilder.WithCargo(cargoName, 100, 100).Build();

  ShipType shipType;

  ShipBuilder shipBuilder;
  auto ship = shipBuilder.WithShipType(shipType).WithCargo(cargoName, 10).Build();

  tura::domain::models::Game gameData;
  gameData.gameState = tura::domain::models::GameState::InHarbor;
  gameData.currentGold = 10000;
  gameData.currentHarbor = harbor;
  gameData.currentShip = ship;

  SellCargoCommand command;
  command.cargoName = cargoName;
  command.cargoAmount = 11;
  CommandBase<SellCargoCommand> wrappedCommand(command, gameData);

  SellCargoCommandHandler sut;

  // Act and assert.
  ASSERT_THROW_SYSTEM_ERROR(sut.HandleCommand(wrappedCommand), tura::Error::InsufficientCargoInShip);
}

TEST(SellCargoCommandHandler, HandleCommand_UnknownCargo_ThrowsUnknownCargo2)
{
  Harbor harbor;

  ShipType shipType;

  ShipBuilder shipBuilder;
  auto ship = shipBuilder.WithShipType(shipType).Build();

  tura::domain::models::Game gameData;
  gameData.gameState = tura::domain::models::GameState::InHarbor;
  gameData.currentGold = 10000;
  gameData.currentHarbor = harbor;
  gameData.currentShip = ship;

  SellCargoCommand command;
  command.cargoName = "Test cargo";
  command.cargoAmount = 11;
  CommandBase<SellCargoCommand> wrappedCommand(command, gameData);

  SellCargoCommandHandler sut;

  // Act and assert.
  ASSERT_THROW_SYSTEM_ERROR(sut.HandleCommand(wrappedCommand), tura::Error::UnknownCargo);
}

TEST(SellCargoCommandHandler, HandleCommand_RemovesCargoSoldFromShip)
{
  // Arrange.
  const auto cargoName = "Test cargo";

  HarborBuilder harborBuilder;
  auto harbor = harborBuilder.WithCargo(cargoName, 100, 100).Build();

  ShipType shipType;

  ShipBuilder shipBuilder;
  auto ship = shipBuilder.WithShipType(shipType).WithCargo(cargoName, 10).Build();

  tura::domain::models::Game gameData;
  gameData.gameState = tura::domain::models::GameState::InHarbor;
  gameData.currentGold = 0;
  gameData.currentHarbor = harbor;
  gameData.currentShip = ship;

  SellCargoCommand command;
  command.cargoName = cargoName;
  command.cargoAmount = 10;
  CommandBase<SellCargoCommand> wrappedCommand(command, gameData);

  SellCargoCommandHandler sut;

  // Act.
  sut.HandleCommand(wrappedCommand);

  // Assert.
  EXPECT_EQ(gameData.currentShip.goods[0].amount, 0);
}

TEST(SellCargoCommandHandler, HandleCommand_AddsCargoSoldToHarbor)
{
  // Arrange.
  const auto cargoName = "Test cargo";

  HarborBuilder harborBuilder;
  auto harbor = harborBuilder.WithCargo(cargoName, 100, 100).Build();

  ShipType shipType;

  ShipBuilder shipBuilder;
  auto ship = shipBuilder.WithShipType(shipType).WithCargo(cargoName, 10).Build();

  tura::domain::models::Game gameData;
  gameData.gameState = tura::domain::models::GameState::InHarbor;
  gameData.currentGold = 0;
  gameData.currentHarbor = harbor;
  gameData.currentShip = ship;

  SellCargoCommand command;
  command.cargoName = cargoName;
  command.cargoAmount = 10;
  CommandBase<SellCargoCommand> wrappedCommand(command, gameData);

  SellCargoCommandHandler sut;

  // Act.
  sut.HandleCommand(wrappedCommand);

  // Assert.
  EXPECT_EQ(gameData.currentHarbor.goods[0].cargo.amount, 110);
}

TEST(SellCargoCommandHandler, HandleCommand_AddsCorrectAmountOfGoldToPlayer)
{
  // Arrange.
  const auto cargoName = "Test cargo";

  HarborBuilder harborBuilder;
  auto harbor = harborBuilder.WithCargo(cargoName, 100, 100).Build();

  ShipType shipType;

  ShipBuilder shipBuilder;
  auto ship = shipBuilder.WithShipType(shipType).WithCargo(cargoName, 10).Build();

  tura::domain::models::Game gameData;
  gameData.gameState = tura::domain::models::GameState::InHarbor;
  gameData.currentGold = 0;
  gameData.currentHarbor = harbor;
  gameData.currentShip = ship;

  SellCargoCommand command;
  command.cargoName = cargoName;
  command.cargoAmount = 10;
  CommandBase<SellCargoCommand> wrappedCommand(command, gameData);

  SellCargoCommandHandler sut;

  // Act.
  sut.HandleCommand(wrappedCommand);

  // Assert.
  EXPECT_EQ(gameData.currentGold, 1000);
}
