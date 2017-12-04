#ifndef LIBTURADOR_TESTS_MOCKS_SHIPTYPEREPOSITORYMOCK_H_INCLUDED
#define LIBTURADOR_TESTS_MOCKS_SHIPTYPEREPOSITORYMOCK_H_INCLUDED

#include <gmock/gmock.h>

#include <tura/dal/repositories/shiptyperepositoryinterface.h>
#include <tura/domain/models/shiptype.h>

class ShipTypeRepositoryMock : public tura::dal::repositories::ShipTypeRepositoryInterface
{
public:
  MOCK_CONST_METHOD0(GetShipTypeCount, unsigned int());
  MOCK_CONST_METHOD1(GetShipTypeByName, tura::domain::models::ShipType(const char* const shipTypeName));
  MOCK_CONST_METHOD0(GetRandomShipType, tura::domain::models::ShipType());
};

#endif // LIBTURADOR_TESTS_MOCKS_SHIPTYPEREPOSITORYMOCK_H_INCLUDED
