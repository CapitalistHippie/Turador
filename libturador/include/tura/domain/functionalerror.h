#ifndef LIBTURADOR_TURA_DOMAIN_FUNCTIONALERROR_H_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_FUNCTIONALERROR_H_INCLUDED

namespace tura
{
namespace domain
{
enum class FunctionalError
{
  None,
  InsuitableState,
  InsuitableShipType,
  InsufficientGold,
  InsufficientCargoInHarbor,
  InsufficientCannonsForSaleInHarbor,
  InsufficientCargoInShip,
  InsufficientCannonsInShip,
  InsufficientShipCargoSpace,
  UnknownCargo,
  UnknownSailRoute,
  CargoNotInShip,
  ShipCannonLimitReached,
  ShipNotForSaleInHarbor
};
}
}

#endif // #ifndef LIBTURADOR_TURA_DOMAIN_FUNCTIONALERROR_H_INCLUDED
