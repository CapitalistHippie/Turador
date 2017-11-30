#ifndef LIBTURADOR_TURA_APP_GAMECLIENT_H_INCLUDED
#define LIBTURADOR_TURA_APP_GAMECLIENT_H_INCLUDED

#include "tura/domain/commands/purchasecargocommand.h"
#include "tura/domain/commands/repairshipcommand.h"
#include "tura/domain/commands/sellcargocommand.h"
#include "tura/domain/commands/startgamecommand.h"
#include "tura/domain/game.h"
#include "tura/domain/models/game.h"
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

  void RepairShip(unsigned int amountOfGoldToSpend)
  {
    domain::commands::RepairShipCommand command;
    command.amount = amountOfGoldToSpend;

    HandleCommand(command);
  }
};
}
}

#endif // LIBTURADOR_TURA_APP_GAMECLIENT_H_INCLUDED
