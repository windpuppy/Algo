#include "BFS.h"
#include "../Common/TreeHelper.h"

int main()
{
	BFS obj;

	// Bipartitie
	{
		vector<vector<int>> values{
		{0, 1, 4},
		{1, 0, 4, 3, 2},
		{2, 1, 3},
		{3, 1, 4, 2},
		{4, 3, 0, 1} };
		vector<GraphNode*> graph = TreeHelper::buildGraph(values);
		bool res = obj.bipartite(graph);
	}

	// kth closest to (0, 0, 0)
	{
		vector<int> a{ 1, 2, 3 };
		vector<int> b{ 2, 4 };
		vector<int> c{ 1, 2 };
		//auto res = obj.kthClosestPointToOrigin(a, b, c, 10);
	}

	// Smallest range
	{
		vector<vector<int>> arrays{
		  { 1, 4, 100 },
		  { 2, 5 },
		  { 8, 10, 15 }
		};
		auto res = obj.smallestRange(arrays);
	}

	// Word ladder
	{
		vector<string> dict{ "git", "hit", "hog", "hot", "got" };
		auto res = obj.wordLadder("git", "hot", dict);
		auto res2 = obj.wordLadder2("git", "hot", dict);
		auto res3 = obj.wordLadder3("git", "hot", dict);
	}

	// Super ugly number
	{
		vector<int> primes{ 2, 7, 13, 19 };
		auto res = obj.superUglyNumber(12, primes);
	}

	// Shortest distance from all points
	// 0: land, 1: house, 2: obstacle
	{
		vector<vector<int>> grid{
		  {1, 0, 2, 0, 1},
		  {0, 0, 0, 0, 0},
		  {0, 0, 1, 0, 0} };
		auto res = obj.shortestDistanceFromAllPoints(grid);
	}

	// Best meeting point
	// 0: space, 1: person
	{
		vector<vector<int>> grid{
		  {1, 0, 0, 0, 1},
		  {0, 0, 0, 0, 0},
		  {0, 0, 1, 0, 0} };
		auto res = obj.bestMeetingPoint(grid);
		vector<vector<int>> grid2{ {1,1} };
		res = obj.bestMeetingPoint(grid2);
	}

	// Place to put the chair
	// C: empty, E: equipment, O: obstacle
	{
		vector<vector<char>> grid{
		  {'C', 'C', 'E', 'O', 'C'},
		  {'C', 'C', 'O', 'C', 'E'},
		  {'C', 'C', 'E', 'E', 'C'},
		  {'C', 'O', 'C', 'E', 'E'},
		  {'C', 'C', 'O', 'C', 'C'} };
		auto res = obj.placeToPutChair(grid);
	}

	// Closest distance to zero
	{
		vector<vector<int>> grid{ {1, 1, 1}, {0, 1, 0}, {0, 0, 0} };
		auto res = obj.closestDistanceToZero(grid);
	}

	// Walls and Gates
	{
		vector<vector<int>> grid{
		  {INT_MAX, -1, 0, INT_MAX},
		  {INT_MAX, INT_MAX, INT_MAX, -1},
		  {INT_MAX, -1, INT_MAX, -1},
		  {0, -1, INT_MAX, INT_MAX} };
		auto res = obj.wallsAndGates(grid);
		auto res2 = obj.wallsAndGates2(grid);
	}


	// Pacific Atlantic flow
	{
		vector<vector<int>> grid{ {1,2,2,3},{3,2,3,4},{2,4,5,3},{6,7,1,4} };
		auto res = obj.pacificAtlantic(grid);
		res = obj.pacificAtlantic_bfs(grid);
	}

	// Shortest distance to char
	{
		auto res = obj.shortestDistanceToChar("geeksforgeeks", 'e');
	}

	// String distance (input might have dups)
	{
		vector<string> words{ "this", "is", "a", "is", "fox", "happy" };
		auto res = obj.stringDistance(words, "fox", "is"); // 1
	}
	cin.get();
	return 0;
}


