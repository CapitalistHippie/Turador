#include "tura/harborfactory.h"

#include "csvparser.hpp"

#include <ctime>
#include <random>

using namespace tura;
using namespace tura::models;

static const char* const CARGO_PRICES_FILE_PATH = "assets/goederen prijzen.csv";
static const char* const CARGO_AMOUNTS_FILE_PATH = "assets/goederen hoeveelheid.csv";

static const int HARBORS_AMOUNT = 24;
static const int CARGO_TYPES_AMOUNT = 15;

Harbor HarborFactory::ConstructHarbor(const models::HarborStats& stats) const
{
  Harbor harbor;

  std::default_random_engine rngGenerator;
  rngGenerator.seed(time(0));

  strncpy(harbor.name, stats.harborName, sizeof(harbor.name));

  for (unsigned int i = 0; i < CARGO_TYPES_AMOUNT; ++i)
  {
    strncpy(harbor.goods[i].cargo.name, stats.cargoStats[i].cargoName, sizeof(harbor.goods[i].cargo.name));

    std::uniform_int_distribution<int> rngDistribution1(stats.cargoStats[i].priceMin, stats.cargoStats[i].priceMax);

    harbor.goods[i].price = rngDistribution1(rngGenerator);
  }

  return harbor;
}

HarborFactory::HarborFactory()
{
  CsvParser parser;
  parser.OpenFile(CARGO_PRICES_FILE_PATH);

  // Parse the first row which contains the cargo names.
  auto cargoNamesRow = parser.ParseNextRow();

  // First column is nothing. Ignore it.
  parser.IgnoreNextColumn(cargoNamesRow);

  // There are 15 types of cargo and 24 harbors.
  for (unsigned int i = 0; i < CARGO_TYPES_AMOUNT; ++i)
  {
    char cargoNameBuffer[64];
    parser.ParseNextColumn(cargoNamesRow, cargoNameBuffer, sizeof(cargoNameBuffer));

    // Write the cargo names to the harborcargostats models.
    for (unsigned int j = 0; j < GetAmountOfHarbors(); ++j)
    {
      strncpy(harborStats[j].cargoStats[i].cargoName, cargoNameBuffer, sizeof(harborStats[j].cargoStats[i].cargoName));
    }
  }

  // The following rows all start with the name of the harbor and then 'minimum price-maximum price'.
  // There are 24 of these. The same amount as the amount of harbors.
  for (unsigned int i = 0; i < GetAmountOfHarbors(); ++i)
  {
    auto row = parser.ParseNextRow();

    // Write the harbor name to the harbor stats as that hasn't been done yet.
    parser.ParseNextColumn(row, harborStats[i].harborName, sizeof(harborStats[i].harborName));

    // Parse the prices.
    for (unsigned int j = 0; j < CARGO_TYPES_AMOUNT; ++j)
    {
      char pricesBuffer[64];
      parser.ParseNextColumn(row, pricesBuffer, sizeof(pricesBuffer));

      auto pricesStream = std::stringstream(pricesBuffer);
      unsigned int priceMin = 0;
      pricesStream >> priceMin;

      // Ignore the '-'.
      pricesStream.ignore();

      unsigned int priceMax = 0;
      pricesStream >> priceMax;

      harborStats[i].cargoStats[j].priceMin = priceMin;
      harborStats[i].cargoStats[j].priceMax = priceMax;
    }
  }

  // And now for the cargo amounts.
  parser.OpenFile(CARGO_AMOUNTS_FILE_PATH);
  parser.IgnoreNextRow();

  for (unsigned int i = 0; i < GetAmountOfHarbors(); ++i)
  {
    auto row = parser.ParseNextRow();

    // Parse the amounts.
    for (unsigned int j = 0; j < CARGO_TYPES_AMOUNT; ++j)
    {
      char amountsBuffer[64];
      parser.ParseNextColumn(row, amountsBuffer, sizeof(amountsBuffer));

      auto amountsStream = std::stringstream(amountsBuffer);
      unsigned int amountMin = 0;
      amountsStream >> amountMin;

      // Ignore the '-'.
      amountsStream.ignore();

      unsigned int amountMax = 0;
      amountsStream >> amountMax;

      harborStats[i].cargoStats[j].amountMin = amountMin;
      harborStats[i].cargoStats[j].amountMax = amountMax;
    }
  }
}

unsigned int HarborFactory::GetAmountOfHarbors() const
{
  return HARBORS_AMOUNT;
}

Harbor HarborFactory::GetHarborByName(const char* const harborName) const
{
  for (unsigned int i = 0; i < GetAmountOfHarbors(); ++i)
  {
    if (strcmp(harborName, harborStats[i].harborName) == 0)
    {
      return ConstructHarbor(harborStats[i]);
    }
  }

  // TODO: Throw
}

Harbor HarborFactory::GetHarborByIndex(unsigned int index) const
{
  if (index >= GetAmountOfHarbors())
  {
    // TODO: Throw.
  }

  return ConstructHarbor(harborStats[index]);
}
