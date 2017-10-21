#ifndef LIBTURADOR_TURA_MODELS_HARBORCARGO_H_INCLUDED
#define LIBTURADOR_TURA_MODELS_HARBORCARGO_H_INCLUDED

#include "cargo.h"

namespace tura
{
namespace models
{
struct HarborCargo
{
  Cargo cargo;
  unsigned int price;
};
}
}

#endif // LIBTURADOR_TURA_MODELS_HARBORCARGO_H_INCLUDED
