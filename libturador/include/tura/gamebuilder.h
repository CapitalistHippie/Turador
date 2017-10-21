#ifndef LIBTURADOR_TURA_GAMEBUILDER_H_INCLUDED
#define LIBTURADOR_TURA_GAMEBUILDER_H_INCLUDED

#include "game.h"
#include "gameconfiguration.h"
#include "harborfactoryinterface.h"

namespace tura
{
class GameBuilder
{
private:
  HarborFactoryInterface* harborFactory;

public:
  GameBuilder& WithHarborFactory(HarborFactoryInterface* harborFactory)
  {
    this->harborFactory = harborFactory;

    return *this;
  }

  Game Build()
  {
    auto gameConfiguration = GameConfiguration();
    gameConfiguration.harborFactory = harborFactory;

    return Game(gameConfiguration);
  }
};
}

#endif // LIBTURADOR_TURA_GAMEBUILDER_H_INCLUDED
