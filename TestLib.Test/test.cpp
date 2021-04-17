#include "gtest/gtest.h"
#include "../Array/Array.h"

namespace ArrayTests {

    Array obj;
    TEST(ArrayTests, Merge2SortedArrays) {
        vector<int> a{ 1, 3, 5, 10, 100, 2000 };
        vector<int> b{ 50, 99, 1999, 5000 };
        auto res = obj.mergeTwoSortedArrays(a, b);
        vector<int> c{1, 3, 5, 10, 50, 99, 100, 1999, 2000, 5000};
        EXPECT_EQ(c, res);

        res = obj.mergeTwoSortedArraysIter(a, b);
        EXPECT_EQ(c, res);
    }

    TEST(ArrayTests, Merge2SortedArrays2)
    {
        vector<int> a{ 1, 2, 3, 0, 0, 0 };
        vector<int> b{ 2, 5, 6 };
        obj.mergeTwoSortedArrays2(a, 3, b, 3);
        vector<int> c{ 1, 2, 2, 3, 5, 6 };
        EXPECT_EQ(c, a);
    }

    TEST(ArrayTests, Merge2SortedArrays3)
    {
        vector<int> a{ 1, 2, 3, 0, 0, 0 };
        vector<int> b{ 2, 5, 6 };
        obj.mergeTwoSortedArrays3(a, 3, b, 3);
        vector<int> c{ 1, 2, 2, 3, 5, 6 };
        EXPECT_EQ(c, a);
    }

    TEST(ArrayTests, CommonElements)
    {
        vector<int> a{ 1, 2, 3 };
        vector<int> b{ 3, 1, 4 };
        auto res = obj.commonNumbersOfTwoArrays(a, b);
        vector<int> c{ 1, 3 };
        EXPECT_EQ(c, res);

        res = obj.commonNumbersOfTwoArrays2(a, b);
        EXPECT_EQ(c, res);
    }

    TEST(ArrayTests, CommonElementsDuplicate)
    {
        vector<int> a{ 1, 2, 3, 2 };
        vector<int> b{ 3, 4, 2, 2, 2 };
        auto res = obj.commonNumbersOfTwoArrays3(a, b);
    }

    TEST(ArrayTests, RomanToIngeter)
    {
        auto res = obj.intToRoman(4);
        EXPECT_EQ("IV", res);
        res = obj.intToRoman(9);
        EXPECT_EQ("IX", res);
        res = obj.intToRoman(53);
        EXPECT_EQ("LIII", res);
        res = obj.intToRoman(3999);
        EXPECT_EQ("MMMCMXCIX", res);
        res = obj.intToRoman(9843);
        EXPECT_EQ("MMMMMMMMMDCCCXLIII", res);
    }

    TEST(ArrayTests, IntegerToRoman)
    {
        auto res = obj.romanToInt("III");
        EXPECT_EQ(3, res);
        res = obj.romanToInt("IV");
        EXPECT_EQ(4, res);
        res = obj.romanToInt("IX");
        EXPECT_EQ(9, res);
        res = obj.romanToInt("LVIII");
        EXPECT_EQ(58, res);
        res = obj.romanToInt("MCMXCIV");
        EXPECT_EQ(1994, res);
    }

    TEST(ArrayTests, TwoSum)
    {
        auto res = obj.TwoSum(vector<int>{2, 4, 2, 1}, 4);
        EXPECT_EQ(true, res);
        res = obj.TwoSum(vector<int>{2, 4, 1}, 4);
        EXPECT_EQ(false, res);
    }
}
