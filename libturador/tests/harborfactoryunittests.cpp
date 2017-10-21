#include <gtest/gtest.h>

#include <tura/harborfactory.h>

#include <iostream>

#include "testhelpers.h"

using namespace tura;
using namespace testing;

TEST(HarborFactory, GetAmountOfHarbors_Returns24)
{
  // Arrange.
  HarborFactory sut;

  // Act.

  // Assert.
  EXPECT_EQ(24, sut.GetAmountOfHarbors());
}

TEST(HarborRepository, GetHarbors_ReturnsValidHarbors)
{
  // Arrange.
  HarborFactory sut;

  // Act.

  // Assert.
  for (unsigned int i = 0; i < sut.GetAmountOfHarbors(); ++i)
  {
    auto harbor = sut.GetHarborByIndex(i);

    EXPECT_STRNE("", harbor.name);

    for (unsigned int j = 0; j < 15; ++j)
    {
      EXPECT_NE(0, harbor.goods[j].price);
      EXPECT_STRNE("", harbor.goods[j].cargo.name);
    }
  }
}
