#ifndef LIBTURADOR_TURA_DOMAIN_STATES_LOSTSTATE_H_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_STATES_LOSTSTATE_H_INCLUDED

#include "tura/domain/models/lostreason.h"
#include "tura/domain/states/state.h"

namespace tura
{
namespace domain
{
namespace states
{
class LostState : public State
{
public:
  models::LostReason lostReason = models::LostReason::SunkInStorm;
};
}
}
}

#endif // LIBTURADOR_TURA_DOMAIN_STATES_LOSTSTATE_H_INCLUDED
