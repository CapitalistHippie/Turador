#ifndef LIBTURADOR_TURA_DOMAIN_CONSTANTS_H_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_CONSTANTS_H_INCLUDED

#include "tura/domain/models/gamestate.h"

namespace tura
{
namespace domain
{
struct Constants
{
  static const models::GameState GameInitialState = models::GameState::InHarbor;
  static const unsigned int GameInitialGold = 1000;
};
}
}

#endif // LIBTURADOR_TURA_DOMAIN_CONSTANTS_H_INCLUDED
