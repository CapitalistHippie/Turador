#ifndef LIBTURADOR_TURA_HARBORFACTORY_H_INCLUDED
#define LIBTURADOR_TURA_HARBORFACTORY_H_INCLUDED

#include "models/harbor.h"
#include "models/harborstats.h"

#include "harborfactoryinterface.h"

namespace tura
{
class HarborFactory : public HarborFactoryInterface
{
private:
  models::HarborStats harborStats[24];

  models::Harbor ConstructHarbor(const models::HarborStats& stats) const;

public:
  HarborFactory();

  unsigned int GetAmountOfHarbors() const override;
  models::Harbor GetHarborByName(const char* const harborName) const override;
  models::Harbor GetHarborByIndex(unsigned int index) const override;
};
}

#endif // LIBTURADOR_TURA_HARBORFACTORY_H_INCLUDED
