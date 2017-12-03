#ifndef LIBTURADOR_TESTS_MOCKS_HARBORGENERATORYMOCK_H_INCLUDED
#define LIBTURADOR_TESTS_MOCKS_HARBORGENERATORYMOCK_H_INCLUDED

#include <gmock/gmock.h>

#include <tura/domain/harborgeneratorinterface.h>
#include <tura/domain/models/harbor.h>
#include <tura/domain/models/harborcargogenerationparameters.h>
#include <tura/helpers/chararray.hpp>

class HarborGeneratorMock : public tura::domain::HarborGeneratorInterface
{
public:
  MOCK_CONST_METHOD0(GenerateRandomHarbor, tura::domain::models::Harbor());
  MOCK_CONST_METHOD1(GenerateHarborByName,
                     tura::domain::models::Harbor(const tura::helpers::CharArray<64>& harborName));
  MOCK_CONST_METHOD1(GenerateHarbor,
                     tura::domain::models::Harbor(const tura::domain::models::HarborGenerationParameters& parameters));
};

#endif // LIBTURADOR_TESTS_MOCKS_HARBORGENERATORYMOCK_H_INCLUDED
