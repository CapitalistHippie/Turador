#ifndef LIBTURADOR_TURA_DOMAIN_COMMANDS_PURCHASECARGOCOMMAND_H_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_COMMANDS_PURCHASECARGOCOMMAND_H_INCLUDED

#include "tura/domain/commandmediator.hpp"

namespace tura
{
namespace domain
{
namespace commands
{
struct PurchaseCargoCommand : public CommandInterface
{
  char cargoName[64];
  unsigned int cargoAmount;
};
}
}
}

#endif // LIBTURADOR_TURA_DOMAIN_COMMANDS_PURCHASECARGOCOMMAND_H_INCLUDED
