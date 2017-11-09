#ifndef LIBTURADOR_TURA_DOMAIN_MODELS_HARBORCARGOGENERATIONPARAMETERS_H_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_MODELS_HARBORCARGOGENERATIONPARAMETERS_H_INCLUDED

#include "tura/helpers/chararray.hpp"

namespace tura
{
namespace domain
{
namespace models
{
struct HarborCargoGenerationParameters
{
  helpers::CharArray<64> cargoName;

  unsigned int priceMin = 0;
  unsigned int priceMax = 0;

  unsigned int amountMin = 0;
  unsigned int amountMax = 0;
};
}
}
}

#endif // LIBTURADOR_TURA_DOMAIN_MODELS_HARBORCARGOGENERATIONPARAMETERS_H_INCLUDED
