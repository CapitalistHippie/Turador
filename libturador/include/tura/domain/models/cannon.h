#ifndef LIBTURADOR_TURA_DOMAIN_MODELS_CANNON_H_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_MODELS_CANNON_H_INCLUDED

#include "tura/domain/models/cannonclass.h"

namespace tura
{
namespace domain
{
namespace models
{
struct Cannon
{
  CannonClass cannonClass = CannonClass::Medium;
};
}
}
}

#endif // LIBTURADOR_TURA_DOMAIN_MODELS_CANNON_H_INCLUDED
