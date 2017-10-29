#ifndef LIBTURADOR_TURA_COMMANDS_COMMANDBASE_H_INCLUDED
#define LIBTURADOR_TURA_COMMANDS_COMMANDBASE_H_INCLUDED

#include "../models/game.h"

namespace tura
{
class Game;

namespace commands
{
template<typename Command>
class CommandBase : public CommandInterface
{
public:
  const Command& command;
  const Game& game;
  models::Game& gameData;

  CommandBase(const Command& command, const Game& game, models::Game& gameData)
    : command(command)
    , game(game)
    , gameData(gameData)
  {
  }
};
}
}

#endif // LIBTURADOR_TURA_COMMANDS_COMMANDBASE_H_INCLUDED
