#ifndef LIBTURADOR_TURA_DOMAIN_MODELS_SAILROUTE_H_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_MODELS_SAILROUTE_H_INCLUDED

#include "tura/helpers/chararray.hpp"

namespace tura
{
namespace domain
{
namespace models
{
struct SailRoute
{
  helpers::CharArray<64> fromHarborName;
  helpers::CharArray<64> toHarborName;
  unsigned int distanceInTurns = 0;
};
}
}
}

#endif // LIBTURADOR_TURA_DOMAIN_MODELS_SAILROUTE_H_INCLUDED
