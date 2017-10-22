#include "tura/game.h"

#include "tura/commandhandlers/purchasecargocommandhandler.hpp"
#include "tura/commands/purchasecargocommand.h"

using namespace tura;
using namespace tura::models;
using namespace tura::commands;
using namespace tura::commandhandlers;

Game::Game(GameConfiguration gameConfiguration)
  : gameConfiguration(gameConfiguration)
  , gameState(models::GameState::NotStarted)
{
  RegisterCommandHandler<PurchaseCargoCommand, PurchaseCargoCommandHandler>();
}

void Game::Start()
{
  gameState = GameState::InHarbor;
}

GameState Game::GetState() const
{
  return gameState;
}
