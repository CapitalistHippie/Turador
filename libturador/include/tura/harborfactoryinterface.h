#ifndef LIBTURADOR_TURA_HARBORFACTORYINTERFACE_H_INCLUDED
#define LIBTURADOR_TURA_HARBORFACTORYINTERFACE_H_INCLUDED

#include "models/harbor.h"

namespace tura
{
class HarborFactoryInterface
{
public:
  virtual ~HarborFactoryInterface() = default;
  virtual unsigned int GetAmountOfHarbors() const = 0;
  virtual models::Harbor GetHarborByName(const char* const harborName) const = 0;
  virtual models::Harbor GetHarborByIndex(unsigned int index) const = 0;
};
}

#endif // LIBTURADOR_TURA_HARBORFACTORYINTERFACE_H_INCLUDED
