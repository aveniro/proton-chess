#include "pcmath.h"
#include "scpunitc.h"

TEST(pcpow)
{
    ASSERT_EQ_MSG(pcpow(1, 0), 1, "1^0 == 1.");
    ASSERT_EQ_MSG(pcpow(5, 2), 25, "5^2 == 25.");
    ASSERT_EQ_MSG(pcpow(0, 10), 0, "0^10 == 0.");
    ASSERT_EQ_MSG(pcpow(10, 5), 100000, "10^5 == 100000.");
    ASSERT_EQ_MSG(pcpow(7, 2), 49, "7^2 == 49.");
    ASSERT_EQ_MSG(pcpow(2, 6), 64, "2^6 == 64.");
}

TEST_SUITE(PCMath)
{
    ADD_TEST(pcpow);
}