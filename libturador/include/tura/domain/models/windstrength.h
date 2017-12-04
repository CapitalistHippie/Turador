#ifndef LIBTURADOR_TURA_DOMAIN_MODELS_WINDSTRENGTH_H_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_MODELS_WINDSTRENGTH_H_INCLUDED

namespace tura
{
namespace domain
{
namespace models
{
enum class WindStrength
{
  None = 0,
  Breeze = 1,
  Weak = 2,
  Normal = 3,
  Strong = 4,
  Storm = 5,
  Unknown = 99
};
}
}
}

#endif // LIBTURADOR_TURA_DOMAIN_MODELS_WINDSTRENGTH_H_INCLUDED
