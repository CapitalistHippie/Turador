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

TEST(PurchaseCargoCommandHandler, HandleCommand_NotInHarbor_ThrowsInsuitableState)
{
  // Arrange.
  tura::HarborBuilder harborBuilder;
  auto harbor = harborBuilder.WithName("Test harbor").Build();

  StrictMock<HarborFactoryMock> harborFactoryMock;
  ON_CALL(harborFactoryMock, GetHarborByIndex(0)).WillByDefault(Return(harbor));

  tura::GameBuilder gameBuilder;
  auto game = gameBuilder.WithHarborFactory(&harborFactoryMock).Build();

  tura::commands::PurchaseCargoCommand command(game);

  tura::commandhandlers::PurchaseCargoCommandHandler sut;

  // Act and assert.
  ASSERT_THROW_SYSTEM_ERROR(sut.HandleCommand(command), tura::Error::InsuitableState);
}
