#include <system_error>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <tura/commandhandlers/startgamecommandhandler.hpp>
#include <tura/commands/startgamecommand.h>
#include <tura/error.h>
#include <tura/harborbuilder.hpp>
#include <tura/models/gamestate.h>
#include <tura/models/harbor.h>
#include <tura/models/ship.h>
#include <tura/models/shiptype.h>
#include <tura/shipbuilder.hpp>

#include "../../helpers/testhelpers.h"

using namespace testing;

tura::commands::StartGameCommand BuildCommand()
{
  return tura::commands::StartGameCommand();
}

TEST(StartGameCommandHandler, HandleCommand_AlreadyRunning_ThrowsInsuitableState)
{
  // Arrange.
  tura::models::Game gameData;
  gameData.gameState = tura::models::GameState::InHarbor;

  tura::commands::StartGameCommand command;
  tura::commands::CommandBase<tura::commands::StartGameCommand> wrappedCommand(command, gameData);

  tura::commandhandlers::StartGameCommandHandler sut;

  // Act and assert.
  ASSERT_THROW_SYSTEM_ERROR(sut.HandleCommand(wrappedCommand), tura::Error::InsuitableState);
}

TEST(StartGameCommandHandler, HandleCommand_ResetsGameData)
{
  // Arrange.
  tura::models::Game gameData;
  gameData.currentGold = 100000;

  tura::commands::StartGameCommand command;
  tura::commands::CommandBase<tura::commands::StartGameCommand> wrappedCommand(command, gameData);

  tura::commandhandlers::StartGameCommandHandler sut;

  // Act.
  sut.HandleCommand(wrappedCommand);

  // Assert.
  EXPECT_EQ(1000, gameData.currentGold);
}

TEST(StartGameCommandHandler, HandleCommand_SetsStateToInHarbor)
{
  // Arrange.
  tura::models::Game gameData;

  tura::commands::StartGameCommand command;
  tura::commands::CommandBase<tura::commands::StartGameCommand> wrappedCommand(command, gameData);

  tura::commandhandlers::StartGameCommandHandler sut;

  // Act.
  sut.HandleCommand(wrappedCommand);

  // Assert.
  EXPECT_EQ(tura::models::GameState::InHarbor, gameData.gameState);
}

TEST(StartGameCommandHandler, HandleCommand_SetsCurrentHarborToRandomHarbor)
{
  // Arrange.
  tura::models::Game gameData;

  tura::commands::StartGameCommand command;
  tura::commands::CommandBase<tura::commands::StartGameCommand> wrappedCommand(command, gameData);

  tura::commandhandlers::StartGameCommandHandler sut;

  // Act.
  sut.HandleCommand(wrappedCommand);

  // Assert.
  EXPECT_EQ(tura::models::GameState::InHarbor, gameData.gameState);
}
