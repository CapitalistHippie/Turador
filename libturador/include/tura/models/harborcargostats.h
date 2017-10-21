#ifndef LIBTURADOR_TURA_MODELS_HARBORCARGOSTATS_H_INCLUDED
#define LIBTURADOR_TURA_MODELS_HARBORCARGOSTATS_H_INCLUDED

namespace tura
{
namespace models
{
struct HarborCargoStats
{
  char cargoName[64] = "";

  unsigned int priceMin = 0;
  unsigned int priceMax = 0;

  unsigned int amountMin = 0;
  unsigned int amountMax = 0;
};
}
}

#endif // LIBTURADOR_TURA_MODELS_HARBORCARGOSTATS_H_INCLUDED
