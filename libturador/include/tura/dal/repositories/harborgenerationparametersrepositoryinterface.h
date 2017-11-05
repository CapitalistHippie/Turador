#ifndef LIBTURADOR_TURA_DAL_REPOSITORIES_HARBORGENERATIONPARAMETERSREPOSITORYINTERFACE_H_INCLUDED
#define LIBTURADOR_TURA_DAL_REPOSITORIES_HARBORGENERATIONPARAMETERSREPOSITORYINTERFACE_H_INCLUDED

#include "tura/domain/models/harborgenerationparameters.h"

namespace tura
{
namespace dal
{
namespace repositories
{
class HarborGenerationParametersRepositoryInterface
{
public:
  virtual ~HarborGenerationParametersRepositoryInterface() = default;
  virtual unsigned int GetHarborGenerationParametersCount() const = 0;
  virtual domain::models::HarborGenerationParameters GetHarborGenerationParametersByName(
    const char* const harborGenerationParametersName) const = 0;
  virtual domain::models::HarborGenerationParameters GetHarborGenerationParametersByIndex(unsigned int index) const = 0;
  virtual domain::models::HarborGenerationParameters GetRandomHarborGenerationParameters() const = 0;
};
}
}
}

#endif // LIBTURADOR_TURA_DAL_REPOSITORIES_HARBORGENERATIONPARAMETERSREPOSITORYINTERFACE_H_INCLUDED
