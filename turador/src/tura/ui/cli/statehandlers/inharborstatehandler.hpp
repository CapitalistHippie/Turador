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

public:
  using BaseStateHandler::BaseStateHandler;

  void EnterState() override
  {
    RegisterCommand<helpers::CharArray<64>, unsigned int>("purchasecargo");
    RegisterCommandHandler("purchasecargo",
                           std::bind(&InHarborStateHandler::PurchaseCargoCommandHandler, this, std::placeholders::_1));
  }

  void ExitStateFromBase() noexcept override {}

  void RenderConsole() const override
  {
    auto gameData = gameClient.GetGameData();
    const domain::models::Harbor& harbor = gameData.currentHarbor;

    outputStream << "You are docked in harbor " << harbor.name.array << ".\n"
                 << "Goods:\n"
                 << "Name - Amount in stock - Price in gold\n";

    for (const auto& cargo : harbor.goods)
    {
      outputStream << cargo.cargo.name << " - " << cargo.cargo.amount << " - " << cargo.price << "\n";
    }
  }
};
}
}
}
}

#endif // TURADOR_TURA_UI_CLI_STATEHANDLERS_INHARBORSTATEHANDLER_HPP_INCLUDED
