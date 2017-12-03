#ifndef LIBTURADOR_TURA_DOMAIN_HARBORGENERATOR_HPP_INCLUDED
#define LIBTURADOR_TURA_DOMAIN_HARBORGENERATOR_HPP_INCLUDED

#include <chrono>
#include <random>

#include "tura/dal/repositories/harborgenerationparametersfilerepository.h"
#include "tura/dal/repositories/harborgenerationparametersrepositoryinterface.h"
#include "tura/dal/repositories/sailroutefilerepository.hpp"
#include "tura/dal/repositories/sailrouterepository.h"
#include "tura/dal/repositories/shiptypefilerepository.h"
#include "tura/dal/repositories/shiptyperepositoryinterface.h"
#include "tura/domain/constants.h"
#include "tura/domain/harborgeneratorinterface.h"
#include "tura/domain/models/harbor.h"
#include "tura/domain/models/harborcargo.h"
#include "tura/domain/models/harborgenerationparameters.h"
#include "tura/helpers/array.hpp"

namespace tura
{
namespace domain
{
class HarborGenerator : public HarborGeneratorInterface
{
private:
  dal::repositories::HarborGenerationParametersFileRepository harborGenerationParametersRepositoryInstance;
  dal::repositories::HarborGenerationParametersRepositoryInterface* harborGenerationParametersRepository;

  dal::repositories::SailRouteFileRepository sailRouteRepositoryInstance;
  dal::repositories::SailRouteRepository* sailRouteRepository;

  dal::repositories::ShipTypeFileRepository shipTypeRepositoryInstance;
  dal::repositories::ShipTypeRepositoryInterface* shipTypeRepository;

  std::default_random_engine rng;

public:
  HarborGenerator()
    : harborGenerationParametersRepository(&harborGenerationParametersRepositoryInstance)
    , sailRouteRepository(&sailRouteRepositoryInstance)
    , shipTypeRepository(&shipTypeRepositoryInstance)
  {
    auto seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());
    rng.seed(seed);
  }

  HarborGenerator(
    dal::repositories::HarborGenerationParametersRepositoryInterface* harborGenerationParametersRepository,
    dal::repositories::SailRouteRepository* sailRouteRepository,
    dal::repositories::ShipTypeRepositoryInterface* shipTypeRepository)
    : harborGenerationParametersRepository(harborGenerationParametersRepository)
    , sailRouteRepository(sailRouteRepository)
    , shipTypeRepository(shipTypeRepository)
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
      std::uniform_int_distribution<unsigned int> rngPriceDistribution(parameters.priceMin, parameters.priceMax);
      cargo.price = rngPriceDistribution(rng);

      // Amount.
      std::uniform_int_distribution<unsigned int> rngAmountDistribution(parameters.amountMin, parameters.amountMax);
      cargo.cargo.amount = rngAmountDistribution(rng);

      harbor.goods.Add(cargo);
    }

    // Cannons for sale.
    std::uniform_int_distribution<unsigned int> rngCannonsForSaleAmountDistribution(
      Constants::HarborLightCannonsForSaleMin, Constants::HarborLightCannonsForSaleMax);
    for (unsigned int i = 0; i < rngCannonsForSaleAmountDistribution(rng); ++i)
    {
      models::Cannon cannon;
      cannon.cannonClass = models::CannonClass::Light;
      harbor.cannonsForSale.Add(cannon);
    }

    rngCannonsForSaleAmountDistribution = std::uniform_int_distribution<unsigned int>(
      Constants::HarborMediumCannonsForSaleMin, Constants::HarborMediumCannonsForSaleMax);
    for (unsigned int i = 0; i < rngCannonsForSaleAmountDistribution(rng); ++i)
    {
      models::Cannon cannon;
      cannon.cannonClass = models::CannonClass::Medium;
      harbor.cannonsForSale.Add(cannon);
    }

    rngCannonsForSaleAmountDistribution = std::uniform_int_distribution<unsigned int>(
      Constants::HarborHeavyCannonsForSaleMin, Constants::HarborHeavyCannonsForSaleMax);
    for (unsigned int i = 0; i < rngCannonsForSaleAmountDistribution(rng); ++i)
    {
      models::Cannon cannon;
      cannon.cannonClass = models::CannonClass::Heavy;
      harbor.cannonsForSale.Add(cannon);
    }

    // Ships for sale.
    auto shipTypeCount = shipTypeRepository->GetShipTypeCount();
    helpers::Array<unsigned int, 64> randomNumbersSource;
    for (unsigned int i = 0; i < shipTypeCount; ++i)
    {
      randomNumbersSource.Add(i);
    }

    for (unsigned int i = 0; i < Constants::HarborShipsForSale; ++i)
    {
      std::uniform_int_distribution<unsigned int> dist(0, randomNumbersSource.size() - 1);
      auto shipTypeIndex = randomNumbersSource[dist(rng)];

      harbor.shipsForSale.Add(shipTypeRepository->GetShipTypeByIndex(shipTypeIndex));

      randomNumbersSource.Remove(shipTypeIndex);
    }

    // Sail routes.
    harbor.sailRoutes = sailRouteRepository->GetSailRoutesFromHarbor(harbor.name);

    return harbor;
  }
};
}
}

#endif // LIBTURADOR_TURA_DOMAIN_HARBORGENERATOR_HPP_INCLUDED
