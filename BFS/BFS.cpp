#include "BFS.h"

int main()
{
  BFS sol;

  // K Smallest min heap
  {
    vector<int> values{ 3, 1, 5, 2, 4 };
    auto res = sol.kSmallest_minheap(values, 5);
  }

  // K Smallest max heap
  {
    vector<int> values{ 3, 1, 5, 2, 4 };
    auto res = sol.kSmallest_maxheap(values, 5);
  }

  // K Smallest quick sort
  {
    vector<int> values{ 3, 1, 5, 2, 4 };
    auto res = sol.kSmallest_quicksort(values, 5);
  }

  // Bipartitie
  {
    vector<vector<int>> values{
    {0, 1, 4},
    {1, 0, 4, 3, 2},
    {2, 1, 3},
    {3, 1, 4, 2},
    {4, 3, 0, 1}};
    auto graph = Helper::buildGraph(values);
    auto res = sol.bipartite(graph);
  }

  // Kth Smallest in sorted matrix
  {
    vector<vector<int>> values{
    {1, 2, 3, 5, 6},
    {2, 3, 3, 6, 8},
    {3, 4, 5, 7, 9},
    {4, 5, 6, 8, 10},
    {5, 6, 9, 10, 11} };
    auto res = sol.kthSmallest(values, 7); // 3
    res = sol.kthSmallest(values, 10); // 5

    vector<vector<int>> values2{ {1} };
    res = sol.kthSmallest(values2, 1);
  }

  // Kth smallest with 3, 5, 7 factors
  {
    auto res = sol.kthSmallest357(40);
  }

  // Kth smallest with 2, 3, factors
  {
    auto res = sol.kthSmallest23(40);
  }

  // kth closest to (0, 0, 0)
  {
    vector<int> a{ 1, 3, 5 };
    vector<int> b{ 2, 4 };
    vector<int> c{ 3, 6 };
    //auto res = sol.kthClosestPointTo000(a, b, c, 4);
  }

  // Minimum distance of three arrays
  {
    vector<int> a{ 1, 2, 3 };
    vector<int> b{ 4, 5 };
    vector<int> c{ 3, 4 };
    auto res = sol.minimumThreeArrayDistance(a, b, c); // 2 (min dist between 3, 4, 3 or 3, 4, 4)
  }

  // Smallest range
  {
    vector<vector<int>> arrays{
      { 1, 4, 100 },
      { 2, 5 },
      { 8, 10, 15 }
    };
    auto res = sol.smallestRange(arrays);
  }

  // Word ladder
  {
    vector<string> dict{ "git", "hit", "hog", "hot" };
    auto res = sol.wordLadder("git", "hot", dict);
  }

  // Super ugly number
  {
    vector<int> primes{ 2, 7, 13, 19 };
    auto res = sol.superUglyNumber(12, primes);
  }

  // Shortest distance between two cells
  {
    vector<vector<char>> grid{
      {'1', '0', '1', 's'},
      {'0', '1', '0', '0'},
      {'1', '0', '0', '0'},
      {'d', '0', '0', '0'}};
    auto res = sol.shortestDistanceTwoCells(grid); // 6
  }

  // Shortest distance from all points
  // 0: land, 1: house, 2: obstacle
  {
    vector<vector<int>> grid{
      {1, 0, 2, 0, 1},
      {0, 0, 0, 0, 0},
      {0, 0, 1, 0, 0}};
    auto res = sol.shortestDistanceFromAllPoints(grid);
  }

  // Best meeting point
  // 0: space, 1: person
  {
    vector<vector<int>> grid{
      {1, 0, 0, 0, 1},
      {0, 0, 0, 0, 0},
      {0, 0, 1, 0, 0} };
    auto res = sol.bestMeetingPoint(grid);
    vector<vector<int>> grid2{{1,1}};
    res = sol.bestMeetingPoint(grid2);
  }

  // Place to put the chair
  // C: empty, E: equipment, O: obstacle
  {
    vector<vector<char>> grid{
      {'C', 'C', 'E', 'O', 'C'},
      {'C', 'C', 'O', 'C', 'E'},
      {'C', 'C', 'E', 'E', 'C'},
      {'C', 'O', 'C', 'E', 'E'},
      {'C', 'C', 'O', 'C', 'C'}};
    auto res = sol.placeToPutChair(grid);
  }

  // Closest distance to zero
  {
    vector<vector<int>> grid{ {1, 1, 1}, {0, 1, 0}, {0, 0, 0} };
    auto res = sol.closestDistanceToZero(grid);
  }

  // Shortest distance to char
  {
    auto res = sol.shortestDistanceToChar("geeksforgeeks", 'e');
  }

  // Word distance 1 & 2
  {
    vector<string> words{ "practice", "makes", "perfect", "coding", "makes" };
    auto res = sol.shortestWordDistance(words, "makes", "coding"); // 1
    res = sol.shortestWordDistance2(words, "makes", "makes"); // 3
  }

  // String distance (input might have dups)
  {
    vector<string> words{ "this", "is", "a", "is", "fox", "happy" };
    auto res = sol.stringDistance(words, "fox", "is"); // 1
  }
  cin.get();
  return 0;
}


