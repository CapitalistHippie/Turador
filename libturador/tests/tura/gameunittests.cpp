#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <tura/game.h>
#include <tura/gamebuilder.hpp>
#include <tura/harborbuilder.hpp>
#include <tura/models/gamestate.h>
#include <tura/models/harbor.h>

#include "../helpers/testhelpers.h"
#include "../mocks/harborfactorymock.h"

using namespace testing;

TEST(Game, Start_GameStartsInHarborState)
{
  // Arrange.
  tura::HarborBuilder harborBuilder;
  auto harbor = harborBuilder.WithName("Test harbor").Build();

  StrictMock<HarborFactoryMock> harborFactoryMock;
  ON_CALL(harborFactoryMock, GetHarborByIndex(0)).WillByDefault(Return(harbor));

  tura::GameBuilder gameBuilder;
  auto sut = gameBuilder.WithHarborFactory(&harborFactoryMock).Build();

  // Act.
  sut.Start();

  // Assert.
  EXPECT_EQ(tura::models::GameState::InHarbor, sut.GetState());
}
