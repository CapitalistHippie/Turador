#ifndef LIBTURADOR_TURA_HARBORREPOSITORY_H_INCLUDED
#define LIBTURADOR_TURA_HARBORREPOSITORY_H_INCLUDED

#include "models/harbor.h"

#include "harborrepositoryinterface.h"

namespace tura
{
class HarborRepository : public HarborRepositoryInterface
{
private:
  models::Harbor harbors[24];

public:
  HarborRepository();

  const models::Harbor* GetHarbors() const override;
  unsigned int GetAmountOfHarbors() const override;
  models::Harbor GetHarborByName(const char* const harborName) const override;
};
}

#endif // LIBTURADOR_TURA_HARBORREPOSITORY_H_INCLUDED
