#ifndef LIBTURADOR_TURA_MODELS_CARGO_H_INCLUDED
#define LIBTURADOR_TURA_MODELS_CARGO_H_INCLUDED

namespace tura
{
namespace models
{
struct Cargo
{
  char name[64] = "";
  unsigned int amount = 0;
};
}
}

#endif // LIBTURADOR_TURA_MODELS_CARGO_H_INCLUDED
