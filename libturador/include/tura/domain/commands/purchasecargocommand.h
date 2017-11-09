#ifndef LIBTURADOR_TURA_DOMAIN_COMMANDS_PURCHASECARGOCOMMAND_H_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_COMMANDS_PURCHASECARGOCOMMAND_H_INCLUDED

#include "tura/domain/commandmediator.hpp"
#include "tura/helpers/chararray.hpp"

namespace tura
{
namespace domain
{
namespace commands
{
struct PurchaseCargoCommand : public CommandInterface
{
  helpers::CharArray<64> cargoName;
  unsigned int cargoAmount;
};
}
}
}

#endif // LIBTURADOR_TURA_DOMAIN_COMMANDS_PURCHASECARGOCOMMAND_H_INCLUDED
