#ifndef TURADOR_TURA_UI_UI_HPP_INCLUDED
#define TURADOR_TURA_UI_UI_HPP_INCLUDED

#include <iostream>

#include <tura/app/gameclient.hpp>

#include "tura/error.h"
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
  commandParser.RegisterCommand("quit");
  commandParser.RegisterCommand("exit");

  InputCommand command;

  do
  {
    try
    {
      command = commandParser.ParseCommand(std::cin);
    }
    catch (const std::system_error& e)
    {
      if (e.code() == Error::CommandNotRegistered)
      {
        RenderConsole(gameClient.GetGameData());

        std::cout << "\nUnknown command. Please try again!\n";
      }
      else
      {
        throw;
      }
    }
  } while (command.command != "quit" && command.command != "exit");
}
}
}

#endif // #ifndef TURADOR_TURA_UI_UI_HPP_INCLUDED
