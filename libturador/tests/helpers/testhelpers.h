#ifndef LIBTURADOR_TESTS_TESTHELPERS_H_INCLUDED
#define LIBTURADOR_TESTS_TESTHELPERS_H_INCLUDED

#define ASSERT_THROW_SYSTEM_ERROR(statement, errorCode)                                                                \
  \
{                                                                                                                   \
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
  \
}

#endif // LIBTURADOR_TESTS_TESTHELPERS_H_INCLUDED
