#ifndef LIBTURADOR_TURA_DOMAIN_STATES_INBATTLESTATE_H_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_STATES_INBATTLESTATE_H_INCLUDED

#include "tura/domain/models/sailtrip.h"
#include "tura/domain/models/ship.h"
#include "tura/domain/states/state.h"

namespace tura
{
namespace domain
{
namespace states
{
class InBattleState : public State
{
public:
  models::Ship enemyShip;
  models::SailTrip trip;
};
}
}
}

#endif // LIBTURADOR_TURA_DOMAIN_STATES_INBATTLESTATE_H_INCLUDED
