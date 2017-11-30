#ifndef TURADOR_TURA_UI_CLI_STATEHANDLERS_INHARBORSTATEHANDLER_HPP_INCLUDED
#define TURADOR_TURA_UI_CLI_STATEHANDLERS_INHARBORSTATEHANDLER_HPP_INCLUDED

#include <functional>

#include <tura/domain/models/game.h>

#include "tura/ui/cli/helpers.hpp"
#include "tura/ui/cli/statehandlers/basestatehandler.hpp"

namespace tura
{
namespace ui
{
namespace cli
{
namespace statehandlers
{
class InHarborStateHandler : public BaseStateHandler
{
private:
  void PurchaseCargoCommandHandler(const InputCommand& inputCommand)
  {
    auto cargoName = inputCommand.GetParameter<helpers::CharArray<64>>(0);
    auto cargoAmount = inputCommand.GetParameter<unsigned int>(1);

    gameClient.PurchaseCargo(cargoName, cargoAmount);
  }

  void SellCargoCommandHandler(const InputCommand& inputCommand)
  {
    auto cargoName = inputCommand.GetParameter<helpers::CharArray<64>>(0);
    auto cargoAmount = inputCommand.GetParameter<unsigned int>(1);

    gameClient.SellCargo(cargoName, cargoAmount);
  }

public:
  using BaseStateHandler::BaseStateHandler;

  void EnterState() override
  {
    RegisterCommand<helpers::CharArray<64>, unsigned int>("purchasecargo");
    RegisterCommandHandler("purchasecargo",
                           std::bind(&InHarborStateHandler::PurchaseCargoCommandHandler, this, std::placeholders::_1));

    RegisterCommand<helpers::CharArray<64>, unsigned int>("sellcargo");
    RegisterCommandHandler("sellcargo",
                           std::bind(&InHarborStateHandler::SellCargoCommandHandler, this, std::placeholders::_1));
  }

  void ExitStateFromBase() noexcept override {}

  void RenderConsole() const override
  {
    auto gameData = gameClient.GetGameData();
    const domain::models::Harbor& harbor = gameData.currentHarbor;

    outputStream << "You have " << gameData.currentGold << " gold.\n"
                 << "Your ship is the " << gameData.currentShip.shipType.name << ".\n"
                 << "Your ship has " << gameData.currentShip.hitpoints << " out of "
                 << gameData.currentShip.shipType.hitPointsMax << " hitpoints.\n"
                 << "Your ship has the following goods on board:\n"
                 << "(Name - Amount)\n";

    for (const auto& cargo : gameData.currentShip.goods)
    {
      outputStream << cargo.name << " - " << cargo.amount << "\n";
    }

    outputStream << '\n';

    outputStream << "You are docked in harbor " << harbor.name.array << ".\n"
                 << "This harbor has the following goods in stock:\n"
                 << "(Name - Amount - Price in gold)\n";

    for (const auto& cargo : harbor.goods)
    {
      outputStream << cargo.cargo.name << " - " << cargo.cargo.amount << " - " << cargo.price << '\n';
    }

    outputStream << '\n';

    outputStream << "The following commands are available:\n"
                 << "purchasecargo <cargo name> <cargo amount>\n"
                 << "sellcargo <cargo name> <cargo amount>\n";
  }
};
}
}
}
}

#endif // TURADOR_TURA_UI_CLI_STATEHANDLERS_INHARBORSTATEHANDLER_HPP_INCLUDED
