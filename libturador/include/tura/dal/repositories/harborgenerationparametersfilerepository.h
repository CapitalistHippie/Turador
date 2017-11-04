#ifndef LIBTURADOR_TURA_DAL_REPOSITORIES_HARBORGENERATIONPARAMETERSFILEREPOSITORY_H_INCLUDED
#define LIBTURADOR_TURA_DAL_REPOSITORIES_HARBORGENERATIONPARAMETERSFILEREPOSITORY_H_INCLUDED

#include "tura/dal/models/harborgenerationparameters.h"
#include "tura/dal/repositories/harborgenerationparametersrepositoryinterface.h"

namespace tura
{
namespace dal
{
namespace repositories
{
class HarborGenerationParametersFileRepository : public HarborGenerationParametersRepositoryInterface
{
private:
  models::HarborGenerationParameters harborGenerationParameters[24];

public:
  HarborGenerationParametersFileRepository();

  unsigned int GetHarborGenerationParametersCount() const override;
  models::HarborGenerationParameters GetHarborGenerationParametersByName(
    const char* const harborGenerationParametersName) const override;
  models::HarborGenerationParameters GetHarborGenerationParametersByIndex(unsigned int index) const override;
  models::HarborGenerationParameters GetRandomHarborGenerationParameters() const override;
};
}
}
}

#endif // LIBTURADOR_TURA_DAL_REPOSITORIES_HARBORGENERATIONPARAMETERSFILEREPOSITORY_H_INCLUDED
