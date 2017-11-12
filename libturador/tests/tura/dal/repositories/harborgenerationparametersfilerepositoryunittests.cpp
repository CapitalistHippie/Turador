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

    EXPECT_STRNE("", harborGenerationParameters.harborName.array);

    for (const auto& cargoGenerationParameters : harborGenerationParameters.cargoGenerationParameters)
    {
      EXPECT_STRNE("", cargoGenerationParameters.cargoName.array);

      EXPECT_NE(0, cargoGenerationParameters.priceMin);
      EXPECT_LE(cargoGenerationParameters.priceMin, cargoGenerationParameters.priceMax);
      EXPECT_LE(cargoGenerationParameters.amountMin, cargoGenerationParameters.amountMax);
    }
  }
}
