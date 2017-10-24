#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <tura/game.h>
#include <tura/gamebuilder.hpp>
#include <tura/harborbuilder.hpp>
#include <tura/models/gamestate.h>
#include <tura/models/harbor.h>

#include "../mocks/harborfactorymock.h"

using namespace testing;

TEST(Game, Start_GameStartsInHarborState)
{
  // Arrange.
  const char* const harborName = "Test harbor";

  tura::HarborBuilder harborBuilder;
  auto harbor = harborBuilder.WithName(harborName).Build();

  StrictMock<HarborFactoryMock> harborFactoryMock;
  EXPECT_CALL(harborFactoryMock, GetHarborByIndex(0)).WillOnce(Return(harbor));

  tura::GameBuilder gameBuilder;
  auto sut = gameBuilder.WithHarborFactory(&harborFactoryMock).Build();

  // Act.
  sut.Start();

  // Assert.
  EXPECT_EQ(tura::models::GameState::InHarbor, sut.GetGameData().gameState);
}
