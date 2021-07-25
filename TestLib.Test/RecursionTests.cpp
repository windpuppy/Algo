#include "TestFixture.h"
#include <Recursion/Recursion.h>

namespace RecursionTests {

    Recursion obj;

    TEST(RecursionTests, fibonacci) {
        int res = obj.fibonacci(8);
        EXPECT_EQ(res, 21);
        res = obj.fibonacci(1);
        EXPECT_EQ(res, 1);
    }

    TEST(RecursionTests, power) {
        long res = obj.power(2, 5);
        EXPECT_EQ(res, 32);
        res = obj.power(2, 0);
        EXPECT_EQ(res, 1);

        res = obj.power_naive(2, 5);
        EXPECT_EQ(res, 32);
    }

    TEST(RecursionTests, StringAbbrevMatch) {
        bool res = obj.stringAbbreviationMatching("book", "4");
        EXPECT_TRUE(res);
        res = obj.stringAbbreviationMatching("book", "b3");
        EXPECT_TRUE(res);
        res = obj.stringAbbreviationMatching("book", "b2k");
        EXPECT_TRUE(res);
        res = obj.stringAbbreviationMatching("lovercom", "3er3");
        EXPECT_TRUE(res);
    }

}
