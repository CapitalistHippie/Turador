#ifndef LIBTURADOR_TURA_DOMAIN_MODELS_SAILTRIP_H_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_MODELS_SAILTRIP_H_INCLUDED

#include "tura/domain/models/sailroute.h"
#include "tura/domain/models/windstrength.h"

namespace tura
{
namespace domain
{
namespace models
{
struct SailTrip
{
  SailRoute route;
  int turnsSailed = 0;

  WindStrength lastWindStrength = WindStrength::Unknown;
};
}
}
}

#endif // LIBTURADOR_TURA_DOMAIN_MODELS_SAILTRIP_H_INCLUDED
