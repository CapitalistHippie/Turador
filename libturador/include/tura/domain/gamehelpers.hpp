#ifndef LIBTURADOR_TURA_DOMAIN_GAMEHELPERS_H_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_GAMEHELPERS_H_INCLUDED

#include <chrono>
#include <random>

#include "tura/domain/models/cannon.h"
#include "tura/domain/models/cannonclass.h"
#include "tura/domain/models/ship.h"

namespace tura
{
namespace domain
{
inline unsigned int GetShipUsedCargoSpace(const models::Ship& ship)
{
  unsigned int usedCargoSpace = 0;

  for (const auto& cargo : ship.goods)
  {
    usedCargoSpace += cargo.amount;
  }

  return usedCargoSpace;
}

inline unsigned int CalculateCannonsDamage(const helpers::Array<models::Cannon, 64>& cannons)
{
  std::default_random_engine rng;
  auto seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());
  rng.seed(seed);

  std::uniform_int_distribution<unsigned int> lightCannonDamageDist(0, 2);
  std::uniform_int_distribution<unsigned int> mediumCannonDamageDist(0, 4);
  std::uniform_int_distribution<unsigned int> heavyCannonDamageDist(0, 6);

  unsigned int damage = 0;

  for (const auto& cannon : cannons)
  {
    switch (cannon.cannonClass)
    {
      case models::CannonClass::Light:
        damage += lightCannonDamageDist(rng);
        break;
      case models::CannonClass::Medium:
        damage += mediumCannonDamageDist(rng);
        break;
      case models::CannonClass::Heavy:
        damage += heavyCannonDamageDist(rng);
        break;
    }
  }

  return damage;
}
}
}

#endif // LIBTURADOR_TURA_DOMAIN_GAMEHELPERS_H_INCLUDED
