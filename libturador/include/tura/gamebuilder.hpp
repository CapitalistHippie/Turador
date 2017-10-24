#ifndef LIBTURADOR_TURA_GAMEBUILDER_H_INCLUDED
#define LIBTURADOR_TURA_GAMEBUILDER_H_INCLUDED

#include <utility>

#include "game.h"
#include "gameconfiguration.h"
#include "harborfactoryinterface.h"

namespace tura
{
class GameBuilder
{
private:
  GameConfiguration gameConfiguration;

public:
  GameBuilder& WithHarborFactory(HarborFactoryInterface* harborFactory)
  {
    gameConfiguration.harborFactory = harborFactory;

    return *this;
  }

  GameBuilder& WithStartingGold(unsigned int startingGold)
  {
    gameConfiguration.startingGold = startingGold;

    return *this;
  }

  Game Build() const { return Game(gameConfiguration); }
};
}

#endif // LIBTURADOR_TURA_GAMEBUILDER_H_INCLUDED
