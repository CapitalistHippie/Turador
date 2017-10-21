#ifndef LIBTURADOR_TESTS_MOCKS_MOCKHARBORFACTORY_H_INCLUDED
#define LIBTURADOR_TESTS_MOCKS_MOCKHARBORFACTORY_H_INCLUDED

#include <gmock/gmock.h>

#include <tura/models/harbor.h>

#include <tura/harborfactoryinterface.h>

class MockHarborFactory : public HarborFactoryInterface
{
public:
  MOCK_CONST_METHOD0(GetAmountOfHarbors, unsigned int());
};

#endif // LIBTURADOR_TESTS_MOCKS_MOCKHARBORFACTORY_H_INCLUDED
