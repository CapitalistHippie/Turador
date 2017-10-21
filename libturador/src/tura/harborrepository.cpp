#include "tura/harborrepository.h"

#include "csvparser.hpp"

using namespace tura;
using namespace tura::models;

static const char* const CARGO_PRICES_FILE_PATH = "assets/goederen prijzen.csv";
static const char* const CARGO_AMOUNTS_FILE_PATH = "assets/goederen hoeveelheid.csv";

static const int HARBORS_AMOUNT = 24;
static const int CARGO_TYPES_AMOUNT = 15;

HarborRepository::HarborRepository()
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

    // Write the cargo names to the harborcargo models.
    for (unsigned int j = 0; j < HARBORS_AMOUNT; ++j)
    {
      strncpy(harbors[j].goods[i].cargo.name, cargoNameBuffer, sizeof(harbors[j].goods[i].cargo.name));
    }
  }

  // The following rows all start with the name of the harbor and then 'minimum price-maximum price'.
  // There are 24 of these. The same amount as the amount of harbors.
  for (unsigned int i = 0; i < HARBORS_AMOUNT; ++i)
  {
    auto row = parser.ParseNextRow();

    // Write the harbor name to the harbor as that hasn't been done yet.
    parser.ParseNextColumn(row, harbors[i].name, sizeof(harbors[i].name));
  }
}

const Harbor* HarborRepository::GetHarbors() const
{
  return &harbors[0];
}

unsigned int HarborRepository::GetAmountOfHarbors() const
{
  return 24;
}

Harbor HarborRepository::GetHarborByName(const char* const harborName) const
{
  for (unsigned int i = 0; i < GetAmountOfHarbors(); ++i)
  {
    if (strcmp(harborName, harbors[i].name))
    {
      return harbors[i];
    }
  }

  // TODO: Throw
}
