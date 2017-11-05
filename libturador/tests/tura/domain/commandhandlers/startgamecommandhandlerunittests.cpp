#include <system_error>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <tura/domain/commandhandlers/startgamecommandhandler.hpp>
#include <tura/domain/commands/startgamecommand.h>
#include <tura/domain/constants.h>
#include <tura/domain/models/gamestate.h>
#include <tura/domain/models/harbor.h>
#include <tura/domain/models/ship.h>
#include <tura/domain/models/shiptype.h>
#include <tura/error.h>
#include <tura/harborbuilder.hpp>
#include <tura/shipbuilder.hpp>

#include "../../../helpers/testhelpers.h"
#include "../../../mocks/harborgeneratormock.h"

using namespace testing;

tura::domain::commands::StartGameCommand BuildCommand()
{
  return tura::domain::commands::StartGameCommand();
}

TEST(StartGameCommandHandler, HandleCommand_AlreadyRunning_ThrowsInsuitableState)
{
  // Arrange.
  tura::domain::models::Game gameData;
  gameData.gameState = tura::domain::models::GameState::InHarbor;

  tura::domain::commands::StartGameCommand command;
  tura::domain::commands::CommandBase<tura::domain::commands::StartGameCommand> wrappedCommand(command, gameData);

  NiceMock<HarborGeneratorMock> harborGeneratorMock;

  tura::domain::commandhandlers::StartGameCommandHandler sut(&harborGeneratorMock);

  // Act and assert.
  ASSERT_THROW_SYSTEM_ERROR(sut.HandleCommand(wrappedCommand), tura::Error::InsuitableState);
}

TEST(StartGameCommandHandler, HandleCommand_ResetsGameData)
{
  // Arrange.
  tura::domain::models::Game gameData;
  gameData.currentGold = 100000;

  tura::domain::commands::StartGameCommand command;
  tura::domain::commands::CommandBase<tura::domain::commands::StartGameCommand> wrappedCommand(command, gameData);

  NiceMock<HarborGeneratorMock> harborGeneratorMock;

  tura::domain::commandhandlers::StartGameCommandHandler sut(&harborGeneratorMock);

  // Act.
  sut.HandleCommand(wrappedCommand);

  // Assert.
  EXPECT_EQ(tura::domain::Constants::GameInitialGold, gameData.currentGold);
}

TEST(StartGameCommandHandler, HandleCommand_SetsStateToInHarbor)
{
  // Arrange.
  tura::domain::models::Game gameData;

  tura::domain::commands::StartGameCommand command;
  tura::domain::commands::CommandBase<tura::domain::commands::StartGameCommand> wrappedCommand(command, gameData);

  NiceMock<HarborGeneratorMock> harborGeneratorMock;

  tura::domain::commandhandlers::StartGameCommandHandler sut(&harborGeneratorMock);

  // Act.
  sut.HandleCommand(wrappedCommand);

  // Assert.
  EXPECT_EQ(tura::domain::models::GameState::InHarbor, gameData.gameState);
}

TEST(StartGameCommandHandler, HandleCommand_SetsCurrentHarborToRandomHarbor)
{
  // Arrange.
  tura::domain::models::Game gameData;

  tura::domain::commands::StartGameCommand command;
  tura::domain::commands::CommandBase<tura::domain::commands::StartGameCommand> wrappedCommand(command, gameData);

  tura::HarborBuilder harborBuilder;
  auto randomHarbor = harborBuilder.WithName("Random harbor").Build();

  StrictMock<HarborGeneratorMock> harborGeneratorMock;
  EXPECT_CALL(harborGeneratorMock, GenerateRandomHarbor()).WillOnce(Return(randomHarbor));

  tura::domain::commandhandlers::StartGameCommandHandler sut(&harborGeneratorMock);

  // Act.
  sut.HandleCommand(wrappedCommand);

  // Assert.
  EXPECT_STREQ(randomHarbor.name, gameData.currentHarbor.name);
}
