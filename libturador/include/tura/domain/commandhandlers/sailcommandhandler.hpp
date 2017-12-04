#ifndef LIBTURADOR_TURA_DOMAIN_COMMANDHANDLERS_SAILCOMMANDHANDLER_HPP_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_COMMANDHANDLERS_SAILCOMMANDHANDLER_HPP_INCLUDED

#include <algorithm>
#include <chrono>
#include <math.h>
#include <random>
#include <system_error>

#include "tura/domain/commands/commandbase.h"
#include "tura/domain/commands/sailcommand.h"
#include "tura/domain/constants.h"
#include "tura/domain/functionalerror.h"
#include "tura/domain/functionalerrorcategory.h"
#include "tura/domain/harborgenerator.hpp"
#include "tura/domain/harborgeneratorinterface.h"
#include "tura/domain/models/gamestate.h"
#include "tura/domain/models/sailroute.h"
#include "tura/domain/models/sailtrip.h"
#include "tura/domain/models/windstrength.h"
#include "tura/domain/shipgenerator.hpp"
#include "tura/domain/shipgeneratorinterface.h"
#include "tura/helpers/commandmediator.hpp"

namespace tura
{
namespace domain
{
namespace commandhandlers
{
class SailCommandHandler : public helpers::CommandHandlerBase<commands::CommandBase<commands::SailCommand>>
{
private:
  enum class SailResult
  {
    Battle = 0,
    Sail = 1
  };

  enum class StormResult
  {
    BlownOffCourse = 0,
    Nothing = 1,
    BlownOnCourse = 2
  };

  HarborGenerator harborGeneratorInstance;
  HarborGeneratorInterface* harborGenerator;

  ShipGenerator shipGeneratorInstance;
  ShipGeneratorInterface* shipGenerator;

public:
  SailCommandHandler()
    : harborGenerator(&harborGeneratorInstance)
    , shipGenerator(&shipGeneratorInstance)
  {
  }

  SailCommandHandler(HarborGeneratorInterface* harborGenerator, ShipGeneratorInterface* shipGenerator)
    : harborGenerator(harborGenerator)
    , shipGenerator(shipGenerator)
  {
  }

  void HandleCommand(const commands::CommandBase<commands::SailCommand>& command) const override
  {
    auto& gameData = command.gameData;
    auto& harbor = gameData.currentHarbor;
    auto& ship = gameData.currentShip;
    auto& trip = gameData.currentSailTrip;

    // Check if we're in the right state.
    if (gameData.gameState != models::GameState::Sailing)
    {
      throw std::system_error(std::make_error_code(FunctionalError::InsuitableState));
    }

    // Determine if there is a battle or if we're sailing.
    std::default_random_engine rng;
    auto seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());
    rng.seed(seed);
    std::discrete_distribution<> dist({ Constants::SailingBattleChance, Constants::SailingSailChance });
    auto decision = static_cast<SailResult>(dist(rng));

    if (decision == SailResult::Battle)
    {
      gameData.currentEnemyShip = shipGenerator->GenerateRandomEnemyShip();
      gameData.gameState = models::GameState::InBattle;
    }
    else
    {
      // Determine the wind strength.
      std::discrete_distribution<> windStrengthDist({ Constants::SailingWindStrengthChanceNone,
                                                      Constants::SailingWindStrengthChanceBreeze,
                                                      Constants::SailingWindStrengthChanceWeak,
                                                      Constants::SailingWindStrengthChanceNormal,
                                                      Constants::SailingWindStrengthChanceStrong,
                                                      Constants::SailingWindStrengthChanceStorm });
      auto windStrength = static_cast<models::WindStrength>(windStrengthDist(rng));
      trip.lastWindStrength = windStrength;

      switch (windStrength)
      {
        case models::WindStrength::None:
          break;
        case models::WindStrength::Breeze:
          if (ship.shipType.weightClass == models::ShipWeightClass::Light)
          {
            trip.turnsSailed++;
          }
          break;
        case models::WindStrength::Weak:
          if (ship.shipType.weightClass != models::ShipWeightClass::Heavy)
          {
            trip.turnsSailed++;
          }
          break;
        case models::WindStrength::Normal:
          trip.turnsSailed++;
          break;
        case models::WindStrength::Strong:
          trip.turnsSailed += 2;
          break;
        case models::WindStrength::Storm:
          // Determine the storm result.
          std::discrete_distribution<> stormResultDist({ Constants::SailingStormResultChanceBlownOffCourse,
                                                         Constants::SailingStormResultChanceNothing,
                                                         Constants::SailingStormResultChanceBlownOnCourse });
          auto stormResult = static_cast<StormResult>(stormResultDist(rng));

          switch (stormResult)
          {
            case StormResult::BlownOffCourse:
              trip.turnsSailed--;
              break;
            case StormResult::BlownOnCourse:
              trip.turnsSailed++;
              break;
            case StormResult::Nothing:
              break;
          }

          // Calculate the damage done to the ship by the storm.
          std::uniform_real_distribution<float> damageDist(0.1f, 1.0f);
          unsigned int damage = std::round(ship.hitPoints * damageDist(rng));
          ship.hitPoints -= damage;
      }

      // Check if the player has reached his destination.
      if (trip.turnsSailed >= trip.route.distanceInTurns)
      {
        gameData.currentHarbor = harborGenerator->GenerateHarborByName(gameData.currentSailTrip.route.toHarborName);
        gameData.gameState = models::GameState::InHarbor;
      }
    }
  }
};
}
}
}

#endif // #ifndef LIBTURADOR_TURA_DOMAIN_COMMANDHANDLERS_SAILCOMMANDHANDLER_HPP_INCLUDED
