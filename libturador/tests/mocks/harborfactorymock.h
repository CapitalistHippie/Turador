#ifndef LIBTURADOR_TESTS_MOCKS_HARBORFACTORYMOCK_H_INCLUDED
#define LIBTURADOR_TESTS_MOCKS_HARBORFACTORYMOCK_H_INCLUDED

#include <gmock/gmock.h>

#include <tura/models/harbor.h>

#include <tura/harborfactoryinterface.h>

class HarborFactoryMock : public tura::HarborFactoryInterface
{
public:
  MOCK_CONST_METHOD0(GetAmountOfHarbors, unsigned int());
  MOCK_CONST_METHOD1(GetHarborByName, tura::models::Harbor(const char* const harborName));
  MOCK_CONST_METHOD1(GetHarborByIndex, tura::models::Harbor(unsigned int index));
};

#endif // LIBTURADOR_TESTS_MOCKS_HARBORFACTORYMOCK_H_INCLUDED
