#include "tura/dal/repositories/harborgenerationparametersfilerepository.h"

#include <chrono>
#include <random>
#include <system_error>

#include "tura/error.h"
#include "tura/helpers/csvparser.hpp"

using namespace tura;
using namespace tura::helpers;
using namespace tura::domain::models;
using namespace tura::dal::repositories;

static const char* const CARGO_PRICES_FILE_PATH = "assets/goederen prijzen.csv";
static const char* const CARGO_AMOUNTS_FILE_PATH = "assets/goederen hoeveelheid.csv";

HarborGenerationParametersFileRepository::HarborGenerationParametersFileRepository()
{
  CsvParser parser;
  parser.OpenFile(CARGO_PRICES_FILE_PATH);

  // Parse the first row which contains the cargo names.
  CsvRow rowBuffer;
  parser.ParseNextRow(rowBuffer);

  // First column is nothing. Ignore it.
  rowBuffer.IgnoreNextColumn();

  helpers::Array<HarborCargoGenerationParameters, 32> cargoGenerationParametersBuffers;

  char cargoNameBuffer[64];
  while (rowBuffer.ParseNextColumn(cargoNameBuffer, sizeof(cargoNameBuffer)) != ParsingStatus::EndOfFile)
  {
    HarborCargoGenerationParameters cargoGenerationParametersBuffer;
    cargoGenerationParametersBuffer.cargoName = cargoNameBuffer;

    cargoGenerationParametersBuffers.Add(std::move(cargoGenerationParametersBuffer));
  }

  // The following rows all start with the name of the harbor and then 'minimum price-maximum price'. Wer're also now
  // parsing the harbors so we add the previously parsed cargo generation parameters on the harbor.
  while (parser.ParseNextRow(rowBuffer) != ParsingStatus::EndOfFile)
  {
    HarborGenerationParameters harborGenerationParametersBuffer;
    harborGenerationParametersBuffer.cargoGenerationParameters = cargoGenerationParametersBuffers;

    // Write the harbor name to the harbor generation parameters as that hasn't been done yet.
    rowBuffer.ParseNextColumn(harborGenerationParametersBuffer.harborName.array,
                              harborGenerationParametersBuffer.harborName.MaxLength());

    // Parse the prices.
    for (auto& cargoGenerationParametersBuffer : harborGenerationParametersBuffer.cargoGenerationParameters)
    {
      char pricesBuffer[64];
      rowBuffer.ParseNextColumn(pricesBuffer, sizeof(pricesBuffer));

      auto pricesStream = std::stringstream(pricesBuffer);
      unsigned int priceMin = 0;
      pricesStream >> priceMin;

      // Ignore the '-'.
      pricesStream.ignore();

      unsigned int priceMax = 0;
      pricesStream >> priceMax;

      cargoGenerationParametersBuffer.priceMin = priceMin;
      cargoGenerationParametersBuffer.priceMax = priceMax;
    }

    harborGenerationParameters.Add(harborGenerationParametersBuffer);
  }

  // And now for the cargo amounts.
  // TODO: We're atm assuming the harbors and cargo parameters are in the same order as in the previous file. Should
  // revise this.
  parser.OpenFile(CARGO_AMOUNTS_FILE_PATH);
  parser.IgnoreNextRow();

  for (auto& harborGenerationParametersBuffer : harborGenerationParameters)
  {
    parser.ParseNextRow(rowBuffer);

    // Ignore the first column which has the harbor name.
    rowBuffer.IgnoreNextColumn();

    // Parse the amounts.
    for (auto& cargoGenerationParametersBuffer : harborGenerationParametersBuffer.cargoGenerationParameters)
    {
      char amountsBuffer[64];
      rowBuffer.ParseNextColumn(amountsBuffer, sizeof(amountsBuffer));

      auto amountsStream = std::stringstream(amountsBuffer);
      unsigned int amountMin = 0;
      amountsStream >> amountMin;

      // Ignore the '-'.
      amountsStream.ignore();

      unsigned int amountMax = 0;
      amountsStream >> amountMax;

      cargoGenerationParametersBuffer.amountMin = amountMin;
      cargoGenerationParametersBuffer.amountMax = amountMax;
    }
  }
}

unsigned int HarborGenerationParametersFileRepository::GetHarborGenerationParametersCount() const
{
  return harborGenerationParameters.size();
}

HarborGenerationParameters HarborGenerationParametersFileRepository::GetHarborGenerationParametersByName(
  const char* const name) const
{
  if (name == nullptr)
  {
    throw std::system_error(std::make_error_code(Error::InvalidArgument), "Argument 'name' can not be null.");
  }

  for (unsigned int i = 0; i < GetHarborGenerationParametersCount(); ++i)
  {
    if (name == harborGenerationParameters[i].harborName)
    {
      return harborGenerationParameters[i];
    }
  }

  throw std::system_error(std::make_error_code(Error::UnknownHarborGenerationParameters));
}

HarborGenerationParameters HarborGenerationParametersFileRepository::GetHarborGenerationParametersByIndex(
  unsigned int index) const
{
  if (index >= GetHarborGenerationParametersCount())
  {
    throw std::system_error(std::make_error_code(Error::OutOfRange), "Index is out of range.");
  }

  return harborGenerationParameters[index];
}

HarborGenerationParameters HarborGenerationParametersFileRepository::GetRandomHarborGenerationParameters() const
{
  std::default_random_engine rng;
  auto seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());
  rng.seed(seed);
  std::uniform_int_distribution<int> rngDistribution1(0, GetHarborGenerationParametersCount() - 1);

  return harborGenerationParameters[rngDistribution1(rng)];
}
