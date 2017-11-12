#include <system_error>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <tura/domain/harborgenerator.hpp>
#include <tura/domain/models/harbor.h>
#include <tura/domain/models/harborgenerationparameters.h>
#include <tura/error.h>

#include "helpers/testhelpers.h"
#include "mocks/harborgenerationparametersrepositorymock.h"

using namespace testing;
using namespace tura::domain;
using namespace tura::domain::models;

TEST(HarborGenerator, GenerateHarbor_PriceMinHigherThanPriceMax_ThrowsInvalidArgument)
{
  // Arrange.
  HarborCargoGenerationParameters harborCargoGenerationParameters;
  harborCargoGenerationParameters.priceMin = 50;
  harborCargoGenerationParameters.priceMax = 40;

  HarborGenerationParameters harborGenerationParameters;
  harborGenerationParameters.cargoGenerationParameters.Add(harborCargoGenerationParameters);

  HarborGenerator sut;

  // Act and assert.
  EXPECT_THROW_SYSTEM_ERROR(sut.GenerateHarbor(harborGenerationParameters), tura::Error::InvalidArgument);
}

TEST(HarborGenerator, GenerateHarbor_AmountMinHigherThanAmountMax_ThrowsInvalidArgument)
{
  // Arrange.
  HarborCargoGenerationParameters harborCargoGenerationParameters;
  harborCargoGenerationParameters.amountMin = 50;
  harborCargoGenerationParameters.amountMax = 40;

  HarborGenerationParameters harborGenerationParameters;
  harborGenerationParameters.cargoGenerationParameters.Add(harborCargoGenerationParameters);

  HarborGenerator sut;

  // Act and assert.
  EXPECT_THROW_SYSTEM_ERROR(sut.GenerateHarbor(harborGenerationParameters), tura::Error::InvalidArgument);
}

TEST(HarborGenerator, GenerateHarbor_SetsHarborName)
{
  // Arrange.
  HarborGenerationParameters harborGenerationParameters;
  harborGenerationParameters.harborName = "Random harbor name";

  HarborGenerator sut;

  // Act.
  auto result = sut.GenerateHarbor(harborGenerationParameters);

  // Assert.
  EXPECT_STREQ(harborGenerationParameters.harborName.array, result.name.array);
}

TEST(HarborGenerator, GenerateHarbor_SetsHarborGoodsPricesBetweenInclusivePriceMinAndPriceMax)
{
  // Arrange.
  HarborCargoGenerationParameters harborCargoGenerationParameters;
  harborCargoGenerationParameters.priceMin = 50;
  harborCargoGenerationParameters.priceMax = 60;

  HarborGenerationParameters harborGenerationParameters;
  harborGenerationParameters.cargoGenerationParameters.Add(harborCargoGenerationParameters);

  HarborGenerator sut;

  // Act.
  auto result = sut.GenerateHarbor(harborGenerationParameters);

  // Assert.
  EXPECT_GE(result.goods[0].price, harborGenerationParameters.cargoGenerationParameters[0].priceMin);
  EXPECT_LE(result.goods[0].price, harborGenerationParameters.cargoGenerationParameters[0].priceMax);
}

TEST(HarborGenerator, GenerateHarbor_SetsHarborGoodsAmountsBetweenInclusiveAmountMinAndAmountMax)
{
  // Arrange.
  HarborCargoGenerationParameters harborCargoGenerationParameters;
  harborCargoGenerationParameters.amountMin = 50;
  harborCargoGenerationParameters.amountMax = 60;

  HarborGenerationParameters harborGenerationParameters;
  harborGenerationParameters.cargoGenerationParameters.Add(harborCargoGenerationParameters);

  HarborGenerator sut;

  // Act.
  auto result = sut.GenerateHarbor(harborGenerationParameters);

  // Assert.
  EXPECT_GE(result.goods[0].cargo.amount, harborGenerationParameters.cargoGenerationParameters[0].amountMin);
  EXPECT_LE(result.goods[0].cargo.amount, harborGenerationParameters.cargoGenerationParameters[0].amountMax);
}

TEST(HarborGenerator, GenerateHarbor_SetsLightHarborCannonsForSaleBetweenInclusiveMinAndMax)
{
  // Arrange.
  HarborGenerationParameters harborGenerationParameters;

  HarborGenerator sut;

  // Act.
  auto result = sut.GenerateHarbor(harborGenerationParameters);

  // Assert.
}
