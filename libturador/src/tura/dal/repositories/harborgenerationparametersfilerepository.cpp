#include "tura/dal/repositories/harborgenerationparametersfilerepository.h"

#include <ctime>
#include <random>
#include <stdexcept>
#include <system_error>

#include "tura/error.h"
#include "tura/helpers/csvparser.hpp"

using namespace tura;
using namespace tura::helpers;
using namespace tura::domain::models;
using namespace tura::dal::repositories;

static const char* const CARGO_PRICES_FILE_PATH = "assets/goederen prijzen.csv";
static const char* const CARGO_AMOUNTS_FILE_PATH = "assets/goederen hoeveelheid.csv";

static const int CARGO_TYPE_COUNT = 15;

HarborGenerationParametersFileRepository::HarborGenerationParametersFileRepository()
{
  CsvParser parser;
  parser.OpenFile(CARGO_PRICES_FILE_PATH);

  // Parse the first row which contains the cargo names.
  auto cargoNamesRow = parser.ParseNextRow();

  // First column is nothing. Ignore it.
  cargoNamesRow.IgnoreNextColumn();

  // There are 15 types of cargo and 24 harbors.
  for (unsigned int i = 0; i < CARGO_TYPE_COUNT; ++i)
  {
    char cargoNameBuffer[64];
    cargoNamesRow.ParseNextColumn(cargoNameBuffer, sizeof(cargoNameBuffer));

    // Write the cargo names to the models.
    for (unsigned int j = 0; j < GetHarborGenerationParametersCount(); ++j)
    {
      strncpy(harborGenerationParameters[j].cargoGenerationParameters[i].cargoName,
              cargoNameBuffer,
              sizeof(harborGenerationParameters[j].cargoGenerationParameters[i].cargoName));
    }
  }

  // The following rows all start with the name of the harbor and then 'minimum price-maximum price'.
  // There are 24 of these. The same amount as the amount of harbors.
  for (unsigned int i = 0; i < GetHarborGenerationParametersCount(); ++i)
  {
    auto row = parser.ParseNextRow();

    // Write the harbor name to the harbor generation parameters as that hasn't been done yet.
    row.ParseNextColumn(harborGenerationParameters[i].harborName, sizeof(harborGenerationParameters[i].harborName));

    // Parse the prices.
    for (unsigned int j = 0; j < CARGO_TYPE_COUNT; ++j)
    {
      char pricesBuffer[64];
      row.ParseNextColumn(pricesBuffer, sizeof(pricesBuffer));

      auto pricesStream = std::stringstream(pricesBuffer);
      unsigned int priceMin = 0;
      pricesStream >> priceMin;

      // Ignore the '-'.
      pricesStream.ignore();

      unsigned int priceMax = 0;
      pricesStream >> priceMax;

      harborGenerationParameters[i].cargoGenerationParameters[j].priceMin = priceMin;
      harborGenerationParameters[i].cargoGenerationParameters[j].priceMax = priceMax;
    }
  }

  // And now for the cargo amounts.
  parser.OpenFile(CARGO_AMOUNTS_FILE_PATH);
  parser.IgnoreNextRow();

  for (unsigned int i = 0; i < GetHarborGenerationParametersCount(); ++i)
  {
    auto row = parser.ParseNextRow();

    // Parse the amounts.
    for (unsigned int j = 0; j < CARGO_TYPE_COUNT; ++j)
    {
      char amountsBuffer[64];
      row.ParseNextColumn(amountsBuffer, sizeof(amountsBuffer));

      auto amountsStream = std::stringstream(amountsBuffer);
      unsigned int amountMin = 0;
      amountsStream >> amountMin;

      // Ignore the '-'.
      amountsStream.ignore();

      unsigned int amountMax = 0;
      amountsStream >> amountMax;

      harborGenerationParameters[i].cargoGenerationParameters[j].amountMin = amountMin;
      harborGenerationParameters[i].cargoGenerationParameters[j].amountMax = amountMax;
    }
  }
}

unsigned int HarborGenerationParametersFileRepository::GetHarborGenerationParametersCount() const
{
  return HARBOR_GENERATION_PARAMETERS_COUNT;
}

HarborGenerationParameters HarborGenerationParametersFileRepository::GetHarborGenerationParametersByName(
  const char* const name) const
{
  if (name == nullptr)
  {
    throw std::invalid_argument("Argument 'name' may not be null.");
  }

  for (unsigned int i = 0; i < GetHarborGenerationParametersCount(); ++i)
  {
    if (strcmp(name, harborGenerationParameters[i].harborName) == 0)
    {
      return harborGenerationParameters[i];
    }
  }

  throw std::system_error(std::make_error_code(Error::UnknownEntityName));
}

HarborGenerationParameters HarborGenerationParametersFileRepository::GetHarborGenerationParametersByIndex(
  unsigned int index) const
{
  if (index >= GetHarborGenerationParametersCount())
  {
    throw std::out_of_range("Index out of range.");
  }

  return harborGenerationParameters[index];
}

HarborGenerationParameters HarborGenerationParametersFileRepository::GetRandomHarborGenerationParameters() const
{
  std::default_random_engine rng;
  rng.seed(time(0));
  std::uniform_int_distribution<int> rngDistribution1(0, GetHarborGenerationParametersCount());

  return harborGenerationParameters[rngDistribution1(rng)];
}
