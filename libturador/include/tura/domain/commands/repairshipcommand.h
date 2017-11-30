#ifndef LIBTURADOR_TURA_DOMAIN_COMMANDS_REPAIRSHIPCOMMAND_H_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_COMMANDS_REPAIRSHIPCOMMAND_H_INCLUDED

#include "tura/helpers/commandmediator.hpp"

namespace tura
{
namespace domain
{
namespace commands
{
struct RepairShipCommand : public helpers::CommandInterface
{
  unsigned int amount = 0;
};
}
}
}

#endif // LIBTURADOR_TURA_DOMAIN_COMMANDS_REPAIRSHIPCOMMAND_H_INCLUDED
