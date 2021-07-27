#include "TestFixture.h"
#include <Recursion/Recursion.h>

namespace RecursionTests {

    Recursion obj;

    TEST(RecursionTests, Fibonacci) {
        int res = obj.fibonacci(8);
        EXPECT_EQ(res, 21);
        res = obj.fibonacci(1);
        EXPECT_EQ(res, 1);
    }

    TEST(RecursionTests, Power) {
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

    TEST(RecursionTests, SpiralTraverse) {
        vector<vector<int>> matrix{
            vector<int>{1, 2, 3, 4},
            vector<int>{5, 6, 7, 8},
            vector<int>{9, 10, 11, 12},
            vector<int>{13, 14, 15, 16},
        };
        auto res = obj.spiralTraverse(matrix);
        vector<int> expected{ 1, 2, 3, 4, 8, 12, 16, 15, 14, 13, 9, 5, 6, 7, 11, 10 };
        EXPECT_EQV(res, expected);
    }

    TEST(RecursionTests, SpiralTraverse2) {
        vector<vector<int>> matrix{
            vector<int>{1, 2, 3, 4},
            vector<int>{5, 6, 7, 8},
            vector<int>{9, 10, 11, 12}
        };
        auto res = obj.spiralTraverse2(matrix);
        vector<int> expected{ 1, 2, 3, 4, 8, 12, 11, 10, 9, 5, 6, 7};
        EXPECT_EQV(res, expected);
    }

}
