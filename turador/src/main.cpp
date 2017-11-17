#include <iostream>

#include <tura/app/gameclient.hpp>

#include "tura/ui/ui.hpp"

int main()
{
  int exitCode = 0;

  try
  {
    tura::app::GameClient gameClient;
    tura::ui::Start(gameClient);
  }
  catch (const std::system_error& e)
  {
    exitCode = e.code().value();

    std::cout << "A fatal error occurred: " << exitCode << ": " << e.what() << "\nPress any key to exit.";
  }
  catch (const std::exception& e)
  {
    exitCode = -1;

    std::cout << "A fatal error occurred: " << e.what() << "\nPress any key to exit.";
  }
  catch (...)
  {
    exitCode = -1;

    std::cout << "An unknown fatal error occurred.\nPress any key to exit.";
  }

  return exitCode;
}
