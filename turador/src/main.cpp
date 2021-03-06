// Memory leak detection.
#ifndef NDEBUG
#define _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC_NEW
#include <stdlib.h>

#include <crtdbg.h>
#endif // #ifndef NDEBUG

#include <iostream>

#include <tura/app/gameclient.hpp>

#include "tura/ui/cli/cliui.h"

int main()
{
#ifndef NDEBUG
  // Memory leak detection.
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // #ifndef NDEBUG

  int exitCode = 0;

#ifdef NDEBUG
  try
  {
#endif

    tura::app::GameClient gameClient;
    tura::ui::cli::CliUi commandLineInterfaceUi(gameClient, std::cin, std::cout);
    commandLineInterfaceUi.Start();

#ifdef NDEBUG
  }
  catch (const std::system_error& e)
  {
    exitCode = e.code().value();

    std::cout << "A fatal error occurred: " << exitCode << ": " << e.what() << "\nPress any key to exit.";
    std::cin.ignore();
  }
  catch (const std::exception& e)
  {
    exitCode = -1;

    std::cout << "A fatal error occurred: " << e.what() << "\nPress any key to exit.";
    std::cin.ignore();
  }
  catch (...)
  {
    exitCode = -1;

    std::cout << "An unknown fatal error occurred.\nPress any key to exit.";
    std::cin.ignore();
  }
#endif

  return exitCode;
}
