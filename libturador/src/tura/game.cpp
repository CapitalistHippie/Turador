#include "tura/game.h"

#include "tura/commandhandlers/purchasecargocommandhandler.hpp"
#include "tura/commands/purchasecargocommand.h"

using namespace tura;
using namespace tura::models;
using namespace tura::commands;
using namespace tura::commandhandlers;

tura::Game::Game(GameConfiguration gameConfiguration)
  : harborFactory(gameConfiguration.harborFactory)
  , commandMediator(gameConfiguration.commandMediator)
  , gameConfiguration(gameConfiguration)
{
  commandMediator->RegisterCommandHandler<CommandBase<PurchaseCargoCommand>, PurchaseCargoCommandHandler>();
}

void tura::Game::Start()
{
  // The game starts in a harbor. Set the state to InHarbor and the harbor to the first one.
  gameData.gameState = GameState::InHarbor;
  gameData.currentHarbor = harborFactory->GetHarborByIndex(0);

  gameData.currentGold = gameConfiguration.startingGold;
}

const models::Game& tura::Game::GetGameData() const
{
  return gameData;
}
