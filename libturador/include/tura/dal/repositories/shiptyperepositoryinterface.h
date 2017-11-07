#ifndef LIBTURADOR_TURA_DAL_REPOSITORIES_SHIPTYPEREPOSITORYINTERFACE_H_INCLUDED
#define LIBTURADOR_TURA_DAL_REPOSITORIES_SHIPTYPEREPOSITORYINTERFACE_H_INCLUDED

#include "tura/domain/models/shiptype.h"

namespace tura
{
namespace dal
{
namespace repositories
{
class ShipTypeRepositoryInterface
{
public:
  virtual ~ShipTypeRepositoryInterface() = default;
  virtual unsigned int GetShipTypeCount() const = 0;
  virtual domain::models::ShipType GetShipTypeByName(const char* const shipTypeName) const = 0;
};
}
}
}

#endif // LIBTURADOR_TURA_DAL_REPOSITORIES_SHIPTYPEREPOSITORYINTERFACE_H_INCLUDED
