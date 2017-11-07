#include <gtest/gtest.h>

#include <tura/dal/repositories/shiptypefilerepository.h>

using namespace testing;
using namespace tura::dal::repositories;
using namespace tura::domain::models;

TEST(ShipTypeRepository, GetShipTypeCount_Returns24)
{
  // Arrange.
  ShipTypeRepository sut;

  // Act.

  // Assert.
  EXPECT_EQ(13, sut.GetShipTypeCount());
}

TEST(ShipTypeRepository, GetShipTypeByName_ReturnsValidShipType)
{
  // Arrange.
  ShipTypeRepository sut;

  auto shipTypeName = "Barque";

  // Act.
  auto shipType = sut.GetShipTypeByName(shipTypeName);

  // Assert.
  EXPECT_STREQ(shipTypeName, shipType.name);
  EXPECT_EQ(36000, shipType.price);
  EXPECT_EQ(250, shipType.cargoSpaceMax);
  EXPECT_EQ(20, shipType.cannonSpaceMax);
  EXPECT_EQ(150, shipType.hitPointsMax);
  EXPECT_EQ(ShipSizeClass::Small, shipType.sizeClass);
  EXPECT_EQ(ShipWeightClass::Light, shipType.weightClass);
}
