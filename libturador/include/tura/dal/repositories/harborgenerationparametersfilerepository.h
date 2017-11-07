#ifndef LIBTURADOR_TURA_DAL_REPOSITORIES_HARBORGENERATIONPARAMETERSFILEREPOSITORY_H_INCLUDED
#define LIBTURADOR_TURA_DAL_REPOSITORIES_HARBORGENERATIONPARAMETERSFILEREPOSITORY_H_INCLUDED

#include "tura/dal/repositories/harborgenerationparametersrepositoryinterface.h"
#include "tura/domain/models/harborgenerationparameters.h"

namespace tura
{
namespace dal
{
namespace repositories
{
class HarborGenerationParametersFileRepository : public HarborGenerationParametersRepositoryInterface
{
private:
  static const int HARBOR_GENERATION_PARAMETERS_COUNT = 24;

  domain::models::HarborGenerationParameters harborGenerationParameters[HARBOR_GENERATION_PARAMETERS_COUNT];

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
