#ifndef LIBTURADOR_TURA_DOMAIN_MODELS_HARBOR_H_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_MODELS_HARBOR_H_INCLUDED

#include "tura/domain/models/harborcargo.h"

namespace tura
{
namespace domain
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

#endif // LIBTURADOR_TURA_DOMAIN_MODELS_HARBOR_H_INCLUDED
