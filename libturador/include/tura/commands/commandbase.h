#ifndef LIBTURADOR_TURA_COMMANDS_COMMANDBASE_H_INCLUDED
#define LIBTURADOR_TURA_COMMANDS_COMMANDBASE_H_INCLUDED

#include "../../commandhandler.hpp"

namespace tura
{
class Game;

namespace commands
{
struct CommandBase : public CommandInterface
{
  Game& game;

  CommandBase(Game& game)
    : game(game)
  {
  }
};
}
}

#endif // LIBTURADOR_TURA_COMMANDS_COMMANDBASE_H_INCLUDED
