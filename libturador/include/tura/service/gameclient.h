#ifndef LIBTURADOR_TURA_SERVICE_GAMECLIENT_H_INCLUDED
#define LIBTURADOR_TURA_SERVICE_GAMECLIENT_H_INCLUDED

#include "tura/domain/game.h"

namespace tura
{
namespace service
{
class GameClient
{
private:
  domain::Game game;

public:
  GameClient();

  template<typename Command>
  void HandleCommand(const Command& command)
  {
    game.HandleCommand(command);
  }
};
}
}

#endif // LIBTURADOR_TURA_SERVICE_GAMECLIENT_H_INCLUDED
