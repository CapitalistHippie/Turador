#ifndef LIBTURADOR_TURA_DOMAIN_MODELS_CARGO_H_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_MODELS_CARGO_H_INCLUDED

#include "tura/helpers/chararray.hpp"

namespace tura
{
namespace domain
{
namespace models
{
struct Cargo
{
  helpers::CharArray<64> name;
  unsigned int amount = 0;
};
}
}
}

#endif // LIBTURADOR_TURA_DOMAIN_MODELS_CARGO_H_INCLUDED
