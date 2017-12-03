#ifndef LIBTURADOR_TURA_DOMAIN_MODELS_GAMESTATE_H_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_MODELS_GAMESTATE_H_INCLUDED

namespace tura
{
namespace domain
{
namespace models
{
enum class GameState
{
  NotStarted,
  InHarbor,
  Won,
  Lost
};
}
}
}

#endif // LIBTURADOR_TURA_DOMAIN_MODELS_GAMESTATE_H_INCLUDED
