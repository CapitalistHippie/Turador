#ifndef LIBTURADOR_TURA_DOMAIN_MODELS_CANNONTYPE_H_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_MODELS_CANNONTYPE_H_INCLUDED

#include "tura/domain/models/cannonclass.h"

namespace tura
{
namespace domain
{
namespace models
{
struct CannonType
{
  CannonClass cannonClass = CannonClass::Medium;
  unsigned int price = 0;
};
}
}
}

#endif // LIBTURADOR_TURA_DOMAIN_MODELS_CANNONTYPE_H_INCLUDED
