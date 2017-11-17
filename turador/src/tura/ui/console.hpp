#ifndef TURADOR_TURA_UI_CONSOLE_HPP_INCLUDED
#define TURADOR_TURA_UI_CONSOLE_HPP_INCLUDED

#include <cstdlib>
#include <istream>
#include <sstream>

#include <tura/domain/models/game.h>

namespace tura
{
namespace ui
{
void ClearConsole()
{
#ifdef _WIN32
  system("cls");
#else
  for (int i = 0; i < 100; ++i)
  {
    std::cout << '\n';
  }
#endif
}

void RenderConsole(const tura::domain::models::Game& gameData)
{
  ClearConsole();
}
}
}

#endif // #ifndef TURADOR_TURA_UI_CONSOLE_HPP_INCLUDED
