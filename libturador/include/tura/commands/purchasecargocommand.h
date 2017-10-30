#ifndef LIBTURADOR_TURA_COMMANDS_PURCHASECARGOCOMMAND_H_INCLUDED
#define LIBTURADOR_TURA_COMMANDS_PURCHASECARGOCOMMAND_H_INCLUDED

#include "../../commandmediator.hpp"

namespace tura
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

#endif // LIBTURADOR_TURA_COMMANDS_PURCHASECARGOCOMMAND_H_INCLUDED
