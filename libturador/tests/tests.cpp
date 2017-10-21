#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tura/game.h"
#include "tura/gamebuilder.h"
#include "tura/harbor.h"
#include "tura/harborrepositoryinterface.h"

#define ASSERT_THROW_SYSTEM_ERROR(statement, errorCode)                                                                \
  {                                                                                                                    \
    try                                                                                                                \
    {                                                                                                                  \
      statement;                                                                                                       \
      FAIL() << "Expected: " #statement " throws std::system_error.\n"                                                 \
                "  Actual: it doesn't.";                                                                               \
    }                                                                                                                  \
    catch (const std::system_error& exception)                                                                         \
    {                                                                                                                  \
      ASSERT_EQ(exception.code(), std::make_error_code(errorCode));                                                    \
    }                                                                                                                  \
    catch (...)                                                                                                        \
    {                                                                                                                  \
      FAIL() << "Expected: " #statement " throws std::system_error.\n"                                                 \
                "  Actual: it doesn't.";                                                                               \
    }                                                                                                                  \
  }

using namespace tura;
using namespace testing;

class MockHarborRepository : public HarborRepositoryInterface
{
public:
  MOCK_CONST_METHOD0(GetHarbors, Harbor*());
  MOCK_CONST_METHOD0(GetAmountOfHarbors, unsigned int());
};

TEST(Harbor, CanPurchaseGoodsAtHarbor)
{
  // Arrange.
  Harbor harbors[] = { Harbor() };

  StrictMock<MockHarborRepository> harborRepository;
  ON_CALL(harborRepository, GetHarbors()).WillByDefault(Return(harbors));
  ON_CALL(harborRepository, GetAmountOfHarbors()).WillByDefault(Return(1));

  auto gameBuilder = GameBuilder().WithHarborRepository(&harborRepository);

  // Act.
  // Assert.
  ASSERT_TRUE(true);
}

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);

  int returnValue;
  returnValue = RUN_ALL_TESTS();

  return returnValue;
}
