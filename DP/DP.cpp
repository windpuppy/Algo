#include "DP.h"
#include <cassert>

int main()
{
	DynamicProgramming obj;

	// Longest consecutive ones
	{
		vector<int> input{ 1, 0, 0, 1, 1, 0, 1, 1, 1, 0 };
		auto res = obj.longestConsecutiveOnes(input); // 3
		res = obj.longestConsecutiveOnes2(input); // 6
		res = obj.longestConsecutiveOnes3(input, 2); // 7
	}

	// Longest consecutive sequence
	{
		auto res = obj.longestConsecutiveSequence(vector<int>{100, 4, 200, 1, 3, 2});
	}

	// Longest cross of ones
	{
		vector<vector<int>> matrix{ {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 1, 1, 1}, {1, 0, 1, 1} };
		auto res = obj.longestCrossOfOnes(matrix);
		vector<vector<int>> matrix2{ {1,1,1,0,1},{1,0,1,1,1},{1,1,1,1,1},{1,0,1,1,0},{0,0,1,1,0} };
		res = obj.longestCrossOfOnes(matrix2);
	}

	// Longest X of ones
	{
		vector<vector<int>> matrix{ {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 1, 1, 1}, {1, 0, 1, 1} };
		auto res = obj.longestXOfOnes(matrix);
	}

	// Largest subarray sum
	{
		vector<int> nums{ 1, 2, 4, -1, -2, 10, -1, -100, -1, 10, 20 };
		auto res = obj.largestSubArraySum(nums); // 30
		nums = vector<int>{ 1, 4, -2, -8, 10, 3, 2, 9, -5 };
		res = obj.largestSubArraySum(nums);
	}

	// Largest subarray sum - return[sum, left, right]
	{
		vector<int> nums{ 1, 2, 4, -1, -2, 10, -1, -100, -1, 10, 20 };
		auto res = obj.largestSubArraySum2(nums); // 30, 9, 10
		nums = vector<int>{ 1, 4, -2, -8, 10, 3, 2, 9, -5 };
		res = obj.largestSubArraySum2(nums);
	}

	// Largest subarray sum - circular array
	{
		vector<int> nums{ -1, -2, 10, 11, 12, -2, -1 };
		auto res = obj.largestSubArraySum3(nums);
		nums = vector<int>{ 10, -1, -2, -3, 10 };
		res = obj.largestSubArraySum3(nums);
		nums = vector<int>{ -1, -2, -3 };
		res = obj.largestSubArraySum3(nums);
	}

	// Largest submatrix sum
	{
		vector<vector<int>> matrix{ {2,-1,2,1,-3},{0,-2,-1,2,1},{3,2,1,-3,-2} };
		auto res = obj.largestSubmatrixSum(matrix);
		res = obj.largestSubmatrixSum2(matrix);
	}

	// Largest subarray product
	{
		vector<double> input{ 4,-2,-3,-2,3 };
		auto res = obj.largestSubArrayProduct(input); // 24
	}

	// Largest submatrix product
	{
		vector<vector<double>> matrix{ {1, -0.2, 3, 2}, {-4, 1, -1, 1}, {-3, 2, 2, 2}, {-1, 1, 1, 1} };
		auto res = obj.largestSubmatrixProduct(matrix);
	}

	// Largest square of ones
	{
		vector<vector<int>> matrix{
		  {1, 0, 1, 1, 1},
		  {1, 1, 1, 1, 1},
		  {1, 1, 0, 1, 0},
		  {1, 1, 1, 1, 1},
		  {1, 1, 1, 0, 0} };
		auto res = obj.largestSquareOfOnes(matrix);

		vector<vector<int>> matrix2(5, { 0, 1, 1, 1, 1 });
		res = obj.largestSquareOfOnes(matrix2);
	}

	// Largest rectangle in histogram
	{
		vector<int> input{ 2, 1, 2, 3, 1 };
		auto res = obj.largestRectangleInHistogram(input); // 5
		vector<int> input2{ 1, 0, 1, 1, 1 };
		res = obj.largestRectangleInHistogram(input2); // 3
	}

	// Largest rectangle of ones
	{
		vector<vector<int>> matrix{
		  {1, 0, 0, 1, 1, 1},
		  {1, 0, 1, 1, 0, 1},
		  {0, 1, 1, 1, 1, 1},
		  {0, 0, 1, 1, 1, 1} };
		auto res = obj.largestRectangleOfOnes(matrix); // 8
	}

	// Largest square surrounded by ones
	{
		vector<vector<int>> matrix{
		  {1, 0, 1, 1, 1},
		  {1, 1, 1, 1, 1},
		  {1, 1, 0, 1, 0},
		  {1, 1, 1, 1, 1},
		  {1, 1, 1, 0, 0} };
		auto res = obj.largestSquareSurroundedByOnes(matrix);
		res = obj.largestSquareSurroundedByOnes(vector<vector<int>>{ {1}});
		res = obj.largestSquareSurroundedByOnes(vector<vector<int>>{ {1, 1}, { 1,1 }});
	}

	// Largest square of matches
	{
		vector<vector<int>> matrix{
		  {3, 1, 1, 3, 0, 1, 1, 0},
		  {2, 0, 0, 2, 0, 0, 0, 0},
		  {3, 1, 3, 0, 0, 0, 0, 0},
		  {2, 0, 2, 0, 0, 0, 0, 0},
		  {1, 1, 0, 0, 0, 0, 0, 0} };
		auto res = obj.largestSquareOfMatches(matrix); // 2, which means 2 x 2)
	}

	// Max product cutting rope
	{
		auto res = obj.maxProductCuttingRope(5); // 6, one cut, _ _ | _ _ _
	}

	// Cutting wood stick
	{
		auto res = obj.cuttingWood(vector<int>{2, 4, 7}, 10);
	}

	// Array hopper
	{
		vector<int> input{ 2, 3, 1, 1, 4 };
		auto res = obj.arrayHopper(input);
		vector<int> input2{ 1, 2, 0 };
		res = obj.arrayHopper(input2);
		vector<int> input3{ 4, 2, 1, 2, 0, 0 };
		res = obj.arrayHopper(input3);
	}

	// Array hopper 2
	{
		vector<int> input{ 2, 3, 1, 1, 2, 4, 2, 0, 1, 1 };
		auto res = obj.arrayHopper2(input); // 4
		vector<int> input2{ 2, 1, 0, 3, 1 };
		res = obj.arrayHopper2(input2); // -1
	}



	// Edit distance
	{
		auto res = obj.editDistance_DFS("asdf", "sghj");
		res = obj.editDistance("asdf", "sghj");
		res = obj.editDistance("ab", "dbbabc");
	}

	// One edit distance
	{
		auto res = obj.oneEditDistance("aabcc", "aacc"); // true
		res = obj.oneEditDistance("aabb", "aab"); // true
		res = obj.oneEditDistance("aabcc", "aaccd"); // false
		res = obj.oneEditDistance("bartera", "bartterr"); // false
		res = obj.oneEditDistance("", "");
	}

	// One edit palindrome
	{
		auto res = obj.oneEditPalindrome("ricecar");
		res = obj.oneEditPalindrome("raceacar");
	}

	// Word break
	{
		vector<string> dict{ "bob", "cat", "rob" };
		auto res = obj.wordBreak("bobcatrob", dict);

		vector<string> dict2{ "i", "like", "sam", "sung", "samsung", "mobile", "ice", "cream", "icecream", "man", "go", "mango" };
		res = obj.wordBreak("ilikesamsung", dict2);

		vector<string> dict3{ "leet", "code" };
		res = obj.wordBreak("leetcode", dict3);
	}

	//  Word pattern
	{
		string s("dog cat cat dog"), p("abba");
		auto res = obj.wordPattern(s, p);
	}

	// Max water trapped
	{
		vector<int> input{ 3, 0, 2, 0, 4 };
		auto res = obj.maxWaterTrapped(input);
	}

	// Buy Stock - at most 1 transaction
	{
		vector<int> input{ 2, 3, 2, 1, 4, 5 };
		auto res = obj.buyStock(input); // 4
	}

	// Buy stock - at most k transactions
	{
		vector<int> input{ 2, 5, 7, 1, 4, 3, 1, 3 };
		auto res = obj.buyStock4(input, 1);
		res = obj.buyStock4(input, 2);
	}

	// Buy stock 2 - as many transactions
	{
		vector<int> input{ 2, 3, 2, 1, 4, 5 };
		auto res = obj.buyStock2(input); // 5
	}

	// Wildcard matching
	{
		auto res = obj.wildCardMatching("xaylmz", "x?y*z"); // true
		res = obj.wildCardMatching("", "*");
	}

	// Climbing stairs
	{
		auto res = obj.climbingStairs(4); // 5
	}

	// Ascending triple
	{
		vector<int> input{ 1, 5, 2, 4 };
		auto res = obj.ascendingTriple(input);
	}

	// Least obstacles
	{
		vector<vector<int>> matrix{
		  {0, 1, 0, 1, 1, 0, 0, 0},
		  {1, 1, 1, 0, 0, 0, 1, 1} };
		auto res = obj.leastObstacle(matrix); // 3
	}

	// Unique paths
	{
		vector<vector<int>> matrix{ {0,0,0}, {0,1,0}, {0,0,0} };
		auto res = obj.uniquePathsObstacles(matrix); // 6
	}

	// Minimum path sum in 2D grid
	{
		vector<vector<int>> matrix{ {5,1,2,4}, {4,1,0,1}, {0,3,7,6} };
		auto res = obj.minimumPathSum(matrix); // 14
	}

	// Decode ways
	{
		auto res = obj.decodeWays("213"); // 3
		res = obj.decodeWays2("213");
		res = obj.decodeWays("2134"); // 5
		res = obj.decodeWays2("2134");
		res = obj.decodeWays2("01234");
	}

	// Knight dialer
	{
		auto res = obj.knightDialer(3);
	}

	// Split array "smallest" largest sum
	{
		vector<int> nums{ 7, 2, 5, 10, 8 };
		auto res = obj.splitArrayLargestSum(nums, 2); // 18
	}

	// Can I win
	{
		vector<int> nums{ 2, 1, 4, 5, 3 };
		auto res = obj.canIWin(nums);
	}

	cin.get();
	return 0;
}

