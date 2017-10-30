#ifndef LIBTURADOR_TURA_GAMECONFIGURATION_H_INCLUDED
#define LIBTURADOR_TURA_GAMECONFIGURATION_H_INCLUDED

#include "harborfactoryinterface.h"

namespace tura
{
class GameConfiguration
{
public:
  static const unsigned int STARTING_GOLD_DEFAULT = 1000;

  HarborFactoryInterface* harborFactory = nullptr;
  CommandMediator* commandMediator = nullptr;

  unsigned int startingGold = STARTING_GOLD_DEFAULT;
};
}

#endif // LIBTURADOR_TURA_GAMECONFIGURATION_H_INCLUDED
