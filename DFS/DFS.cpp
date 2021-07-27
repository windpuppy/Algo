#include "DFS.h"
#include <ctime>

int main()
{
  DFS obj;
  srand(time(NULL));

  // Subsets - dedup
  {
    auto res = obj.subsets2("abb");
    res = obj.subsets2("abab");
  }

  // Subsets of K
  {
    auto res = obj.subsetsOfK("abc", 2);
  }

  // subsets of K - dedup
  {
    auto res = obj.subsetsOfK2("abab", 2);
  }

  // subset of k in n
  {
    auto res = obj.subsetsOfK_nums(4, 2);
  }

  // Valid parentheses 2
  {
    auto res = obj.validParentheses2(1, 1, 0);
    res = obj.validParentheses2(1, 0, 0);
  }

  // Remove invalid parentheses
  {
    string input = "((a)(())))";
    //string input = ")())))))))))";
    auto res = obj.removeInvalidParentheses(input);
  }

  // Factor combinations
  {
    auto res = obj.factorCombinations(24);
  }

  // All Permutations 2
  {
    auto res = obj.permutations2("abbca");
  }

  // All permutations of subsets
  {
    auto res = obj.permutationOfSubsets("abc");
  }

  // Palindrome permutation 1 & 2
  {
    auto res = obj.palindromePermutation("aabbcc");
    auto res2 = obj.palindromePermutation2("aabb");
  }

  // Combination sum
  {
    vector<int> input{ 2, 2, 2, 4, 4, 8, 6, 6, 6 };
    auto res = obj.combinationSum(input, 8);

    vector<int> input2{ 1, 2, 3, 6 };
    res = obj.combinationSum(input2, 12);
  }

  // Combination sum 2 (each candidate can only be used once)
  {
    vector<int> input{ 1, 1, 2, 3 };
    auto res = obj.combinationSum2(input, 4);

    vector<int> input2{ 10, 1, 2, 7, 6, 1, 5 };
    res = obj.combinationSum2(input2, 8);
  }

  // Telephone pad
  {
    auto res = obj.telephonePad(213);
    res = obj.telephonePad_bfs(102);
  }

  // N queens
  {
    auto res = obj.nQueens(4);
  }

  // Number of islands
  {
    vector<vector<char>> grid{
      {'1', '1', '0', '0', '0'},
      {'0', '1', '0', '0', '1'},
      {'1', '0', '0', '1', '1'},
      {'0', '0', '0', '0', '0'},
      {'1', '0', '1', '1', '0'}};
    auto g = grid;
    auto res = obj.numIslands(g); // 4
    g = grid;
    res = obj.numIslands(g, false);

    vector<vector<char>> grid2{
      {'1', '1', '0', '0', '0'},
      {'1', '1', '0', '0', '0'},
      {'0', '0', '1', '0', '0'},
      {'0', '0', '0', '1', '1'}};
    g = grid2;
    res = obj.numIslands(g); // 3
    g = grid2;
    res = obj.numIslands(g, false);
  }

  // Cheapest flight with k most stops
  {
    vector<vector<int>> flights{
      {0, 1, 100},
      {0, 2, 1000},
      {1, 2, 200}};
    auto res = obj.cheapestFlightsWithKStops(3, flights, 0, 2, 1); // city 0 to 2, 1 stop, price 300
    res = obj.cheapestFlightsWithKStops(3, flights, 0, 2, 0); // city 0 to 2, 0 stop, price 1000

    res = obj.cheapestFlightsWithKStops_bfs(3, flights, 0, 2, 1); // city 0 to 2, 1 stop, price 300
    res = obj.cheapestFlightsWithKStops_bfs(3, flights, 0, 2, 0); // city 0 to 2, 0 stop, price 1000

    res = obj.cheapestFlightsWithKStops_dp(3, flights, 0, 2, 1); // city 0 to 2, 1 stop, price 300
    res = obj.cheapestFlightsWithKStops_dp(3, flights, 0, 2, 0); // city 0 to 2, 0 stop, price 1000
  }

  // Restore IP address
  {
    auto res = obj.restoreIpAddress("25525511135");
  }

  // Keep distance of identical elements
  {
    auto res = obj.keepDistance(3);
  }

  // Generate random maze
  {
    auto res = obj.generateRandomMaze(5);
  }

  // Optimal account balancing
  {
    vector<vector<int>> debt{ {0, 1, 10},{1, 0, 1},{1, 2, 5},{2, 0, 5} };
    auto res = obj.optimalAccountBalancing(debt);
  }

  // Different ways to add parentheses
  {
    auto res = obj.differentWaysToAddParentheses("2-1-1");
  }

  cin.get();
  return 0;
}
