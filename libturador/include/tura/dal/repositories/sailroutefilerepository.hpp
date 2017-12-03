#ifndef LIBTURADOR_TURA_DAL_REPOSITORIES_SAILROUTEFILEREPOSITORY_H_INCLUDED
#define LIBTURADOR_TURA_DAL_REPOSITORIES_SAILROUTEFILEREPOSITORY_H_INCLUDED

#include "tura/dal/repositories/sailrouterepository.h"
#include "tura/domain/models/sailroute.h"
#include "tura/helpers/array.hpp"
#include "tura/helpers/chararray.hpp"
#include "tura/helpers/csvparser.hpp"

namespace tura
{
namespace dal
{
namespace repositories
{
class SailRouteFileRepository : public SailRouteRepository
{
private:
  helpers::Array<domain::models::SailRoute, 1024> sailRoutes;

public:
  SailRouteFileRepository()
  {
    helpers::CsvParser parser;
    parser.OpenFile("assets/afstanden tussen steden.csv");

    helpers::Array<helpers::CharArray<64>, 64> harborNameFromBuffers;
    helpers::CsvRow rowBuffer;

    parser.ParseNextRow(rowBuffer);
    rowBuffer.IgnoreNextColumn();

    char harborNameFromBufferBuffer[64];

    while (rowBuffer.ParseNextColumn(harborNameFromBufferBuffer, 64) != helpers::ParsingStatus::EndOfFile)
    {
      harborNameFromBuffers.Emplace(harborNameFromBufferBuffer);
    }

    harborNameFromBuffers.Emplace(harborNameFromBufferBuffer);

    while (parser.ParseNextRow(rowBuffer) != helpers::ParsingStatus::EndOfFile)
    {
      helpers::CharArray<64> harborNameToBuffer;

      rowBuffer.ParseNextColumn(harborNameToBuffer.array, harborNameToBuffer.MaxLength());

      for (const auto& harborNameFromBuffer : harborNameFromBuffers)
      {
        if (harborNameFromBuffer == harborNameToBuffer)
        {
          rowBuffer.IgnoreNextColumn();
          continue;
        }

        domain::models::SailRoute sailRoute;
        sailRoute.fromHarborName = harborNameFromBuffer;
        sailRoute.toHarborName = harborNameToBuffer;
        rowBuffer >> sailRoute.distanceInTurns;

        sailRoutes.Add(std::move(sailRoute));
      }
    }
  }

  const helpers::Array<domain::models::SailRoute, 1024>& GetSailRoutes() const override { return sailRoutes; }

  helpers::Array<domain::models::SailRoute, 64> GetSailRoutesFromHarbor(
    const helpers::CharArray<64>& harborName) const override
  {
    helpers::Array<domain::models::SailRoute, 64> sailRoutesFromHarbor;

    for (const auto& sailRoute : sailRoutes)
    {
      if (sailRoute.fromHarborName == harborName)
      {
        sailRoutesFromHarbor.Add(sailRoute);
      }
    }

    return sailRoutesFromHarbor;
  }
};
}
}
}

#endif // LIBTURADOR_TURA_DAL_REPOSITORIES_SAILROUTEFILEREPOSITORY_H_INCLUDED
