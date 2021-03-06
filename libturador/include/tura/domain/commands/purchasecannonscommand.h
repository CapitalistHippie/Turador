#ifndef LIBTURADOR_TURA_DOMAIN_COMMANDS_PURCHASECANNONSCOMMAND_H_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_COMMANDS_PURCHASECANNONSCOMMAND_H_INCLUDED

#include "tura/domain/models/cannonclass.h"
#include "tura/helpers/commandmediator.hpp"

namespace tura
{
namespace domain
{
namespace commands
{
struct PurchaseCannonsCommand : public helpers::CommandInterface
{
  models::CannonClass cannonClass = models::CannonClass::Light;
  unsigned int amount = 0;
};
}
}
}

#endif // LIBTURADOR_TURA_DOMAIN_COMMANDS_PURCHASECANNONSCOMMAND_H_INCLUDED
