#ifndef LIBTURADOR_TURA_HARBORREPOSITORYINTERFACE_H_INCLUDED
#define LIBTURADOR_TURA_HARBORREPOSITORYINTERFACE_H_INCLUDED

#include "harbor.h"

namespace tura
{
class HarborRepositoryInterface
{
public:
  static const unsigned int HARBOR_COUNT_MAX = 24;

  virtual ~HarborRepositoryInterface() {};
  virtual Harbor* GetHarbors() const = 0;
  virtual unsigned int GetAmountOfHarbors() const = 0;
};
}

#endif // LIBTURADOR_TURA_HARBORREPOSITORYINTERFACE_H_INCLUDED
