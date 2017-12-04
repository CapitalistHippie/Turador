#include "tura/domain/game.h"

#include "tura/domain/commandhandlers/firecommandhandler.hpp"
#include "tura/domain/commandhandlers/purchasecannonscommandhandler.hpp"
#include "tura/domain/commandhandlers/purchasecargocommandhandler.hpp"
#include "tura/domain/commandhandlers/purchaseshipcommandhandler.hpp"
#include "tura/domain/commandhandlers/repairshipcommandhandler.hpp"
#include "tura/domain/commandhandlers/runcommandhandler.hpp"
#include "tura/domain/commandhandlers/sailcommandhandler.hpp"
#include "tura/domain/commandhandlers/sellcannonscommandhandler.hpp"
#include "tura/domain/commandhandlers/sellcargocommandhandler.hpp"
#include "tura/domain/commandhandlers/startgamecommandhandler.hpp"
#include "tura/domain/commandhandlers/startsailingcommandhandler.hpp"
#include "tura/domain/commandhandlers/surrendercommandhandler.hpp"
#include "tura/domain/commands/firecommand.h"
#include "tura/domain/commands/purchasecannonscommand.h"
#include "tura/domain/commands/purchasecargocommand.h"
#include "tura/domain/commands/purchaseshipcommand.h"
#include "tura/domain/commands/repairshipcommand.h"
#include "tura/domain/commands/runcommand.h"
#include "tura/domain/commands/sailcommand.h"
#include "tura/domain/commands/sellcannonscommand.h"
#include "tura/domain/commands/sellcargocommand.h"
#include "tura/domain/commands/startgamecommand.h"
#include "tura/domain/commands/startsailingcommand.h"
#include "tura/domain/commands/surrendercommand.h"

using namespace tura;
using namespace tura::domain;
using namespace tura::domain::commands;
using namespace tura::domain::commandhandlers;

void Game::RegisterCommandHandlers()
{
  commandMediator->RegisterCommandHandler<CommandBase<FireCommand>, FireCommandHandler>();
  commandMediator->RegisterCommandHandler<CommandBase<PurchaseCannonsCommand>, PurchaseCannonsCommandHandler>();
  commandMediator->RegisterCommandHandler<CommandBase<PurchaseCargoCommand>, PurchaseCargoCommandHandler>();
  commandMediator->RegisterCommandHandler<CommandBase<PurchaseShipCommand>, PurchaseShipCommandHandler>();
  commandMediator->RegisterCommandHandler<CommandBase<RepairShipCommand>, RepairShipCommandHandler>();
  commandMediator->RegisterCommandHandler<CommandBase<RunCommand>, RunCommandHandler>();
  commandMediator->RegisterCommandHandler<CommandBase<SailCommand>, SailCommandHandler>();
  commandMediator->RegisterCommandHandler<CommandBase<SellCannonsCommand>, SellCannonsCommandHandler>();
  commandMediator->RegisterCommandHandler<CommandBase<SellCargoCommand>, SellCargoCommandHandler>();
  commandMediator->RegisterCommandHandler<CommandBase<StartGameCommand>, StartGameCommandHandler>();
  commandMediator->RegisterCommandHandler<CommandBase<StartSailingCommand>, StartSailingCommandHandler>();
  commandMediator->RegisterCommandHandler<CommandBase<SurrenderCommand>, SurrenderCommandHandler>();
}

Game::Game()
  : commandMediator(&commandMediatorInstance)
{
  RegisterCommandHandlers();
}

Game::Game(helpers::CommandMediator* commandMediator)
  : commandMediator(commandMediator)
{
  RegisterCommandHandlers();
}

const models::Game& Game::GetGameData() const
{
  return gameData;
}
