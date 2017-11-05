#ifndef LIBTURADOR_TURA_DOMAIN_HARBORGENERATOR_HPP_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_HARBORGENERATOR_HPP_INCLUDED

#include <ctime>
#include <random>

#include "tura/dal/repositories/harborgenerationparametersfilerepository.h"
#include "tura/dal/repositories/harborgenerationparametersrepositoryinterface.h"
#include "tura/domain/harborgeneratorinterface.h"
#include "tura/domain/models/harbor.h"
#include "tura/domain/models/harborgenerationparameters.h"

namespace tura
{
namespace domain
{
class HarborGenerator : public HarborGeneratorInterface
{
private:
  dal::repositories::HarborGenerationParametersFileRepository harborGenerationParametersRepositoryInstance;
  dal::repositories::HarborGenerationParametersRepositoryInterface* harborGenerationParametersRepository;

  std::default_random_engine rng;

public:
  HarborGenerator()
    : harborGenerationParametersRepository(&harborGenerationParametersRepositoryInstance)
  {
    rng.seed(time(0));
  }

  HarborGenerator(
    dal::repositories::HarborGenerationParametersRepositoryInterface* harborGenerationParametersRepository)
    : harborGenerationParametersRepository(harborGenerationParametersRepository)
  {
    rng.seed(time(0));
  }

  models::Harbor GenerateRandomHarbor()
  {
    return GenerateHarbor(harborGenerationParametersRepository->GetRandomHarborGenerationParameters());
  }

  models::Harbor GenerateHarbor(const models::HarborGenerationParameters& parameters)
  {
    models::Harbor harbor;

    strncpy(harbor.name, parameters.harborName, sizeof(harbor.name));

    for (unsigned int i = 0; i < 15; ++i)
    {
      strncpy(harbor.goods[i].cargo.name,
              parameters.cargoGenerationParameters[i].cargoName,
              sizeof(harbor.goods[i].cargo.name));

      std::uniform_int_distribution<int> rngDistribution(parameters.cargoGenerationParameters[i].priceMin,
                                                         parameters.cargoGenerationParameters[i].priceMax);

      harbor.goods[i].price = rngDistribution(rng);
    }

    return harbor;
  }
};
}
}

#endif // LIBTURADOR_TURA_DOMAIN_HARBORGENERATOR_HPP_INCLUDED
