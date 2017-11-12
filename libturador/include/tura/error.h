#ifndef LIBTURADOR_TURA_ERROR_H_INCLUDED
#define LIBTURADOR_TURA_ERROR_H_INCLUDED

#include <system_error>

namespace tura
{
enum class Error
{
  None,
  InvalidArgument,
  OutOfRange,
  InsuitableState,
  InsufficientGold,
  InsufficientCargoInHarbor,
  InsufficientCargoInShip,
  InsufficientShipCargoSpace,
  UnknownCargo,
  UnknownHarborGenerationParameters,
  UnknownShipType,
  UnableToOpenFile,
  NoFileOpened
};
}

namespace std
{
template<>
struct is_error_code_enum<tura::Error> : true_type
{
};

error_code make_error_code(tura::Error);
}

#endif // LIBTURADOR_TURA_ERROR_H_INCLUDED
