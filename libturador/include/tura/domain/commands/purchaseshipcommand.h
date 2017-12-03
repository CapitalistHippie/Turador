#ifndef LIBTURADOR_TURA_DOMAIN_COMMANDS_PURCHASESHIPCOMMAND_H_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_COMMANDS_PURCHASESHIPCOMMAND_H_INCLUDED

#include "tura/helpers/chararray.hpp"
#include "tura/helpers/commandmediator.hpp"

namespace tura
{
namespace domain
{
namespace commands
{
struct PurchaseShipCommand : public helpers::CommandInterface
{
  helpers::CharArray<64> shipType;
};
}
}
}

#endif // LIBTURADOR_TURA_DOMAIN_COMMANDS_PURCHASESHIPCOMMAND_H_INCLUDED
