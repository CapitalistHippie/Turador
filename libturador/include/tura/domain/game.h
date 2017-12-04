#ifndef LIBTURADOR_TURA_DOMAIN_GAME_H_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_GAME_H_INCLUDED

#include "tura/domain/commands/commandbase.h"
#include "tura/domain/models/game.h"
#include "tura/domain/states/inbattlestate.h"
#include "tura/domain/states/inharborstate.h"
#include "tura/domain/states/loststate.h"
#include "tura/domain/states/sailingstate.h"
#include "tura/domain/states/state.h"
#include "tura/helpers/commandmediator.hpp"
#include "tura/helpers/noncopyable.h"

namespace tura
{
namespace domain
{
class Game : helpers::Noncopyable
{
private:
  helpers::CommandMediator commandMediatorInstance;
  helpers::CommandMediator* commandMediator;

  models::Game gameData;

  void RegisterCommandHandlers();

public:
  Game();
  Game(helpers::CommandMediator* commandMediator);
  ~Game()
  {
    if (gameData.state != nullptr)
    {
      delete gameData.state;
    }
  }

  template<typename Command>
  void HandleCommand(const Command& command)
  {
    commands::CommandBase<Command> commandHandlerCommand(command, gameData);

    commandMediator->HandleCommand(commandHandlerCommand);

    // Check if the player reached 1.000.000 gold or if the ship has 0 hitpoints. Those are the winning and losing
    // conditions respectfully.
    if (gameData.currentGold >= 1000000)
    {
      gameData.gameState = models::GameState::Won;
    }
    else if (gameData.currentShip.hitPoints <= 0)
    {
      models::LostReason lostReason;
      if (gameData.gameState == models::GameState::Sailing)
      {
        lostReason = models::LostReason::SunkInStorm;
      }
      else if (gameData.gameState == models::GameState::InBattle)
      {
        lostReason = models::LostReason::SunkByPirates;
      }

      SetGameState(gameData, models::GameState::Lost);

      auto* state = static_cast<states::LostState*>(gameData.state);
      state->lostReason = lostReason;
    }
  }

  const models::Game& GetGameData() const;
};

inline void SetGameState(models::Game& gameData, models::GameState gameState)
{
  if (gameData.state != nullptr)
  {
    delete gameData.state;
  }

  switch (gameState)
  {
    case models::GameState::Lost:
      gameData.state = new states::LostState;
      break;
    case models::GameState::Sailing:
      gameData.state = new states::SailingState;
      break;
    case models::GameState::InBattle:
      gameData.state = new states::InBattleState;
      break;
    case models::GameState::InHarbor:
      gameData.state = new states::InHarborState;
  }

  gameData.gameState = gameState;
}
}
}

#endif // LIBTURADOR_TURA_DOMAIN_GAME_H_INCLUDED
