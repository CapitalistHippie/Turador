#include "tura/dal/repositories/shiptypefilerepository.h"

#include <stdexcept>
#include <system_error>

#include "tura/error.h"
#include "tura/helpers/csvparser.hpp"

using namespace tura;
using namespace tura::helpers;
using namespace tura::domain::models;
using namespace tura::dal::repositories;

static const char* const SHIPS_CSV_FILE_PATH = "assets/schepen.csv";

ShipTypeFileRepository::ShipTypeFileRepository()
{
  CsvParser parser;
  parser.OpenFile(SHIPS_CSV_FILE_PATH);

  // First row is just headers. Ignore it.
  parser.IgnoreNextRow();

  for (unsigned int i = 0; i < GetShipTypeCount(); ++i)
  {
    auto row = parser.ParseNextRow();

    // Parse the easy stuff.
    row.ParseNextColumn(shipTypes[i].name.array, shipTypes[i].name.MaxLength());
    row >> shipTypes[i].price;
    row >> shipTypes[i].cargoSpaceMax;
    row >> shipTypes[i].cannonSpaceMax;
    row >> shipTypes[i].hitPointsMax;

    // Now for the details.
    char detailsBuffer[64];
    row.ParseNextColumn(detailsBuffer, sizeof(detailsBuffer));
    auto detailsStream = std::stringstream(detailsBuffer);

    while (!detailsStream.eof())
    {
      char detailBuffer[64];
      detailsStream.getline(detailBuffer, sizeof(detailBuffer), ',');

      if (strcmp(detailBuffer, "klein") == 0)
      {
        shipTypes[i].sizeClass = ShipSizeClass::Small;
      }
      else if (strcmp(detailBuffer, "licht") == 0)
      {
        shipTypes[i].weightClass = ShipWeightClass::Light;
      }
      else if (strcmp(detailBuffer, "log") == 0)
      {
        shipTypes[i].weightClass = ShipWeightClass::Heavy;
      }
    }
  }
}

unsigned int ShipTypeFileRepository::GetShipTypeCount() const
{
  return SHIP_TYPE_COUNT;
}

ShipType ShipTypeFileRepository::GetShipTypeByName(const char* const shipTypeName) const
{
  if (shipTypeName == nullptr)
  {
    throw std::invalid_argument("Argument 'name' may not be null.");
  }

  for (unsigned int i = 0; i < GetShipTypeCount(); ++i)
  {
    if (shipTypeName == shipTypes[i].name)
    {
      return shipTypes[i];
    }
  }

  throw std::system_error(std::make_error_code(Error::UnknownEntityName));
}
