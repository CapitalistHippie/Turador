#ifndef LIBTURADOR_TURA_GAME_H_INCLUDED
#define LIBTURADOR_TURA_GAME_H_INCLUDED

#include "../commandhandler.hpp"
#include "gameconfiguration.h"
#include "harborfactoryinterface.h"
#include "models/game.h"
#include "models/gamestate.h"
#include "models/harborcargo.h"

namespace tura
{
class Game : public CommandHandler
{
private:
  HarborFactoryInterface* harborFactory;
  GameConfiguration gameConfiguration;

public:
  models::Game gameData;

  Game(GameConfiguration gameConfiguration);

  void Start();

  const models::Game& GetGameData() const;
  const models::HarborCargo& GetCurrentHarborCargoByName(const char* const cargoName) const;
};
}

#endif // LIBTURADOR_TURA_GAME_H_INCLUDED
