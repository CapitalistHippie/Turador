#ifndef LIBTURADOR_TURA_DOMAIN_COMMANDS_COMMANDBASE_H_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_COMMANDS_COMMANDBASE_H_INCLUDED

#include "tura/dal/models/game.h"
#include "tura/domain/commandmediator.hpp"

namespace tura
{
namespace domain
{
class Game;

namespace commands
{
template<typename Command>
class CommandBase : public CommandInterface
{
public:
  const Command& command;
  dal::models::Game& gameData;

  CommandBase(const Command& command, dal::models::Game& gameData)
    : command(command)
    , gameData(gameData)
  {
  }
};
}
}
}

#endif // LIBTURADOR_TURA_DOMAIN_COMMANDS_COMMANDBASE_H_INCLUDED
