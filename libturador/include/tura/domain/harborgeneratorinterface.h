#ifndef LIBTURADOR_TURA_DOMAIN_HARBORGENERATORINTERFACE_H_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_HARBORGENERATORINTERFACE_H_INCLUDED

#include "tura/dal/models/harbor.h"
#include "tura/dal/models/harborgenerationparameters.h"

namespace tura
{
namespace domain
{
class HarborGeneratorInterface
{
public:
  virtual ~HarborGeneratorInterface() = default;

  virtual dal::models::Harbor GenerateRandomHarbor() = 0;
  virtual dal::models::Harbor GenerateHarbor(const dal::models::HarborGenerationParameters& parameters) = 0;
};
}
}

#endif // LIBTURADOR_TURA_DOMAIN_HARBORGENERATORINTERFACE_H_INCLUDED
