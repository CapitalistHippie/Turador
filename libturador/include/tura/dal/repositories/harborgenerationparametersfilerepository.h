#ifndef LIBTURADOR_TURA_DAL_REPOSITORIES_HARBORGENERATIONPARAMETERSFILEREPOSITORY_H_INCLUDED
#define LIBTURADOR_TURA_DAL_REPOSITORIES_HARBORGENERATIONPARAMETERSFILEREPOSITORY_H_INCLUDED

#include "tura/dal/repositories/harborgenerationparametersrepositoryinterface.h"
#include "tura/domain/models/harborgenerationparameters.h"
#include "tura/helpers/array.hpp"

namespace tura
{
namespace dal
{
namespace repositories
{
class HarborGenerationParametersFileRepository : public HarborGenerationParametersRepositoryInterface
{
private:
  tura::helpers::Array<domain::models::HarborGenerationParameters, 32> harborGenerationParameters;

public:
  HarborGenerationParametersFileRepository();

  unsigned int GetHarborGenerationParametersCount() const override;
  domain::models::HarborGenerationParameters GetHarborGenerationParametersByName(
    const char* const harborGenerationParametersName) const override;
  domain::models::HarborGenerationParameters GetHarborGenerationParametersByIndex(unsigned int index) const override;
  domain::models::HarborGenerationParameters GetRandomHarborGenerationParameters() const override;
};
}
}
}

#endif // LIBTURADOR_TURA_DAL_REPOSITORIES_HARBORGENERATIONPARAMETERSFILEREPOSITORY_H_INCLUDED
