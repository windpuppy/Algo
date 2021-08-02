#include "TestFixture.h"
#include <String/String.h>

namespace StringTests {

    String obj;

    TEST(StringTests, TopKFrequent) {
        vector<string> input{ "d","a","c","b","d","a","b","b","a","d","d","a","d" };
        auto res = obj.topKFrequentWords(input, 5);
        vector<string> expected{"d", "a", "b", "c"};
        EXPECT_EQ(res, expected);
    }

    TEST(StringTests, MissingNumber) {
        vector<int> input{ 12, 11, 10, 9, 4, 5, 6, 7, 1, 3, 8 };
        auto res = obj.missingNumber(input);
        EXPECT_EQ(res, 2);
    }

    TEST(StringTests, CommonNumbers) {
        vector<int> a{ 1, 1, 2, 3, 3 };
        vector<int> b{ 2, 3, 3, 4, 5 };
        auto res = obj.commonNumbers(a, b);
        vector<int> expected{ 2, 3, 3 };
        EXPECT_EQ(res, expected);
    }

    TEST(StringTests, RemoveCertainCharacters) {
        auto res = obj.removeCertainCharacters("abcde", "cef");
        EXPECT_EQ(res, "abd");
    }

    TEST(StringTests, RemoveSpaces) {
        auto res = obj.removeSpaces("  i love coding   ");
        EXPECT_EQ(res, "i love coding");
    }

    TEST(StringTest, DedupAdjacent) {
        // keep 1 of each
        auto res = obj.removeAdjacentRepeatedChars("aaabbbc");
        EXPECT_EQ(res, "abc");

        // keep 2 of each
        res = obj.removeAdjacentRepeatedChars2("aaabbbc");
        EXPECT_EQ(res, "aabbc");

        // keep none (input is sorted)
        res = obj.removeAdjacentRepeatedChars3("aaabbbc");
        EXPECT_EQ(res, "c");

        // keep none (input not sorted)
        res = obj.removeAdjacentRepeatedChars4("abbbaaccz"); // "abbbaaccz" -> "aaaccz" -> "ccz" -> "z"
        EXPECT_EQ(res, "z");
        res = obj.removeAdjacentRepeatedChars4("aabccdc"); // "aabccdc" -> "bccdc" -> "bdc"
        EXPECT_EQ(res, "bdc");
        res = obj.removeAdjacentRepeatedChars4("aaaaa"); // "aaaaa" -> ""
        EXPECT_EQ(res, "");
    }

    TEST(StringTests, IsSubString) {
        auto res = obj.isSubstring("abcde", "bcd");
        EXPECT_TRUE(res);
        res = obj.isSubstring_RabinKarp("abcde", "bcd");
        EXPECT_TRUE(res);
    }

    TEST(StringTests, RightShift) {
        auto res = obj.rightShift("abcdefg", 3);
        EXPECT_EQ(res, "efgabcd");
        res = obj.rightShift("abcdefg", 10);
        EXPECT_EQ(res, "efgabcd");
    }
}
