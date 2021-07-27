#include "TestFixture.h"
#include <Array/Array.h>

namespace ArrayTests {

    Array obj;

    class example {
    public:
        int* val;
    };
    TEST(ArrayTests, Merge2SortedArrays) {
        std::shared_ptr<example> e1;
        std::shared_ptr<example> e2;
        std::shared_ptr<example> e3;

        std::vector<std::shared_ptr<example>*> vec { &e1, &e2, &e3 };
        for(auto &n : vec) {
            *n = std::make_shared<example>();
            (*n)->val = new int[2]{ 1, 2 };
        }

        for (auto i = 0; i < vec.size(); ++i) {
            *vec[i] = std::make_shared<example>();
            (*vec[i])->val = new int[2]{ 3, 4 };
        }

        int g1 = e1->val[0];
        int g2 = e1->val[1];
        int g3 = e2->val[0];
        int g4 = e2->val[1];
        int g5 = e3->val[0];
        int g6 = e3->val[1];


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
        vector<int> c{ 2, 2, 3 };
        EXPECT_EQ(c, res);
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

    TEST(ArrayTests, TwoSum_Values_Any)
    {
        auto res = obj.TwoSum_Values_Any(vector<int>{2, 4, 2, 1}, 4);
        EXPECT_EQ(true, res);
        res = obj.TwoSum_Values_Any(vector<int>{2, 4, 1}, 4);
        EXPECT_EQ(false, res);
    }

    TEST(ArrayTests, TwoSum_Indices_Any)
    {
        auto res = obj.TwoSum_Indices_Any(vector<int>{2, 4, 2, 1, 3}, 4);
        vector<int> a{ 0, 2 };
        EXPECT_EQ(a, res);
    }

    TEST(ArrayTests, TwoSum_Indices_All)
    {
        auto res = obj.TwoSum_Indices_All(vector<int>{1, 4, 0, 2, 3, 4}, 5);
        vector<vector<int>> a{ vector<int>{0, 1}, vector<int>{3, 4}, vector<int>{0, 5} };
        EXPECT_EQ(res, a);
    }

    TEST(ArrayTests, TwoSum_Values_Dedup)
    {
        auto res = obj.TwoSum_Values_Dedup(vector<int>{1, 4, 0, 2, 3, 4}, 5);
        vector<vector<int>> a{ vector<int>{1, 4}, vector<int>{2, 3} };
        EXPECT_EQ(res, a);
    }

    TEST(ArrayTests, TwoSum_Values_Closest)
    {
        auto res = obj.TwoSum_Values_Closest(vector<int>{1, 4, 7, 13}, 7); // 1, 7
        vector<int> a{ 1, 7 };
        EXPECT_EQ(a, res);

        res = obj.TwoSum_Values_Closest(vector<int>{1, 2, 3}, -100);
        vector<int> b{ 1, 2 };
        EXPECT_EQ(b, res);
    }

    TEST(ArrayTests, TwoSum_NumPairs_Smaller)
    {
        auto res = obj.TwoSum_NumPairs_Smaller(vector<int>{1, 2, 3, 4, 5, 6}, 8);
        EXPECT_EQ(9, res);

        res = obj.TwoSum_NumPairs_Smaller(vector<int>{1, 5, 4, 3, 2, 6}, 8);
        EXPECT_EQ(9, res);
    }

    TEST(ArrayTests, TwoSum_MaxSum_Smaller)
    {
        auto res = obj.TwoSum_MaxSum_Smaller(vector<int>{2, 4, 6, 8, 10}, 11);
        EXPECT_EQ(10, res);

        res = obj.TwoSum_MaxSum_Smaller(vector<int>{2, 4, 6, 8, 10}, 9);
        EXPECT_EQ(8, res);
    }

    TEST(ArrayTests, TwoSum_TwoArrays)
    {
        auto res = obj.TwoSum_TwoArrays(vector<int>{3, 1, 5}, vector<int>{2, 8}, 7);
        EXPECT_TRUE(true);

        res = obj.TwoSum_TwoArrays(vector<int>{3, 1, 5}, vector<int>{2, 8}, 10);
        EXPECT_FALSE(res);
    }

    TEST(ArrayTests, ThreeSum_AllCombo)
    {
        vector<vector<int>> a{ vector<int>{1, 3, 4}, vector<int>{2, 2, 4} };
        auto res = obj.ThreeSum_AllCombo(vector<int>{1, 2, 2, 3, 2, 4}, 8);
        EXPECT_EQ(a, res);
    }

    TEST(ArrayTests, ThreeSum_ThreeArrays)
    {
        auto res = obj.ThreeSum_ThreeArrays(vector<int>{1, 3, 5}, vector<int>{8, 2}, vector<int>{3}, 14);
        EXPECT_TRUE(res);
    }
}
