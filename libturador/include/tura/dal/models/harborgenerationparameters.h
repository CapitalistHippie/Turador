#ifndef LIBTURADOR_TURA_DAL_MODELS_HARBORGENERATIONPARAMETERS_H_INCLUDED
#define LIBTURADOR_TURA_DAL_MODELS_HARBORGENERATIONPARAMETERS_H_INCLUDED

#include "tura/dal/models/harborcargogenerationparameters.h"

namespace tura
{
namespace dal
{
namespace models
{
struct HarborGenerationParameters
{
  char harborName[64] = "";
  HarborCargoGenerationParameters cargoGenerationParameters[15];
};
}
}
}

#endif // LIBTURADOR_TURA_DAL_MODELS_HARBORGENERATIONPARAMETERS_H_INCLUDED
