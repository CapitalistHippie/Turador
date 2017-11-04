#ifndef LIBTURADOR_TURA_GAMEBUILDER_H_INCLUDED
#define LIBTURADOR_TURA_GAMEBUILDER_H_INCLUDED

#include "../commandmediator.hpp"
#include "game.h"

namespace tura
{
class GameBuilder
{
private:
  CommandMediator* commandMediator;

public:
  GameBuilder& WithCommandMediator(CommandMediator* commandMediator)
  {
    this->commandMediator = commandMediator;

    return *this;
  }

  Game Build() const { return Game(commandMediator); }
};
}

#endif // LIBTURADOR_TURA_GAMEBUILDER_H_INCLUDED
