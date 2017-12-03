#include "tura/dal/repositories/shiptypefilerepository.h"

#include <cstring>
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

  CsvRow rowBuffer;
  while (parser.ParseNextRow(rowBuffer) != ParsingStatus::EndOfFile)
  {
    ShipType shipType;
    shipType.sizeClass = domain::models::ShipSizeClass::Normal;
    shipType.weightClass = domain::models::ShipWeightClass::Normal;

    // Parse the easy stuff.
    rowBuffer.ParseNextColumn(shipType.name.array, shipType.name.MaxLength());
    rowBuffer >> shipType.price;
    rowBuffer >> shipType.cargoSpaceMax;
    rowBuffer >> shipType.cannonSpaceMax;
    rowBuffer >> shipType.hitPointsMax;

    // Now for the details.
    char detailsBuffer[64];
    rowBuffer.ParseNextColumn(detailsBuffer, sizeof(detailsBuffer));
    auto detailsStream = std::stringstream(detailsBuffer);

    while (!detailsStream.eof())
    {
      char detailBuffer[64];
      detailsStream.getline(detailBuffer, sizeof(detailBuffer), ',');

      if (strcmp(detailBuffer, "klein") == 0)
      {
        shipType.sizeClass = ShipSizeClass::Small;
      }
      else if (strcmp(detailBuffer, "licht") == 0)
      {
        shipType.weightClass = ShipWeightClass::Light;
      }
      else if (strcmp(detailBuffer, "log") == 0)
      {
        shipType.weightClass = ShipWeightClass::Heavy;
      }
    }

    shipTypes.Add(shipType);
  }
}

unsigned int ShipTypeFileRepository::GetShipTypeCount() const
{
  return shipTypes.size();
}

ShipType ShipTypeFileRepository::GetShipTypeByName(const char* const shipTypeName) const
{
  if (shipTypeName == nullptr)
  {
    throw std::system_error(std::make_error_code(Error::InvalidArgument), "Argument 'name' may not be null.");
  }

  for (unsigned int i = 0; i < GetShipTypeCount(); ++i)
  {
    if (shipTypeName == shipTypes[i].name)
    {
      return shipTypes[i];
    }
  }

  throw std::system_error(std::make_error_code(Error::UnknownShipType));
}

ShipType ShipTypeFileRepository::GetShipTypeByIndex(unsigned int index) const
{
  return shipTypes[index];
}
