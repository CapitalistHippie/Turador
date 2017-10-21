#ifndef LIBTURADOR_TESTS_MOCKS_MOCKHARBORREPOSITORY_H_INCLUDED
#define LIBTURADOR_TESTS_MOCKS_MOCKHARBORREPOSITORY_H_INCLUDED

#include <gmock/gmock.h>

#include <tura/models/harbor.h>

#include <tura/harborrepositoryinterface.h>

class MockHarborRepository : public HarborRepositoryInterface
{
public:
  MOCK_CONST_METHOD0(GetHarbors, tura::models::Harbor*());
  MOCK_CONST_METHOD0(GetAmountOfHarbors, unsigned int());
};

#endif // LIBTURADOR_TESTS_MOCKS_MOCKHARBORREPOSITORY_H_INCLUDED
