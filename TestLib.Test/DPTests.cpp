#include "TestFixture.h"
#include <DP/DP.h>

namespace DPTests {
	DynamicProgramming obj;

	TEST(DPTests, Fibonacci2) {
		auto res = obj.fibonacci2(0);
		EXPECT_EQ(res, 0);
		res = obj.fibonacci2(1);
		EXPECT_EQ(res, 1);
		res = obj.fibonacci2(2);
		EXPECT_EQ(res, 1);

		res = obj.fibonacci2(60);
		EXPECT_EQ(res, (long)1820529360);
		res = obj.fibonacci2_iter(60);
		EXPECT_EQ(res, (long)1820529360);
	}

	TEST(DPTests, longestAscendingSubArray) {
		vector<int> input{ 1, 2, 2, 3, 3, 4, 5, 6, 6, 7 };
		auto res = obj.longestAscendingSubArray(input); // 4
		EXPECT_EQ(res, 4);

		input = vector<int>{ 7, 2, 3, 1, 5, 8, 9, 6 };
		res = obj.longestAscendingSubArray(input);
		EXPECT_EQ(res, 4);
	}

	TEST(DPTests, longestAscendingSubSequence) {
		vector<int> input{ 7, 2, 3, 1, 5, 8, 9, 6 };
		vector<int> expected{ 2, 3, 5, 8, 9 };
		auto res = obj.longestAscendingSubSequence2(input);
		EXPECT_EQ(res, expected);

		res = obj.longestAscendingSubSequence2(input);
		EXPECT_EQ(res, expected);
		res = obj.longestAscendingSubSequence2({ 1 });
		EXPECT_EQ(res, vector<int>{1});
	}

	TEST(DPTests, LongestCommonSubstring) {
		auto res = obj.longestCommonSubstring("abcdefg", "bbcefgh");
		EXPECT_EQ(res, "efg");
		res = obj.longestCommonSubstring("aaaaaa", "bbaaba");
		EXPECT_EQ(res, "aa");
	}

	TEST(DPTests, LongestCommonSubsequence) {
		auto res = obj.longestCommonSubsequence("acbcf", "abcdaf");
		EXPECT_EQ(res, 4); // "abcf"
	}
}
