#ifndef LIBTURADOR_TURA_DOMAIN_SHIPGENERATORINTERFACE_H_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_SHIPGENERATORINTERFACE_H_INCLUDED

#include "tura/domain/models/ship.h"
#include "tura/domain/models/shiptype.h"

namespace tura
{
namespace domain
{
class ShipGeneratorInterface
{
public:
  virtual ~ShipGeneratorInterface() = default;

  virtual models::Ship GenerateShipByShipTypeName(const char* const shipTypeName) const = 0;
  virtual models::Ship GenerateShipByShipType(const models::ShipType& shipType) const = 0;
  virtual models::Ship GenerateRandomEnemyShip() const = 0;
};
}
}

#endif // LIBTURADOR_TURA_DOMAIN_SHIPGENERATORINTERFACE_H_INCLUDED
