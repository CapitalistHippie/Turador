#ifndef LIBTURADOR_TURA_MODELS_HARBOR_H_INCLUDED
#define LIBTURADOR_TURA_MODELS_HARBOR_H_INCLUDED

#include "harborcargo.h"

namespace tura
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

#endif // LIBTURADOR_TURA_MODELS_HARBOR_H_INCLUDED
