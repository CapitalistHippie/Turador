#ifndef LIBTURADOR_TURA_DOMAIN_MODELS_HARBOR_H_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_MODELS_HARBOR_H_INCLUDED

#include "tura/domain/models/cannon.h"
#include "tura/domain/models/harborcargo.h"
#include "tura/domain/models/shiptype.h"
#include "tura/helpers/array.hpp"
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
  helpers::Array<HarborCargo, 32> goods;
  helpers::Array<Cannon, 32> cannonsForSale;
  helpers::Array<ShipType, 32> shipsForSale;
};
}
}
}

#endif // LIBTURADOR_TURA_DOMAIN_MODELS_HARBOR_H_INCLUDED
