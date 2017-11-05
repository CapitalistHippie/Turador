#ifndef LIBTURADOR_TURA_DOMAIN_MODELS_HARBORCARGO_H_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_MODELS_HARBORCARGO_H_INCLUDED

#include "tura/domain/models/cargo.h"

namespace tura
{
namespace domain
{
namespace models
{
struct HarborCargo
{
  Cargo cargo;
  unsigned int price = 0;
};
}
}
}

#endif // LIBTURADOR_TURA_DOMAIN_MODELS_HARBORCARGO_H_INCLUDED
