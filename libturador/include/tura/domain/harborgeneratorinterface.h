#ifndef LIBTURADOR_TURA_DOMAIN_HARBORGENERATORINTERFACE_H_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_HARBORGENERATORINTERFACE_H_INCLUDED

#include "tura/domain/models/harbor.h"
#include "tura/domain/models/harborgenerationparameters.h"
#include "tura/helpers/chararray.hpp"

namespace tura
{
namespace domain
{
class HarborGeneratorInterface
{
public:
  virtual ~HarborGeneratorInterface() = default;

  virtual models::Harbor GenerateRandomHarbor() const = 0;
  virtual models::Harbor GenerateHarbor(const models::HarborGenerationParameters& parameters) const = 0;
  virtual models::Harbor GenerateHarborByName(const helpers::CharArray<64>& harborName) const = 0;
};
}
}

#endif // LIBTURADOR_TURA_DOMAIN_HARBORGENERATORINTERFACE_H_INCLUDED
