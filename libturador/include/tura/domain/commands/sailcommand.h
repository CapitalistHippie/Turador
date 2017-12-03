#ifndef LIBTURADOR_TURA_DOMAIN_COMMANDS_SAILCOMMAND_H_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_COMMANDS_SAILCOMMAND_H_INCLUDED

#include "tura/helpers/chararray.hpp"
#include "tura/helpers/commandmediator.hpp"

namespace tura
{
namespace domain
{
namespace commands
{
struct SailCommand : public helpers::CommandInterface
{
  helpers::CharArray<64> harborName;
};
}
}
}

#endif // LIBTURADOR_TURA_DOMAIN_COMMANDS_SAILCOMMAND_H_INCLUDED
