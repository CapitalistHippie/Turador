#ifndef TURADOR_TURA_UI_CLI_CONSOLEHELPERS_HPP_INCLUDED
#define TURADOR_TURA_UI_CLI_CONSOLEHELPERS_HPP_INCLUDED

#include <iostream>
#include <stdlib.h>

namespace tura
{
namespace ui
{
namespace cli
{
inline void ClearConsole()
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
}
}
}

#endif // #ifndef TURADOR_TURA_UI_CLI_CONSOLEHELPERS_HPP_INCLUDED
