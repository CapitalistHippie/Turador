#ifndef LIBTURADOR_TURA_DOMAIN_HARBORGENERATOR_HPP_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_HARBORGENERATOR_HPP_INCLUDED

#include <chrono>
#include <random>

#include "tura/dal/repositories/harborgenerationparametersfilerepository.h"
#include "tura/dal/repositories/harborgenerationparametersrepositoryinterface.h"
#include "tura/domain/constants.h"
#include "tura/domain/harborgeneratorinterface.h"
#include "tura/domain/models/harbor.h"
#include "tura/domain/models/harborcargo.h"
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
    auto seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());
    rng.seed(seed);
  }

  HarborGenerator(
    dal::repositories::HarborGenerationParametersRepositoryInterface* harborGenerationParametersRepository)
    : harborGenerationParametersRepository(harborGenerationParametersRepository)
  {
    auto seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());
    rng.seed(seed);
  }

  models::Harbor GenerateRandomHarbor()
  {
    return GenerateHarbor(harborGenerationParametersRepository->GetRandomHarborGenerationParameters());
  }

  models::Harbor GenerateHarbor(const models::HarborGenerationParameters& parameters)
  {
    for (const auto& parameters : parameters.cargoGenerationParameters)
    {
      if (parameters.priceMin > parameters.priceMax)
      {
        throw std::system_error(std::make_error_code(Error::InvalidArgument),
                                "priceMin can not be higher than priceMax.");
      }

      if (parameters.amountMin > parameters.amountMax)
      {
        throw std::system_error(std::make_error_code(Error::InvalidArgument),
                                "amountMin can not be higher than amountMax.");
      }
    }

    models::Harbor harbor;

    harbor.name = parameters.harborName;

    // Cargo.
    for (const auto& parameters : parameters.cargoGenerationParameters)
    {
      tura::domain::models::HarborCargo cargo;
      cargo.cargo.name = parameters.cargoName;

      // Price.
      std::uniform_int_distribution<int> rngPriceDistribution(parameters.priceMin, parameters.priceMax);
      cargo.price = rngPriceDistribution(rng);

      // Amount.
      std::uniform_int_distribution<int> rngAmountDistribution(parameters.amountMin, parameters.amountMax);
      cargo.cargo.amount = rngAmountDistribution(rng);

      harbor.goods.Add(cargo);
    }

    // Cannons for sale.
    std::uniform_int_distribution<int> rngCannonsForSaleAmountDistribution(Constants::HarborLightCannonsForSaleMin,
                                                                           Constants::HarborLightCannonsForSaleMax);
    for (unsigned int i = 0; i < rngCannonsForSaleAmountDistribution(rng); ++i)
    {
      models::Cannon cannon;
      cannon.cannonClass = models::CannonClass::Light;
      harbor.cannonsForSale.Add(cannon);
    }

    rngCannonsForSaleAmountDistribution = std::uniform_int_distribution<int>(Constants::HarborMediumCannonsForSaleMin,
                                                                             Constants::HarborMediumCannonsForSaleMax);
    for (unsigned int i = 0; i < rngCannonsForSaleAmountDistribution(rng); ++i)
    {
      models::Cannon cannon;
      cannon.cannonClass = models::CannonClass::Medium;
      harbor.cannonsForSale.Add(cannon);
    }

    rngCannonsForSaleAmountDistribution = std::uniform_int_distribution<int>(Constants::HarborHeavyCannonsForSaleMin,
                                                                             Constants::HarborHeavyCannonsForSaleMax);
    for (unsigned int i = 0; i < rngCannonsForSaleAmountDistribution(rng); ++i)
    {
      models::Cannon cannon;
      cannon.cannonClass = models::CannonClass::Heavy;
      harbor.cannonsForSale.Add(cannon);
    }

    return harbor;
  }
};
}
}

#endif // LIBTURADOR_TURA_DOMAIN_HARBORGENERATOR_HPP_INCLUDED
