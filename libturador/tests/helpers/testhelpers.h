#ifndef LIBTURADOR_TESTS_TESTHELPERS_H_INCLUDED
#define LIBTURADOR_TESTS_TESTHELPERS_H_INCLUDED

#define ASSERT_THROW_SYSTEM_ERROR(statement, errorCode)                                                                \
  \
{                                                                                                                   \
    try                                                                                                                \
    {                                                                                                                  \
      statement;                                                                                                       \
      FAIL() << "Expected: " #statement " throws std::system_error."                                                   \
             << "\n  Actual: it doesn't.";                                                                             \
    }                                                                                                                  \
    catch (const std::system_error& exception)                                                                         \
    {                                                                                                                  \
      auto code = std::make_error_code(errorCode);                                                                     \
      ASSERT_EQ(exception.code(), code) << "Expected: " #statement " throws std::system_error with error code: "       \
                                        << code << "\n  Actual error code: " << exception.code() << ".";               \
    }                                                                                                                  \
    catch (...)                                                                                                        \
    {                                                                                                                  \
      FAIL() << "Expected: " #statement " throws std::system_error."                                                   \
             << "\n  Actual: a different exception was thrown.";                                                       \
    }                                                                                                                  \
  \
}

#define EXPECT_THROW_SYSTEM_ERROR(statement, errorCode)                                                                \
  \
{                                                                                                                   \
    try                                                                                                                \
    {                                                                                                                  \
      statement;                                                                                                       \
      ADD_FAILURE() << "Expected: " #statement " throws std::system_error."                                            \
                    << "\n  Actual: it doesn't.";                                                                      \
    }                                                                                                                  \
    catch (const std::system_error& exception)                                                                         \
    {                                                                                                                  \
      auto code = std::make_error_code(errorCode);                                                                     \
      EXPECT_EQ(exception.code(), code) << "Expected: " #statement " throws std::system_error with error code: "       \
                                        << code << "\n  Actual error code: " << exception.code() << ".";               \
    }                                                                                                                  \
    catch (...)                                                                                                        \
    {                                                                                                                  \
      ADD_FAILURE() << "Expected: " #statement " throws std::system_error."                                            \
                    << "\n  Actual: a different exception was thrown.";                                                \
    }                                                                                                                  \
  \
}

#endif // LIBTURADOR_TESTS_TESTHELPERS_H_INCLUDED
