#include "tura/game.h"

using namespace tura;
using namespace tura::models;

void Game::Start()
{
  gameState = GameState::InHarbor;
}

GameState Game::GetState() const
{
  return gameState;
}
