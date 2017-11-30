#ifndef LIBTURADOR_TURA_DOMAIN_COMMANDS_SELLCARGOCOMMAND_H_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_COMMANDS_SELLCARGOCOMMAND_H_INCLUDED

#include "tura/helpers/chararray.hpp"
#include "tura/helpers/commandmediator.hpp"

namespace tura
{
namespace domain
{
namespace commands
{
struct SellCargoCommand : public helpers::CommandInterface
{
  helpers::CharArray<64> cargoName;
  unsigned int cargoAmount = 0;
};
}
}
}

#endif // LIBTURADOR_TURA_DOMAIN_COMMANDS_SELLCARGOCOMMAND_H_INCLUDED
