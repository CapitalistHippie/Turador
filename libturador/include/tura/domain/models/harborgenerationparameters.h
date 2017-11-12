#ifndef LIBTURADOR_TURA_DOMAIN_MODELS_HARBORGENERATIONPARAMETERS_H_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_MODELS_HARBORGENERATIONPARAMETERS_H_INCLUDED

#include "tura/domain/models/harborcargogenerationparameters.h"
#include "tura/helpers/array.hpp"
#include "tura/helpers/chararray.hpp"

namespace tura
{
namespace domain
{
namespace models
{
struct HarborGenerationParameters
{
  helpers::CharArray<64> harborName;
  helpers::Array<HarborCargoGenerationParameters, 32> cargoGenerationParameters;
};
}
}
}

#endif // LIBTURADOR_TURA_DOMAIN_MODELS_HARBORGENERATIONPARAMETERS_H_INCLUDED
