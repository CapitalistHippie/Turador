#ifndef LIBTURADOR_TURA_DOMAIN_CONSTANTS_H_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_CONSTANTS_H_INCLUDED

#include "tura/domain/models/gamestate.h"

namespace tura
{
namespace domain
{
struct Constants
{
  static const models::GameState GameInitialState = models::GameState::InHarbor;
  static const unsigned int GameInitialGold = 100000;

  static const unsigned int HarborLightCannonsForSaleMin = 0;
  static const unsigned int HarborLightCannonsForSaleMax = 5;
  static const unsigned int HarborMediumCannonsForSaleMin = 0;
  static const unsigned int HarborMediumCannonsForSaleMax = 3;
  static const unsigned int HarborHeavyCannonsForSaleMin = 0;
  static const unsigned int HarborHeavyCannonsForSaleMax = 2;

  static const unsigned int LightCannonPrice = 50;
  static const unsigned int MediumCannonPrice = 200;
  static const unsigned int HeavyCannonPrice = 1000;
};
}
}

#endif // LIBTURADOR_TURA_DOMAIN_CONSTANTS_H_INCLUDED
