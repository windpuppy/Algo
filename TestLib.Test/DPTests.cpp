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

	TEST(DPTests, LongestConsecutiveOnes) {
		vector<int> input{ 1, 0, 0, 1, 1, 0, 1, 1, 1, 0 };
		auto res = obj.longestConsecutiveOnes(input);
		EXPECT_EQ(res, 3);
		res = obj.longestConsecutiveOnes2(input); // can absorb 1 zero
		EXPECT_EQ(res, 6);
		res = obj.longestConsecutiveOnes3(input, 2); // can absorb k zeros
		EXPECT_EQ(res, 7);
	}

	TEST(DPTests, LongestconsecutiveSequence) {
		auto res = obj.longestConsecutiveSequence(vector<int>{100, 4, 200, 1, 3, 2});
		EXPECT_EQ(res, 4); // [4 1 3 2]
	}

	TEST(DPTests, LongestCrossOfOnes) {
		vector<vector<int>> matrix{
			{0, 0, 0, 0},
			{1, 1, 1, 1},
			{0, 1, 1, 1},
			{1, 0, 1, 1} };
		auto res = obj.longestCrossOfOnes(matrix);
		EXPECT_EQ(res, 2);

		vector<vector<int>> matrix2{
			{1,1,1,0,1},
			{1,0,1,1,1},
			{1,1,1,1,1},
			{1,0,1,1,0},
			{0,0,1,1,0} };
		res = obj.longestCrossOfOnes(matrix2);
		EXPECT_EQ(res, 3);
	}

	TEST(DPTests, LongestXOfOnes) {
		vector<vector<int>> matrix{
			{0, 0, 0, 0},
			{1, 1, 1, 1},
			{0, 1, 1, 1},
			{1, 0, 1, 1} };
		auto res = obj.longestXOfOnes(matrix);
		EXPECT_EQ(res, 2);
	}

	TEST(DPTests, LargestSubarraySum) {
		// Largest subarray sum
		{
			vector<int> nums{ 1, 2, 4, -1, -2, 10, -1, -100, -1, 10, 20 };
			auto res = obj.largestSubArraySum(nums);
			EXPECT_EQ(res, 30);
			nums = vector<int>{ 1, 4, -2, -8, 10, 3, 2, 9, -5 };
			res = obj.largestSubArraySum(nums);
			EXPECT_EQ(res, 24);
		}

		// Largest subarray sum - return[sum, left, right]
		{
			vector<int> nums{ 1, 2, 4, -1, -2, 10, -1, -100, -1, 10, 20 };
			auto res = obj.largestSubArraySum2(nums); // 30, 9, 10
			vector<int> expected{ 30, 9, 10 };
			EXPECT_EQ(res, expected);

			nums = vector<int>{ 1, 4, -2, -8, 10, 3, 2, 9, -5 };
			res = obj.largestSubArraySum2(nums);
			expected = vector<int>{ 24, 4, 7 };
			EXPECT_EQ(res, expected);
		}

		// Largest subarray sum - circular array
		{
			vector<int> nums{ -1, -2, 10, 11, 12, -2, -1 };
			auto res = obj.largestSubArraySum3(nums);
			EXPECT_EQ(res, 33);

			nums = vector<int>{ 10, -1, -2, -3, 10 };
			res = obj.largestSubArraySum3(nums);
			EXPECT_EQ(res, 14);

			nums = vector<int>{ -1, -2, -3 };
			res = obj.largestSubArraySum3(nums);
			EXPECT_EQ(res, -1);
		}
	}

	TEST(DPTests, LargestSubmatrixSum) {
		vector<vector<int>> matrix{
			{2, -1, 2, 1, -3},
			{0, -2, -1, 2, 1},
			{3, 2, 1, -3, -2} };
		auto res = obj.largestSubmatrixSum(matrix); // O(n^4) solution
		EXPECT_EQ(res, 6);
		res = obj.largestSubmatrixSum2(matrix); // O(n^3) solution
		EXPECT_EQ(res, 6);
	}

	TEST(DPTests, LargestSubarrayProduct) {
		vector<double> input{ 4,-2,-3,-2,3 };
		auto res = obj.largestSubArrayProduct(input);
		EXPECT_EQ(res, 24);
		res = obj.largestSubArrayProduct2(input); // just an space O(1) optimized solution
		EXPECT_EQ(res, 24);
	}

	TEST(DPTests, LargestSubmatrixProduct) {
		vector<vector<double>> matrix{ {1, -0.2, 3, 2}, {-4, 1, -1, 1}, {-3, 2, 2, 2}, {-1, 1, 1, 1} };
		auto res = obj.largestSubmatrixProduct(matrix);
		EXPECT_DOUBLE_EQ(res, 115.2);
	}
}
