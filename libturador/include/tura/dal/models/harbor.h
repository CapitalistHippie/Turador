#ifndef LIBTURADOR_TURA_DAL_MODELS_HARBOR_H_INCLUDED
#define LIBTURADOR_TURA_DAL_MODELS_HARBOR_H_INCLUDED

#include "tura/dal/models/harborcargo.h"

namespace tura
{
namespace dal
{
namespace models
{
struct Harbor
{
  char name[64] = "";
  HarborCargo goods[15];
};
}
}
}

#endif // LIBTURADOR_TURA_DAL_MODELS_HARBOR_H_INCLUDED
