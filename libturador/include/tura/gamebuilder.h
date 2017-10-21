#ifndef LIBTURADOR_TURA_GAMEBUILDER_H_INCLUDED
#define LIBTURADOR_TURA_GAMEBUILDER_H_INCLUDED

#include "game.h"
#include "harborrepositoryinterface.h"
#include "gameconfiguration.h"

namespace tura
{
class GameBuilder
{
private:
  HarborRepositoryInterface* harborRepository;

public:
  GameBuilder& WithHarborRepository(HarborRepositoryInterface* harborRepository)
  {
    this->harborRepository = harborRepository;

    return *this;
  }

  Game Build()
  {
    auto gameConfiguration = GameConfiguration();
    gameConfiguration.harborRepository = harborRepository;

    return Game(gameConfiguration);
  }
};
}

#endif // LIBTURADOR_TURA_GAMEBUILDER_H_INCLUDED
