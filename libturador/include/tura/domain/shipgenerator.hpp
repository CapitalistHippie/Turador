#ifndef LIBTURADOR_TURA_DOMAIN_SHIPGENERATOR_HPP_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_SHIPGENERATOR_HPP_INCLUDED

#include <chrono>
#include <random>

#include "tura/dal/repositories/shiptypefilerepository.h"
#include "tura/dal/repositories/shiptyperepositoryinterface.h"
#include "tura/domain/models/cannonclass.h"
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
    ship.hitPoints = shipType.hitPointsMax;

    return ship;
  }

  models::Ship GenerateRandomEnemyShip() const
  {
    std::default_random_engine rng;
    auto seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());
    rng.seed(seed);

    models::Ship enemyShip = GenerateShipByShipType(shipTypeRepository->GetRandomShipType());

    std::uniform_int_distribution<unsigned int> cannonCountDist(1, enemyShip.shipType.cannonSpaceMax);
    auto enemyShipCannonCount = cannonCountDist(rng);

    std::discrete_distribution<> cannonClassDist({ 1.0, 1.0, 1.0 });

    for (unsigned int i = 0; i < enemyShipCannonCount; ++i)
    {
      auto cannonClass = static_cast<models::CannonClass>(cannonClassDist(rng));

      models::Cannon cannon;
      cannon.cannonClass = cannonClass;

      enemyShip.cannons.Add(cannon);
    }

    return enemyShip;
  }
};
}
}

#endif // LIBTURADOR_TURA_DOMAIN_SHIPGENERATOR_HPP_INCLUDED
