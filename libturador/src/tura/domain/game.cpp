#include "tura/domain/game.h"

#include "tura/domain/commandhandlers/purchasecargocommandhandler.hpp"
#include "tura/domain/commandhandlers/startgamecommandhandler.hpp"
#include "tura/domain/commands/purchasecargocommand.h"
#include "tura/domain/commands/startgamecommand.h"

using namespace tura;
using namespace tura::domain;
using namespace tura::domain::commands;
using namespace tura::domain::commandhandlers;

void Game::RegisterCommandHandlers()
{
  commandMediator->RegisterCommandHandler<CommandBase<StartGameCommand>, StartGameCommandHandler>();
  commandMediator->RegisterCommandHandler<CommandBase<PurchaseCargoCommand>, PurchaseCargoCommandHandler>();
}

Game::Game()
  : commandMediator(&commandMediatorInstance)
{
  RegisterCommandHandlers();
}

Game::Game(CommandMediator* commandMediator)
  : commandMediator(commandMediator)
{
  RegisterCommandHandlers();
}

const models::Game& Game::GetGameData() const
{
  return gameData;
}
