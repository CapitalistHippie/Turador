#include <gtest/gtest.h>

#include <tura/dal/repositories/harborgenerationparametersfilerepository.h>

using namespace testing;

TEST(HarborGenerationParametersFileRepository, GetHarborGenerationParametersCount_Returns24)
{
  // Arrange.
  tura::dal::repositories::HarborGenerationParametersFileRepository sut;

  // Act.

  // Assert.
  EXPECT_EQ(24, sut.GetHarborGenerationParametersCount());
}

TEST(HarborGenerationParametersFileRepository, GetHarbors_ReturnsValidHarborGenerationParameters)
{
  // Arrange.
  tura::dal::repositories::HarborGenerationParametersFileRepository sut;

  // Act.

  // Assert.
  for (unsigned int i = 0; i < sut.GetHarborGenerationParametersCount(); ++i)
  {
    auto harborGenerationParameters = sut.GetHarborGenerationParametersByIndex(i);

    EXPECT_STRNE("", harborGenerationParameters.harborName);

    for (unsigned int j = 0; j < 15; ++j)
    {
      EXPECT_STRNE("", harborGenerationParameters.cargoGenerationParameters[j].cargoName);

      EXPECT_NE(0, harborGenerationParameters.cargoGenerationParameters[j].priceMin);
      EXPECT_LE(harborGenerationParameters.cargoGenerationParameters[j].priceMin,
                harborGenerationParameters.cargoGenerationParameters[j].priceMax);
      EXPECT_LE(harborGenerationParameters.cargoGenerationParameters[j].amountMin,
                harborGenerationParameters.cargoGenerationParameters[j].amountMax);
    }
  }
}