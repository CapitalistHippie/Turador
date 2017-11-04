#ifndef LIBTURADOR_TURA_DAL_MODELS_CARGO_H_INCLUDED
#define LIBTURADOR_TURA_DAL_MODELS_CARGO_H_INCLUDED

namespace tura
{
namespace dal
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
}

#endif // LIBTURADOR_TURA_DAL_MODELS_CARGO_H_INCLUDED
