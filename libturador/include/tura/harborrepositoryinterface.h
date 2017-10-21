#ifndef LIBTURADOR_TURA_HARBORREPOSITORYINTERFACE_H_INCLUDED
#define LIBTURADOR_TURA_HARBORREPOSITORYINTERFACE_H_INCLUDED

#include "models/harbor.h"

namespace tura
{
class HarborRepositoryInterface
{
public:
  virtual ~HarborRepositoryInterface(){};
  virtual const models::Harbor* GetHarbors() const = 0;
  virtual unsigned int GetAmountOfHarbors() const = 0;
  virtual models::Harbor GetHarborByName(const char* const harborName) const = 0;
};
}

#endif // LIBTURADOR_TURA_HARBORREPOSITORYINTERFACE_H_INCLUDED
