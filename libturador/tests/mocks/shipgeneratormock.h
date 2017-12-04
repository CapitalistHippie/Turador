#ifndef LIBTURADOR_TESTS_MOCKS_SHIPGENERATORMOCK_H_INCLUDED
#define LIBTURADOR_TESTS_MOCKS_SHIPGENERATORMOCK_H_INCLUDED

#include <gmock/gmock.h>

#include <tura/domain/models/ship.h>
#include <tura/domain/shipgeneratorinterface.h>

class ShipGeneratorMock : public tura::domain::ShipGeneratorInterface
{
public:
  MOCK_CONST_METHOD1(GenerateShipByShipTypeName, tura::domain::models::Ship(const char* const shipTypeName));
  MOCK_CONST_METHOD1(GenerateShipByShipType,
                     tura::domain::models::Ship(const tura::domain::models::ShipType& shipType));
  MOCK_CONST_METHOD0(GenerateRandomEnemyShip, tura::domain::models::Ship());
};

#endif // LIBTURADOR_TESTS_MOCKS_SHIPGENERATORMOCK_H_INCLUDED
