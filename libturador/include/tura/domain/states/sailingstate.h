#ifndef LIBTURADOR_TURA_DOMAIN_STATES_SAILINGSTATE_H_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_STATES_SAILINGSTATE_H_INCLUDED

#include "tura/domain/models/sailtrip.h"
#include "tura/domain/states/state.h"

namespace tura
{
namespace domain
{
namespace states
{
class SailingState : public State
{
public:
  models::SailTrip trip;
};
}
}
}

#endif // LIBTURADOR_TURA_DOMAIN_STATES_SAILINGSTATE_H_INCLUDED
