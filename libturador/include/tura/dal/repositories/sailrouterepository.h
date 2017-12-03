#ifndef LIBTURADOR_TURA_DAL_REPOSITORIES_SAILROUTEREPOSITORY_H_INCLUDED
#define LIBTURADOR_TURA_DAL_REPOSITORIES_SAILROUTEREPOSITORY_H_INCLUDED

#include "tura/domain/models/sailroute.h"
#include "tura/helpers/array.hpp"
#include "tura/helpers/chararray.hpp"

namespace tura
{
namespace dal
{
namespace repositories
{
class SailRouteRepository
{
public:
  virtual ~SailRouteRepository() = default;
  virtual const helpers::Array<domain::models::SailRoute, 1024>& GetSailRoutes() const = 0;
  virtual helpers::Array<domain::models::SailRoute, 64> GetSailRoutesFromHarbor(
    const helpers::CharArray<64>& harborName) const = 0;
};
}
}
}

#endif // LIBTURADOR_TURA_DAL_REPOSITORIES_SAILROUTEREPOSITORY_H_INCLUDED
