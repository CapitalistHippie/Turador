#ifndef LIBTURADOR_TURA_DAL_MODELS_HARBORCARGO_H_INCLUDED
#define LIBTURADOR_TURA_DAL_MODELS_HARBORCARGO_H_INCLUDED

#include "tura/dal/models/cargo.h"

namespace tura
{
namespace dal
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

#endif // LIBTURADOR_TURA_DAL_MODELS_HARBORCARGO_H_INCLUDED
