#ifndef TURADOR_TURA_UI_UI_HPP_INCLUDED
#define TURADOR_TURA_UI_UI_HPP_INCLUDED

#include <iostream>

#include <tura/app/gameclient.hpp>

#include "tura/ui/console.hpp"
#include "tura/ui/inputcommandparser.hpp"

namespace tura
{
namespace ui
{
void Start(app::GameClient& gameClient)
{
  gameClient.Start();

  RenderConsole(gameClient.GetGameData());

  InputCommandParser commandParser;
  commandParser.ParseCommand(std::cin);
}
}
}

#endif // #ifndef TURADOR_TURA_UI_UI_HPP_INCLUDED
