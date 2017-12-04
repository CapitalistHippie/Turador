#ifndef LIBTURADOR_TURA_DAL_REPOSITORIES_SHIPTYPEFILEREPOSITORY_H_INCLUDED
#define LIBTURADOR_TURA_DAL_REPOSITORIES_SHIPTYPEFILEREPOSITORY_H_INCLUDED

#include "tura/dal/repositories/shiptyperepositoryinterface.h"
#include "tura/domain/models/shiptype.h"
#include "tura/helpers/array.hpp"

namespace tura
{
namespace dal
{
namespace repositories
{
class ShipTypeFileRepository : public ShipTypeRepositoryInterface
{
private:
  helpers::Array<domain::models::ShipType, 32> shipTypes;

public:
  ShipTypeFileRepository();

  unsigned int GetShipTypeCount() const override;
  domain::models::ShipType GetShipTypeByName(const char* const shipTypeName) const override;
  domain::models::ShipType GetShipTypeByIndex(unsigned int index) const override;
  domain::models::ShipType GetRandomShipType() const override;
};
}
}
}

#endif // LIBTURADOR_TURA_DAL_REPOSITORIES_SHIPTYPEFILEREPOSITORY_H_INCLUDED
