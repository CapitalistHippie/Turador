#ifndef LIBTURADOR_TURA_DOMAIN_SHIPGENERATOR_HPP_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_SHIPGENERATOR_HPP_INCLUDED

#include "tura/dal/repositories/shiptypefilerepository.h"
#include "tura/dal/repositories/shiptyperepositoryinterface.h"
#include "tura/domain/models/ship.h"
#include "tura/domain/models/shiptype.h"
#include "tura/domain/shipgeneratorinterface.h"

namespace tura
{
namespace domain
{
class ShipGenerator : public ShipGeneratorInterface
{
private:
  dal::repositories::ShipTypeFileRepository shipTypeRepositoryInstance;
  dal::repositories::ShipTypeRepositoryInterface* shipTypeRepository;

public:
  ShipGenerator()
    : shipTypeRepository(&shipTypeRepositoryInstance)
  {
  }

  ShipGenerator(dal::repositories::ShipTypeRepositoryInterface* shipTypeRepository)
    : shipTypeRepository(shipTypeRepository)
  {
  }

  models::Ship GenerateShipByShipTypeName(const char* const shipTypeName) const
  {
    return GenerateShipByShipType(shipTypeRepository->GetShipTypeByName(shipTypeName));
  }

  models::Ship GenerateShipByShipType(const models::ShipType& shipType) const
  {
    models::Ship ship;
    ship.shipType = shipType;
    ship.hitpoints = shipType.hitPointsMax;

    return ship;
  }
};
}
}

#endif // LIBTURADOR_TURA_DOMAIN_SHIPGENERATOR_HPP_INCLUDED
