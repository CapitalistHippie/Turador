#ifndef LIBTURADOR_TURA_DOMAIN_COMMANDS_COMMANDBASE_H_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_COMMANDS_COMMANDBASE_H_INCLUDED

#include "tura/domain/models/game.h"
#include "tura/helpers/commandmediator.hpp"

namespace tura
{
namespace domain
{
class Game;

namespace commands
{
template<typename Command>
class CommandBase : public helpers::CommandInterface
{
public:
  const Command& command;
  models::Game& gameData;

  CommandBase(const Command& command, models::Game& gameData)
    : command(command)
    , gameData(gameData)
  {
  }
};
}
}
}

#endif // LIBTURADOR_TURA_DOMAIN_COMMANDS_COMMANDBASE_H_INCLUDED
