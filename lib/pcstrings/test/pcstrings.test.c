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

TEST_SUITE(PCStrings)
{
        ADD_TEST(cb_read_uchar_from_string);
        ADD_TEST(cb_uchar_to_string);
}