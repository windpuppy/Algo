#include "DP.h"
#include <cassert>

int main()
{
  DynamicProgramming sol;

  // Fibonacci 2
  {
    auto res = sol.fibonacci2(60);
    res = sol.fibonacci2_iter(60);
  }

  // Longest ascending subarray
  {
    vector<int> input{ 1, 2, 2, 3, 3, 4, 5, 6, 6, 7 };
    auto res = sol.longestAscendingSubArray(input); // 4
  }

  // Longest ascending subsequence
  {
    vector<int> input{ 7, 2, 3, 1, 5, 8, 9, 6};
    auto res = sol.longestAscendingSubSequence(input); // 5
    auto res2 = sol.longestAscendingSubSequence2(input); // [2,3,5,8,9]
    res2 = sol.longestAscendingSubSequence2({ 1 }); // 1
  }

  // Longest common substring
  {
    auto res = sol.longestCommonSubstring("abcdefg", "bbcefgh"); // efg
    res = sol.longestCommonSubstring("aaaaaa", "bbaaba"); //aa
  }

  // Longest common subsequence
  {
    auto res = sol.longestCommonSubsequence("acbcf", "abcdaf"); // 4
  }

  // Longest consecutive ones
  {
    vector<int> input{ 1, 0, 0, 1, 1, 0, 1, 1, 1, 0 };
    auto res = sol.longestConsecutiveOnes(input); // 3
    res = sol.longestConsecutiveOnes2(input); // 6
    res = sol.longestConsecutiveOnes3(input, 2); // 7
  }

  // Longest consecutive sequence
  {
    auto res = sol.longestConsecutiveSequence(vector<int>{100, 4, 200, 1, 3, 2});
  }

  // Longest cross of ones
  {
    vector<vector<int>> matrix{ {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 1, 1, 1}, {1, 0, 1, 1} };
    auto res = sol.longestCrossOfOnes(matrix);
    vector<vector<int>> matrix2{ {1,1,1,0,1},{1,0,1,1,1},{1,1,1,1,1},{1,0,1,1,0},{0,0,1,1,0} };
    res = sol.longestCrossOfOnes(matrix2);
  }

  // Longest X of ones
  {
    vector<vector<int>> matrix{ {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 1, 1, 1}, {1, 0, 1, 1} };
    auto res = sol.longestXOfOnes(matrix);
  }

  // Largest subarray sum
  {
    vector<int> nums{ 1, 2, 4, -1, -2, 10, -1, -100, -1, 10, 20 };
    auto res = sol.largestSubArraySum(nums); // 30
    nums = vector<int>{ 1, 4, -2, -8, 10, 3, 2, 9, -5 };
    res = sol.largestSubArraySum(nums);
  }

  // Largest subarray sum - return[sum, left, right]
  {
    vector<int> nums{ 1, 2, 4, -1, -2, 10, -1, -100, -1, 10, 20 };
    auto res = sol.largestSubArraySum2(nums); // 30, 9, 10
    nums = vector<int>{ 1, 4, -2, -8, 10, 3, 2, 9, -5 };
    res = sol.largestSubArraySum2(nums);
  }

  // Largest subarray sum - circular array
  {
    vector<int> nums{ -1, -2, 10, 11, 12, -2, -1 };
    auto res = sol.largestSubArraySum3(nums);
    nums = vector<int>{ 10, -1, -2, -3, 10 };
    res = sol.largestSubArraySum3(nums);
    nums = vector<int>{ -1, -2, -3 };
    res = sol.largestSubArraySum3(nums);
  }

  // Largest submatrix sum
  {
    vector<vector<int>> matrix{ {2,-1,2,1,-3},{0,-2,-1,2,1},{3,2,1,-3,-2} };
    auto res = sol.largestSubmatrixSum(matrix);
    res = sol.largestSubmatrixSum2(matrix);
  }

  // Largest subarray product
  {
    vector<double> input{ 4,-2,-3,-2,3 };
    auto res = sol.largestSubArrayProduct(input); // 24
  }

  // Largest submatrix product
  {
    vector<vector<double>> matrix{{1, -0.2, 3, 2}, {-4, 1, -1, 1}, {-3, 2, 2, 2}, {-1, 1, 1, 1}};
    auto res = sol.largestSubmatrixProduct(matrix);
  }

  // Largest square of ones
  {
    vector<vector<int>> matrix{
      {1, 0, 1, 1, 1},
      {1, 1, 1, 1, 1},
      {1, 1, 0, 1, 0},
      {1, 1, 1, 1, 1},
      {1, 1, 1, 0, 0} };
    auto res = sol.largestSquareOfOnes(matrix);

    vector<vector<int>> matrix2(5, { 0, 1, 1, 1, 1 });
    res = sol.largestSquareOfOnes(matrix2);
  }

  // Largest rectangle in histogram
  {
    vector<int> input{ 2, 1, 2, 3, 1 };
    auto res = sol.largestRectangleInHistogram(input); // 5
    vector<int> input2{ 1, 0, 1, 1, 1 };
    res = sol.largestRectangleInHistogram(input2); // 3
  }

  // Largest rectangle of ones
  {
    vector<vector<int>> matrix{
      {1, 0, 0, 1, 1, 1},
      {1, 0, 1, 1, 0, 1},
      {0, 1, 1, 1, 1, 1},
      {0, 0, 1, 1, 1, 1}};
    auto res = sol.largestRectangleOfOnes(matrix); // 8
  }

  // Largest square surrounded by ones
  {
    vector<vector<int>> matrix{
      {1, 0, 1, 1, 1},
      {1, 1, 1, 1, 1},
      {1, 1, 0, 1, 0},
      {1, 1, 1, 1, 1},
      {1, 1, 1, 0, 0}};
    auto res = sol.largestSquareSurroundedByOnes(matrix);
    res = sol.largestSquareSurroundedByOnes(vector<vector<int>>{{1}});
    res = sol.largestSquareSurroundedByOnes(vector<vector<int>>{ {1, 1}, { 1,1 }});
  }

  // Largest square of matches
  {
    vector<vector<int>> matrix{
      {3, 1, 1, 3, 0, 1, 1, 0},
      {2, 0, 0, 2, 0, 0, 0, 0},
      {3, 1, 3, 0, 0, 0, 0, 0},
      {2, 0, 2, 0, 0, 0, 0, 0},
      {1, 1, 0, 0, 0, 0, 0, 0} };
    auto res = sol.largestSquareOfMatches(matrix); // 2, which means 2 x 2)
  }

  // Max product cutting rope
  {
    auto res = sol.maxProductCuttingRope(5); // 6, one cut, _ _ | _ _ _
  }

  // Cutting wood stick
  {
    auto res = sol.cuttingWood(vector<int>{2, 4, 7}, 10);
  }

  // Array hopper
  {
    vector<int> input{ 2, 3, 1, 1, 4 };
    auto res = sol.arrayHopper(input);
    vector<int> input2{ 1, 2, 0 };
    res = sol.arrayHopper(input2);
    vector<int> input3{ 4, 2, 1, 2, 0, 0 };
    res = sol.arrayHopper(input3);
  }

  // Array hopper 2
  {
    vector<int> input{ 2, 3, 1, 1, 2, 4, 2, 0, 1, 1 };
    auto res = sol.arrayHopper2(input); // 4
    vector<int> input2{ 2, 1, 0, 3, 1 };
    res = sol.arrayHopper2(input2); // -1
  }

  

  // Edit distance
  {
    auto res = sol.editDistance_DFS("asdf", "sghj");
    res = sol.editDistance("asdf", "sghj");
    res = sol.editDistance("ab", "dbbabc");
  }

  // One edit distance
  {
    auto res = sol.oneEditDistance("aabcc", "aacc"); // true
    res = sol.oneEditDistance("aabb", "aab"); // true
    res = sol.oneEditDistance("aabcc", "aaccd"); // false
    res = sol.oneEditDistance("bartera", "bartterr"); // false
    res = sol.oneEditDistance("", "");
  }

  // One edit palindrome
  {
    auto res = sol.oneEditPalindrome("ricecar");
    res = sol.oneEditPalindrome("raceacar");
  }

  // Word break
  {
    vector<string> dict{ "bob", "cat", "rob" };
    auto res = sol.wordBreak("bobcatrob", dict);

    vector<string> dict2{ "i", "like", "sam", "sung", "samsung", "mobile", "ice", "cream", "icecream", "man", "go", "mango" };
    res = sol.wordBreak("ilikesamsung", dict2);

    vector<string> dict3{ "leet", "code" };
    res = sol.wordBreak("leetcode", dict3);
  }

  //  Word pattern
  {
    string s("dog cat cat dog"), p("abba");
    auto res = sol.wordPattern(s, p);
  }

  // Max water trapped
  {
    vector<int> input{ 3, 0, 2, 0, 4 };
    auto res = sol.maxWaterTrapped(input);
  }

  // Buy Stock - at most 1 transaction
  {
    vector<int> input{ 2, 3, 2, 1, 4, 5 };
    auto res = sol.buyStock(input); // 4
  }

  // Buy stock - at most k transactions
  {
    vector<int> input{ 2, 5, 7, 1, 4, 3, 1, 3 };
    auto res = sol.buyStock4(input, 1);
    res = sol.buyStock4(input, 2);
  }

  // Buy stock 2 - as many transactions
  {
    vector<int> input{ 2, 3, 2, 1, 4, 5 };
    auto res = sol.buyStock2(input); // 5
  }

  // Wildcard matching
  {
    auto res = sol.wildCardMatching("xaylmz", "x?y*z"); // true
    res = sol.wildCardMatching("", "*");
  }

  // Climbing stairs
  {
    auto res = sol.climbingStairs(4); // 5
  }

  // Ascending triple
  {
    vector<int> input{ 1, 5, 2, 4 };
    auto res = sol.ascendingTriple(input);
  }

  // Least obstacles
  {
    vector<vector<int>> matrix{
      {0, 1, 0, 1, 1, 0, 0, 0},
      {1, 1, 1, 0, 0, 0, 1, 1}};
    auto res = sol.leastObstacle(matrix); // 3
  }

  // Unique paths
  {
    vector<vector<int>> matrix{ {0,0,0}, {0,1,0}, {0,0,0} };
    auto res = sol.uniquePathsObstacles(matrix); // 6
  }

  // Minimum path sum in 2D grid
  {
    vector<vector<int>> matrix{ {5,1,2,4}, {4,1,0,1}, {0,3,7,6} };
    auto res = sol.minimumPathSum(matrix); // 14
  }

  // Decode ways
  {
    auto res = sol.decodeWays("213"); // 3
    res = sol.decodeWays2("213");
    res = sol.decodeWays("2134"); // 5
    res = sol.decodeWays2("2134");
    res = sol.decodeWays2("01234");
  }

  // Knight dialer
  {
    auto res = sol.knightDialer(3);
  }

  // Split array "smallest" largest sum
  {
    vector<int> nums{ 7, 2, 5, 10, 8 };
    auto res = sol.splitArrayLargestSum(nums, 2); // 18
  }

  // Can I win
  {
    vector<int> nums{ 2, 1, 4, 5, 3 };
    auto res = sol.canIWin(nums);
  }

  cin.get();
  return 0;
}

