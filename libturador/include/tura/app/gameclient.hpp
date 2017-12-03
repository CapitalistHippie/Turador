#ifndef LIBTURADOR_TURA_APP_GAMECLIENT_H_INCLUDED
#define LIBTURADOR_TURA_APP_GAMECLIENT_H_INCLUDED

#include "tura/domain/commands/purchasecannonscommand.h"
#include "tura/domain/commands/purchasecargocommand.h"
#include "tura/domain/commands/purchaseshipcommand.h"
#include "tura/domain/commands/repairshipcommand.h"
#include "tura/domain/commands/sellcannonscommand.h"
// #include "tura/domain/commands/sailcommand.h"
#include "tura/domain/commands/sellcargocommand.h"
#include "tura/domain/commands/startgamecommand.h"
#include "tura/domain/game.h"
#include "tura/domain/models/game.h"
#include "tura/domain/models/sailroute.h"
#include "tura/helpers/array.hpp"
#include "tura/helpers/chararray.hpp"

namespace tura
{
namespace app
{
class GameClient
{
private:
  domain::Game game;

public:
  template<typename Command>
  void HandleCommand(const Command& command)
  {
    game.HandleCommand(command);
  }

  const domain::models::Game& GetGameData() const { return game.GetGameData(); }

  void Start()
  {
    domain::commands::StartGameCommand command;

    HandleCommand(command);
  }

  void PurchaseCargo(tura::helpers::CharArray<64> cargoName, unsigned int cargoAmount)
  {
    domain::commands::PurchaseCargoCommand command;
    command.cargoName = cargoName;
    command.cargoAmount = cargoAmount;

    HandleCommand(command);
  }

  void SellCargo(tura::helpers::CharArray<64> cargoName, unsigned int cargoAmount)
  {
    domain::commands::SellCargoCommand command;
    command.cargoName = cargoName;
    command.cargoAmount = cargoAmount;

    HandleCommand(command);
  }

  void PurchaseCannons(domain::models::CannonClass cannonClass, unsigned int amount)
  {
    domain::commands::PurchaseCannonsCommand command;
    command.cannonClass = cannonClass;
    command.amount = amount;

    HandleCommand(command);
  }

  void SellCannons(domain::models::CannonClass cannonClass, unsigned int amount)
  {
    domain::commands::SellCannonsCommand command;
    command.cannonClass = cannonClass;
    command.amount = amount;

    HandleCommand(command);
  }

  void PurchaseShip(tura::helpers::CharArray<64> shipType)
  {
    domain::commands::PurchaseShipCommand command;
    command.shipType = shipType;

    HandleCommand(command);
  }

  void RepairShip(unsigned int amountOfGoldToSpend)
  {
    domain::commands::RepairShipCommand command;
    command.amount = amountOfGoldToSpend;

    HandleCommand(command);
  }

  void Sail(tura::helpers::CharArray<64> harborName)
  {
    // domain::commands::SailCommand command;
    // command.harborName = harborName;

    // HandleCommand(command);
  }
};
}
}

#endif // LIBTURADOR_TURA_APP_GAMECLIENT_H_INCLUDED
