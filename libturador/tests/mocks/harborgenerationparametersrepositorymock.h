#ifndef LIBTURADOR_TESTS_MOCKS_HARBORGENERATIONPARAMETERSREPOSITORYMOCK_H_INCLUDED
#define LIBTURADOR_TESTS_MOCKS_HARBORGENERATIONPARAMETERSREPOSITORYMOCK_H_INCLUDED

#include "tura/dal/repositories/harborgenerationparametersrepositoryinterface.h"
#include "tura/domain/models/harborgenerationparameters.h"

class HarborGenerationParametersRepositoryMock : tura::dal::repositories::HarborGenerationParametersRepositoryInterface
{
public:
  MOCK_CONST_METHOD0(GetHarborGenerationParametersCount, unsigned int());
  MOCK_CONST_METHOD1(
    GetHarborGenerationParametersByName,
    tura::domain::models::HarborGenerationParameters(const char* const harborGenerationParametersName));
  MOCK_CONST_METHOD1(GetHarborGenerationParametersByIndex,
                     tura::domain::models::HarborGenerationParameters(unsigned int index));
  MOCK_CONST_METHOD0(GetRandomHarborGenerationParameters, tura::domain::models::HarborGenerationParameters());
};

#endif // LIBTURADOR_TESTS_MOCKS_HARBORGENERATIONPARAMETERSREPOSITORYMOCK_H_INCLUDED
