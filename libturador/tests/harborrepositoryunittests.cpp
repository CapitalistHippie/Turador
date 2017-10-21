#include <gtest/gtest.h>

#include <tura/harborrepository.h>

#include <iostream>

#include "testhelpers.h"

using namespace tura;
using namespace testing;

TEST(HarborRepository, GetAmountOfHarbors_Returns24)
{
  // Arrange.
  HarborRepository sut;

  // Act.

  // Assert.
  EXPECT_EQ(24, sut.GetAmountOfHarbors());
}

TEST(HarborRepository, GetHarbors_ReturnsValidHarbors)
{
  // Arrange.
  HarborRepository sut;

  // Act.
  auto harbors = sut.GetHarbors();

  // Assert.
  for (unsigned int i = 0; i < sut.GetAmountOfHarbors(); ++i)
  {
    EXPECT_STRNE("", harbors[i].name);

    for (unsigned int j = 0; j < 15; ++j)
    {
      EXPECT_NE(0, harbors[i].goods[j].price);
      EXPECT_STRNE("", harbors[i].goods[j].cargo.name);
    }
  }
}
