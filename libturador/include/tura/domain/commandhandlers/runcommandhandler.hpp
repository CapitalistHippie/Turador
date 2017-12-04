#ifndef LIBTURADOR_TURA_DOMAIN_COMMANDS_RUNCOMMANDHANDLER_HPP_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_COMMANDS_RUNCOMMANDHANDLER_HPP_INCLUDED

#include <chrono>
#include <random>
#include <system_error>

#include "tura/domain/commands/commandbase.h"
#include "tura/domain/commands/runcommand.h"
#include "tura/domain/functionalerror.h"
#include "tura/domain/functionalerrorcategory.h"
#include "tura/domain/gamehelpers.hpp"
#include "tura/domain/models/game.h"
#include "tura/domain/models/gamestate.h"
#include "tura/domain/models/shipweightclass.h"
#include "tura/domain/states/inbattlestate.h"
#include "tura/domain/states/sailingstate.h"
#include "tura/helpers/commandmediator.hpp"

namespace tura
{
namespace domain
{
namespace commandhandlers
{
class RunCommandHandler : public helpers::CommandHandlerBase<commands::CommandBase<commands::RunCommand>>
{
private:
  enum class Run
  {
    Yes = 0,
    No = 1
  };

public:
  void HandleCommand(const commands::CommandBase<commands::RunCommand>& command) const override
  {
    auto& gameData = command.gameData;
    auto& ship = gameData.currentShip;

    // Check if we're in the right state.
    if (gameData.gameState != models::GameState::InBattle)
    {
      throw std::system_error(std::make_error_code(FunctionalError::InsuitableState));
    }

    auto* state = static_cast<states::InBattleState*>(gameData.state);
    auto& enemyShip = state->enemyShip;

    auto enemyShipCannonsDamage = CalculateCannonsDamage(enemyShip.cannons);
    ship.hitPoints -= enemyShipCannonsDamage;

    // If the ship sunk while running return so the game will handle the loss.
    if (ship.hitPoints <= 0)
    {
      return;
    }

    float baseRunChance = 0.0f;
    switch (ship.shipType.weightClass)
    {
      case models::ShipWeightClass::Light:
        baseRunChance = 0.5f;
        break;
      case models::ShipWeightClass::Normal:
        baseRunChance = 0.3f;
        break;
      case models::ShipWeightClass::Heavy:
        baseRunChance = 0.05f;
    }

    float addedRunChance = 0.0f;
    switch (enemyShip.shipType.weightClass)
    {
      case models::ShipWeightClass::Normal:
        addedRunChance = 0.1f;
        break;
      case models::ShipWeightClass::Heavy:
        addedRunChance = 0.25f;
    }

    auto runChance = baseRunChance + addedRunChance;

    // Determine if we ran or not.
    std::default_random_engine rng;
    auto seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());
    rng.seed(seed);
    std::discrete_distribution<> runDist({ runChance, 1.0f - runChance });
    auto run = static_cast<Run>(runDist(rng));

    if (run == Run::Yes)
    {
      auto trip = std::move(state->trip);

      SetGameState(gameData, models::GameState::Sailing);
      auto* sailingState = static_cast<states::SailingState*>(gameData.state);

      sailingState->trip = std::move(trip);
    }
  }
};
}
}
}

#endif // LIBTURADOR_TURA_DOMAIN_COMMANDS_RUNCOMMANDHANDLER_HPP_INCLUDED
