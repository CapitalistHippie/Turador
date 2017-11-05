#ifndef LIBTURADOR_TURA_DOMAIN_MODELS_HARBORGENERATIONPARAMETERS_H_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_MODELS_HARBORGENERATIONPARAMETERS_H_INCLUDED

#include "tura/domain/models/harborcargogenerationparameters.h"

namespace tura
{
namespace domain
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

#endif // LIBTURADOR_TURA_DOMAIN_MODELS_HARBORGENERATIONPARAMETERS_H_INCLUDED
