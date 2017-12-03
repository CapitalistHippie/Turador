#ifndef TURADOR_TURA_UI_CLI_STATEHANDLERS_INHARBORSTATEHANDLER_HPP_INCLUDED
#define TURADOR_TURA_UI_CLI_STATEHANDLERS_INHARBORSTATEHANDLER_HPP_INCLUDED

#include <functional>

#include <tura/domain/constants.h>
#include <tura/domain/gamehelpers.hpp>
#include <tura/domain/models/cannonclass.h>
#include <tura/domain/models/game.h>
#include <tura/domain/models/shipsizeclass.h>
#include <tura/domain/models/shipweightclass.h>
#include <tura/helpers/chararray.hpp>

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
helpers::CharArray<64> ShipSizeClassToString(domain::models::ShipSizeClass sizeClass)
{
  switch (sizeClass)
  {
    case domain::models::ShipSizeClass::Small:
      return "small";
    case domain::models::ShipSizeClass::Normal:
      return "normal";
  }

  // TODO: Throw.
}

helpers::CharArray<64> ShipWeightClassToString(domain::models::ShipWeightClass weightClass)
{
  switch (weightClass)
  {
    case domain::models::ShipWeightClass::Light:
      return "light";
    case domain::models::ShipWeightClass::Normal:
      return "normal";
    case domain::models::ShipWeightClass::Heavy:
      return "heavy";
  }

  // TODO: Throw.
}

helpers::CharArray<64> CannonClassEnumToString(domain::models::CannonClass cannonClass)
{
  switch (cannonClass)
  {
    case domain::models::CannonClass::Light:
      return "light";
    case domain::models::CannonClass::Medium:
      return "medium";
    case domain::models::CannonClass::Heavy:
      return "heavy";
  }

  // TODO: Throw.
}

domain::models::CannonClass CannonClassStringToEnum(const helpers::CharArray<64>& cannonClass)
{
  if (cannonClass == "light")
  {
    return domain::models::CannonClass::Light;
  }
  else if (cannonClass == "medium")
  {
    return domain::models::CannonClass::Medium;
  }
  else if (cannonClass == "heavy")
  {
    return domain::models::CannonClass::Heavy;
  }

  // TODO: Throw.
}

unsigned int GetCannonCountWithClass(const helpers::Array<domain::models::Cannon, 32>& cannons,
                                     domain::models::CannonClass cannonClass)
{
  return std::count_if(cannons.begin(), cannons.end(), [=](const domain::models::Cannon& cannon) {
    return cannon.cannonClass == cannonClass;
  });
}

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

  void PurchaseCannonsCommandHandler(const InputCommand& inputCommand)
  {
    auto cannonClassString = inputCommand.GetParameter<helpers::CharArray<64>>(0);
    auto cannonClass = CannonClassStringToEnum(cannonClassString);
    auto amount = inputCommand.GetParameter<unsigned int>(1);

    gameClient.PurchaseCannons(cannonClass, amount);
  }

  void SellCannonsCommandHandler(const InputCommand& inputCommand)
  {
    auto cannonClassString = inputCommand.GetParameter<helpers::CharArray<64>>(0);
    auto cannonClass = CannonClassStringToEnum(cannonClassString);
    auto amount = inputCommand.GetParameter<unsigned int>(1);

    gameClient.SellCannons(cannonClass, amount);
  }

  void RepairShipCommandHandler(const InputCommand& inputCommand)
  {
    auto amount = inputCommand.GetParameter<unsigned int>(0);

    gameClient.RepairShip(amount);
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

    RegisterCommand<helpers::CharArray<64>, unsigned int>("purchasecannons");
    RegisterCommandHandler(
      "purchasecannons", std::bind(&InHarborStateHandler::PurchaseCannonsCommandHandler, this, std::placeholders::_1));

    RegisterCommand<helpers::CharArray<64>, unsigned int>("sellcannons");
    RegisterCommandHandler("sellcannons",
                           std::bind(&InHarborStateHandler::SellCannonsCommandHandler, this, std::placeholders::_1));

    RegisterCommand<unsigned int>("repairship");
    RegisterCommandHandler("repairship",
                           std::bind(&InHarborStateHandler::RepairShipCommandHandler, this, std::placeholders::_1));
  }

  void ExitStateFromBase() noexcept override {}

  void RenderConsole() const override
  {
    const auto& gameData = gameClient.GetGameData();
    const auto& harbor = gameData.currentHarbor;
    const auto& ship = gameData.currentShip;

    outputStream << "You have " << gameData.currentGold << " gold.\n"
                 << "Your ship is the " << ship.shipType.name << ".\n"
                 << "Your ship is " << ShipSizeClassToString(ship.shipType.sizeClass) << " sized and weighs "
                 << ShipWeightClassToString(ship.shipType.weightClass) << ".\n"
                 << "Your ship has " << GetCannonCountWithClass(ship.cannons, domain::models::CannonClass::Light)
                 << " light, " << GetCannonCountWithClass(ship.cannons, domain::models::CannonClass::Medium)
                 << " medium and " << GetCannonCountWithClass(ship.cannons, domain::models::CannonClass::Heavy)
                 << " heavy cannons out of a maximum of " << ship.shipType.cannonSpaceMax << ".\n"
                 << "Your ship has " << ship.hitPoints << " out of " << ship.shipType.hitPointsMax << " hit points.\n"
                 << "Your ship has " << domain::GetShipUsedCargoSpace(ship) << " out of " << ship.shipType.cargoSpaceMax
                 << " cargo space in use.\n"
                 << "Your ship has the following goods on board:\n"
                 << "(Name - Amount)\n";

    for (const auto& cargo : ship.goods)
    {
      outputStream << cargo.name << " - " << cargo.amount << "\n";
    }

    outputStream << '\n';

    outputStream << "You are docked in harbor " << harbor.name.array << ".\n"
                 << "The harbor has the following goods in stock:\n"
                 << "(Name - Amount - Price in gold)\n";

    for (const auto& cargo : harbor.goods)
    {
      outputStream << cargo.cargo.name << " - " << cargo.cargo.amount << " - " << cargo.price << '\n';
    }

    outputStream << '\n';

    outputStream << "The harbor has the following cannons in stock:\n"
                 << "(Type - Amount - Price in gold)\n";

    unsigned int lightCannonsForSale =
      GetCannonCountWithClass(harbor.cannonsForSale, domain::models::CannonClass::Light);
    unsigned int mediumCannonsForSale =
      GetCannonCountWithClass(harbor.cannonsForSale, domain::models::CannonClass::Medium);
    unsigned int heavyCannonsForSale =
      GetCannonCountWithClass(harbor.cannonsForSale, domain::models::CannonClass::Heavy);

    outputStream << CannonClassEnumToString(domain::models::CannonClass::Light) << " - " << lightCannonsForSale << " - "
                 << domain::Constants::LightCannonPrice << '\n'
                 << CannonClassEnumToString(domain::models::CannonClass::Medium) << " - " << mediumCannonsForSale
                 << " - " << domain::Constants::MediumCannonPrice << '\n'
                 << CannonClassEnumToString(domain::models::CannonClass::Heavy) << " - " << heavyCannonsForSale << " - "
                 << domain::Constants::HeavyCannonPrice << '\n';

    outputStream << '\n';

    outputStream << "The following commands are available:\n"
                 << "purchasecargo <cargo name> <cargo amount>\n"
                 << "sellcargo <cargo name> <cargo amount>\n"
                 << "purchasecannons <cannon type> <amount>\n"
                 << "sellcannons <cannon type> <amount>\n"
                 << "repairship <amount of gold to spend (1 gold = 10 hit points)>\n";
  }
};
}
}
}
}

#endif // TURADOR_TURA_UI_CLI_STATEHANDLERS_INHARBORSTATEHANDLER_HPP_INCLUDED
