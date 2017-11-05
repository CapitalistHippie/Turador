#ifndef LIBTURADOR_TURA_DOMAIN_HARBORGENERATORINTERFACE_H_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_HARBORGENERATORINTERFACE_H_INCLUDED

#include "tura/domain/models/harbor.h"
#include "tura/domain/models/harborgenerationparameters.h"

namespace tura
{
namespace domain
{
class HarborGeneratorInterface
{
public:
  virtual ~HarborGeneratorInterface() = default;

  virtual models::Harbor GenerateRandomHarbor() = 0;
  virtual models::Harbor GenerateHarbor(const models::HarborGenerationParameters& parameters) = 0;
};
}
}

#endif // LIBTURADOR_TURA_DOMAIN_HARBORGENERATORINTERFACE_H_INCLUDED
