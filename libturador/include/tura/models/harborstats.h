#ifndef LIBTURADOR_TURA_MODELS_HARBORSTATS_H_INCLUDED
#define LIBTURADOR_TURA_MODELS_HARBORSTATS_H_INCLUDED

#include "harborcargostats.h"

namespace tura
{
namespace models
{
struct HarborStats
{
  char harborName[64] = "";
  HarborCargoStats cargoStats[15];
};
}
}

#endif // LIBTURADOR_TURA_MODELS_HARBORSTATS_H_INCLUDED
