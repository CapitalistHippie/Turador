#ifndef LIBTURADOR_TESTS_MOCKS_HARBORGENERATORYMOCK_H_INCLUDED
#define LIBTURADOR_TESTS_MOCKS_HARBORGENERATORYMOCK_H_INCLUDED

#include <gmock/gmock.h>

#include <tura/domain/harborgeneratorinterface.h>
#include <tura/domain/models/harbor.h>
#include <tura/domain/models/harborcargogenerationparameters.h>

class HarborGeneratorMock : public tura::domain::HarborGeneratorInterface
{
public:
  MOCK_METHOD0(GenerateRandomHarbor, tura::domain::models::Harbor());
  MOCK_METHOD1(GenerateHarbor,
               tura::domain::models::Harbor(const tura::domain::models::HarborGenerationParameters& parameters));
};

#endif // LIBTURADOR_TESTS_MOCKS_HARBORGENERATORYMOCK_H_INCLUDED
