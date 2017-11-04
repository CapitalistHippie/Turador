#ifndef LIBTURADOR_TESTS_MOCKS_HARBORGENERATORYMOCK_H_INCLUDED
#define LIBTURADOR_TESTS_MOCKS_HARBORGENERATORYMOCK_H_INCLUDED

#include <gmock/gmock.h>

#include <tura/dal/models/harbor.h>
#include <tura/dal/models/harborcargogenerationparameters.h>
#include <tura/domain/harborgenerator.hpp>

class HarborGeneratorMock : public tura::domain::HarborGenerator
{
public:
  MOCK_METHOD0(GenerateRandomHarbor, tura::dal::models::Harbor());
  MOCK_METHOD1(GenerateHarbor,
               tura::dal::models::Harbor(const tura::dal::models::HarborGenerationParameters& parameters));
};

#endif // LIBTURADOR_TESTS_MOCKS_HARBORGENERATORYMOCK_H_INCLUDED
