#ifndef LIBTURADOR_TURA_DOMAIN_MODELS_HARBOR_H_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_MODELS_HARBOR_H_INCLUDED

#include "tura/domain/models/harborcargo.h"
#include "tura/helpers/chararray.hpp"

namespace tura
{
namespace domain
{
namespace models
{
struct Harbor
{
  helpers::CharArray<64> name;
  HarborCargo goods[15];
};
}
}
}

#endif // LIBTURADOR_TURA_DOMAIN_MODELS_HARBOR_H_INCLUDED
