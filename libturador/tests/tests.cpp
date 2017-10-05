#include <gtest/gtest.h>

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

TEST(Test, TestTesting)
{
  // Arrange.
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
