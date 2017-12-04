#ifndef LIBTURADOR_TURA_DOMAIN_STATES_INHARBORSTATE_H_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_STATES_INHARBORSTATE_H_INCLUDED

#include "tura/domain/models/harbor.h"
#include "tura/domain/states/state.h"

namespace tura
{
namespace domain
{
namespace states
{
class InHarborState : public State
{
public:
  models::Harbor harbor;
};
}
}
}

#endif // LIBTURADOR_TURA_DOMAIN_STATES_INHARBORSTATE_H_INCLUDED
