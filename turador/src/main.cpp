#include <iostream>

#include <tura/app/gameclient.hpp>

void Start()
{
  tura::app::GameClient gameClient;
  gameClient.Start();
}

int main()
{
  int exitCode = 0;

  try
  {
    Start();
  }
  catch (std::system_error& e)
  {
    exitCode = e.code().value();

    std::cout << "A fatal error occurred: " << exitCode << ": " << e.what() << "\nPress any key to exit.";
  }
  catch (std::exception& e)
  {
    exitCode = -1;

    std::cout << "A fatal error occurred: " << e.what() << "\nPress any key to exit.";
  }
  catch (...)
  {
    exitCode = -1;

    std::cout << "An unknown fatal error occurred.\nPress any key to exit.";
  }

  std::cin.get();

  return exitCode;
}
