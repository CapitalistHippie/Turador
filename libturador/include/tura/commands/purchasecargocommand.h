#ifndef LIBTURADOR_TURA_COMMANDS_PURCHASECARGOCOMMAND_H_INCLUDED
#define LIBTURADOR_TURA_COMMANDS_PURCHASECARGOCOMMAND_H_INCLUDED

#include "commandbase.h"

namespace tura
{
namespace commands
{
struct PurchaseCargoCommand : public CommandBase
{
  using CommandBase::CommandBase;

  char cargoName[64];
  unsigned int amount;
};
}
}

#endif // LIBTURADOR_TURA_COMMANDS_PURCHASECARGOCOMMAND_H_INCLUDED
