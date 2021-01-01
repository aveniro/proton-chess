#include "pcstrings.h"
#include "scpunitc.h"

TEST(cb_read_uchar_from_string)
{
        const char *test_string_1 = "100";
        ASSERT_EQ_MSG(cb_read_uchar_from_string(test_string_1, 0), 100, "Value should be 100.");

        const char *test_string_2 = "   211";
        ASSERT_EQ_MSG(cb_read_uchar_from_string(test_string_2, 3), 211, "Value should be 211.");

        const char *test_string_3 = "Agent 007, you are requested in the queen's office.";
        ASSERT_EQ_MSG(cb_read_uchar_from_string(test_string_3, 7), 7, "Value should be 7.");

        const char *test_string_4 = "28";
        ASSERT_EQ_MSG(cb_read_uchar_from_string(test_string_4, 0), 28, "Value should be 28.");

        const char *test_string_5 = "22";
        ASSERT_EQ_MSG(cb_read_uchar_from_string(test_string_5, 0), 22, "Value should be 22.");
}

TEST(cb_uchar_to_string)
{
        char string_buffer[4];

        cb_uchar_to_string(214, string_buffer, 4);
        ASSERT_STR_EQ_MSG(string_buffer, "214", "Value should be 214.");

        cb_uchar_to_string(0, string_buffer, 4);
        ASSERT_STR_EQ_MSG(string_buffer, "0", "Value should be 0.");

        cb_uchar_to_string(55, string_buffer, 4);
        ASSERT_STR_EQ_MSG(string_buffer, "55", "Value should be 55.");

        cb_uchar_to_string(178, string_buffer, 4);
        ASSERT_STR_EQ_MSG(string_buffer, "178", "Value should be 178.");

        cb_uchar_to_string(28, string_buffer, 4);
        ASSERT_STR_EQ_MSG(string_buffer, "28", "Value should be 28.");
}

TEST(is_char_uppercase)
{
    ASSERT_TRUE_MSG(is_char_uppercase('A'), "'A' is an uppercase letter.");
    ASSERT_TRUE_MSG(is_char_uppercase('D'), "'D' is an uppercase letter.");
    ASSERT_TRUE_MSG(is_char_uppercase('O'), "'O' is an uppercase letter.");
    ASSERT_TRUE_MSG(is_char_uppercase('P'), "'P' is an uppercase letter.");

    ASSERT_TRUE_MSG(!is_char_uppercase('j'), "'j' is a lowercase letter.");
    ASSERT_TRUE_MSG(!is_char_uppercase('k'), "'k' is a lowercase letter.");
    ASSERT_TRUE_MSG(!is_char_uppercase('w'), "'w' is a lowercase letter.");
    ASSERT_TRUE_MSG(!is_char_uppercase('m'), "'m' is a lowercase letter.");
}

TEST(is_char_lowercase)
{
    ASSERT_TRUE_MSG(!is_char_lowercase('A'), "'A' is an uppercase letter.");
    ASSERT_TRUE_MSG(!is_char_lowercase('D'), "'D' is an uppercase letter.");
    ASSERT_TRUE_MSG(!is_char_lowercase('O'), "'O' is an uppercase letter.");
    ASSERT_TRUE_MSG(!is_char_lowercase('P'), "'P' is an uppercase letter.");

    ASSERT_TRUE_MSG(is_char_lowercase('j'), "'j' is a lowercase letter.");
    ASSERT_TRUE_MSG(is_char_lowercase('k'), "'k' is a lowercase letter.");
    ASSERT_TRUE_MSG(is_char_lowercase('w'), "'w' is a lowercase letter.");
    ASSERT_TRUE_MSG(is_char_lowercase('m'), "'m' is a lowercase letter.");
}

TEST(is_char_digit)
{
    ASSERT_TRUE_MSG(is_char_digit('0'), "'0' is a digit.");
    ASSERT_TRUE_MSG(is_char_digit('7'), "'9' is a digit.");
    ASSERT_TRUE_MSG(is_char_digit('9'), "'9' is a digit.");
    ASSERT_TRUE_MSG(is_char_digit('1'), "'1' is a digit.");

    ASSERT_TRUE_MSG(!is_char_digit('x'), "'x' is not a digit.");
    ASSERT_TRUE_MSG(!is_char_digit('a'), "'a' is not a digit.");
    ASSERT_TRUE_MSG(!is_char_digit('p'), "'p' is not a digit.");
    ASSERT_TRUE_MSG(!is_char_digit('q'), "'q' is not a digit.");
}

TEST_SUITE(PCStrings)
{
        ADD_TEST(cb_read_uchar_from_string);
        ADD_TEST(cb_uchar_to_string);
        ADD_TEST(is_char_uppercase);
        ADD_TEST(is_char_lowercase);
        ADD_TEST(is_char_digit);
}