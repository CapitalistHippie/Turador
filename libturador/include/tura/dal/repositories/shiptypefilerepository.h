#ifndef LIBTURADOR_TURA_DAL_REPOSITORIES_SHIPTYPEFILEREPOSITORY_H_INCLUDED
#define LIBTURADOR_TURA_DAL_REPOSITORIES_SHIPTYPEFILEREPOSITORY_H_INCLUDED

#include "tura/dal/repositories/shiptyperepositoryinterface.h"
#include "tura/domain/models/shiptype.h"

namespace tura
{
namespace dal
{
namespace repositories
{
class ShipTypeFileRepository : public ShipTypeRepositoryInterface
{
private:
  static const int SHIP_TYPE_COUNT = 13;

  domain::models::ShipType shipTypes[SHIP_TYPE_COUNT];

public:
  ShipTypeFileRepository();

  unsigned int GetShipTypeCount() const override;
  domain::models::ShipType GetShipTypeByName(const char* const shipTypeName) const override;
};
}
}
}

#endif // LIBTURADOR_TURA_DAL_REPOSITORIES_SHIPTYPEFILEREPOSITORY_H_INCLUDED
