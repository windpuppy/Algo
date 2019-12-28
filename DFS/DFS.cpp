#include "DFS.h"
#include <ctime>

int main()
{
  DFS sol;
  srand(time(NULL));

  // Subsets
  {
    auto res = sol.subsets("abc");
    res = sol.subsets_bfs("abcd");
    res = sol.subsets_iter("abc");
    res = sol.subsets("");
  }

  // Subsets - dedup
  {
    auto res = sol.subsets2("abb");
    res = sol.subsets2("abab");
  }

  // Subsets of K
  {
    auto res = sol.subsetsOfK("abc", 2);
  }

  // subsets of K - dedup
  {
    auto res = sol.subsetsOfK2("abab", 2);
  }

  // subset of k in n
  {
    auto res = sol.subsetsOfK_nums(4, 2);
  }

  // Valid parentheses
  {
    auto res = sol.validParentheses(3);
  }

  // Valid parentheses 2
  {
    auto res = sol.validParentheses2(1, 1, 0);
    res = sol.validParentheses2(1, 0, 0);
  }

  // Coin combinations
  {
    vector<int> coins{ 25, 10, 5, 1 };
    auto res = sol.coinCombinations(coins, 99);

    coins = vector<int>{ 1, 5, 10, 25 };
    res = sol.coinCombinations(coins, 99);

    coins = vector<int>{ 34, 31, 29, 16, 2 };
    res = sol.coinCombinations(coins, 10);
  }

  // Factor combinations
  {
    auto res = sol.factorCombinations(24);
  }

  // All permutations
  {
    auto res = sol.permutations("abc");
  }

  // All Permutations 2
  {
    auto res = sol.permutations2("abbca");
  }

  // All permutations of subsets
  {
    auto res = sol.permutationOfSubsets("abc");
  }

  // Palindrome permutation 1 & 2
  {
    auto res = sol.palindromePermutation("aabbcc");
    auto res2 = sol.palindromePermutation2("aabb");
  }

  // Combination sum
  {
    vector<int> input{ 2, 2, 2, 4, 4, 8, 6, 6, 6 };
    auto res = sol.combinationSum(input, 8);

    vector<int> input2{ 1, 2, 3, 6 };
    res = sol.combinationSum(input2, 12);
  }

  // Combination sum 2 (each candidate can only be used once)
  {
    vector<int> input{ 1, 1, 2, 3 };
    auto res = sol.combinationSum2(input, 4);

    vector<int> input2{ 10, 1, 2, 7, 6, 1, 5 };
    res = sol.combinationSum2(input2, 8);
  }

  // Telephone pad
  {
    auto res = sol.telephonePad(213);
    res = sol.telephonePad_bfs(102);
  }

  // N queens
  {
    auto res = sol.nQueens(4);
  }

  // Number of islands
  {
    vector<vector<char>> grid{
      {'1', '1', '0', '0', '0'},
      {'0', '1', '0', '0', '1'},
      {'1', '0', '0', '1', '1'},
      {'0', '0', '0', '0', '0'},
      {'1', '0', '1', '1', '0'}};
    auto g1 = grid;
    auto res = sol.numIslands(g1); // 4
    auto g2 = grid;
    res = sol.numIslands2(g2);

    vector<vector<char>> grid2{
      {'1', '1', '0', '0', '0'},
      {'1', '1', '0', '0', '0'},
      {'0', '0', '1', '0', '0'},
      {'0', '0', '0', '1', '1'}};
    auto g3 = grid2;
    res = sol.numIslands(g3); // 3
    auto g4 = grid2;
    res = sol.numIslands2(g4);
  }

  // Cheapest flight with k most stops
  {
    vector<vector<int>> flights{
      {0, 1, 100},
      {0, 2, 1000},
      {1, 2, 200}};
    auto res = sol.cheapestPrice(3, flights, 0, 2, 1); // city 0 to 2, 1 stop, price 300
    res = sol.cheapestPrice(3, flights, 0, 2, 0); // city 0 to 2, 0 stop, price 1000

    res = sol.cheapestPrice_bfs(3, flights, 0, 2, 1); // city 0 to 2, 1 stop, price 300
    res = sol.cheapestPrice_bfs(3, flights, 0, 2, 0); // city 0 to 2, 0 stop, price 1000

    res = sol.cheapestPrice_dp(3, flights, 0, 2, 1); // city 0 to 2, 1 stop, price 300
    res = sol.cheapestPrice_dp(3, flights, 0, 2, 0); // city 0 to 2, 0 stop, price 1000
  }

  // Restore IP address
  {
    auto res = sol.restoreIpAddress("25525511135");
  }

  // Keep distance of identical elements
  {
    auto res = sol.keepDistance(3);
  }

  // Generate random maze
  {
    auto res = sol.generateRandomMaze(5);
  }

  // Optimal account balancing
  {
    vector<vector<int>> debt{ {0, 1, 10},{1, 0, 1},{1, 2, 5},{2, 0, 5} };
    auto res = sol.optimalAccountBalancing(debt);
  }

  // Different ways to add parentheses
  {
    auto res = sol.differentWaysToAddParentheses("2-1-1");
  }

  cin.get();
  return 0;
}
