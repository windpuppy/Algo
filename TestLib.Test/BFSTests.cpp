#include "TestFixture.h"
#include <BFS/BFS.h>

namespace BFSTests {
	BFS obj;

	TEST(BFSTests, KSmallest) {
		// Using min heap
		vector<int> values{ 3, 1, 5, 2, 4 };
		auto res = obj.kSmallest_minheap(values, 3);
		auto expected = vector<int>{ 1, 2, 3};
		EXPECT_EQ(res, expected);

		// Using max heap
		res = obj.kSmallest_maxheap(values, 2);
		expected = vector<int>{ 1, 2 };
		EXPECT_EQ(res, expected);

		// Using quick sort
		res = obj.kSmallest_maxheap(values, 4);
		expected = vector<int>{ 1, 2, 3, 4 };
		EXPECT_EQ(res, expected);
	}

	TEST(BFSTests, KthSmallestInSortedMatrix) {
		vector<vector<int>> values{
		{1, 2, 3, 5, 6},
		{2, 3, 3, 6, 8},
		{3, 4, 5, 7, 9},
		{4, 5, 6, 8, 10},
		{5, 6, 9, 10, 11} };
		auto res = obj.kthSmallest(values, 7);
		EXPECT_EQ(res, 3);
		res = obj.kthSmallest(values, 10);
		EXPECT_EQ(res, 5);

		vector<vector<int>> values2{ {1} };
		res = obj.kthSmallest(values2, 1);
		EXPECT_EQ(res, 1);
		res = obj.kthSmallest(values2, 2);
		EXPECT_EQ(res, -1);
	}

	TEST(BFSTests, KthSmallestWith357AsFactors) {
		auto res = obj.kthSmallest357(4);
		EXPECT_EQ(res, 735);
		res = obj.kthSmallest357(7);
		EXPECT_EQ(res, 2205);
	}

	TEST(BFSTests, KthSmallestWith23AsFactors) {
		auto res = obj.kthSmallest23(4);
		EXPECT_EQ(res, 4);
		res = obj.kthSmallest23(8);
		EXPECT_EQ(res, 12); // 0, 2, 3, 4, 6, 8, 9, 12
		res = obj.kthSmallest23(1);
		EXPECT_EQ(res, 1);
	}

	TEST(BFSTests, MinThreeArrayDistance) {
		vector<int> a{ 1, 2, 3 };
		vector<int> b{ 4, 5 };
		vector<int> c{ 3, 4 };
		auto res = obj.minimumThreeArrayDistance(a, b, c);
		EXPECT_EQ(res, 2); // 2 (min dist between 3, 4, 3 or 3, 4, 4)
	}

	TEST(BFSTests, CommonElementsInThreeSortedArrays) {
		vector<int> a{ 1, 2, 4, 6, 8, 10 };
		vector<int> b{ 2, 2, 4, 10 };
		vector<int> c{ 2, 6, 8, 10 };
		auto res = obj.commonElementsInThreeSortedArray(a, b, c);
		vector<int> expected{ 2, 10 };
		EXPECT_EQ(res, expected);
	}

	TEST(BFSTest, ShortestDistanceTwoCells) {
		vector<vector<char>> grid{
		  {'1', '0', '1', 's'},
		  {'0', '1', '0', '0'},
		  {'1', '0', '0', '0'},
		  {'d', '0', '1', '0'} };
		auto res = obj.shortestDistanceTwoCells(grid); // 6
		EXPECT_EQ(res, 6);
	}

	// Pacific   ~   ~    ~    ~
	//       ~  1    2    2   (3) *
	//       ~  3    2    3   (4) *
	//       ~  2    4   (5)   3  *
	//       ~ (6)  (7)   1    4  *
	//          *    *    *    *  Atlantic
	TEST(BFSTest, PacificAtlantic) {
		vector<vector<int>> grid{
			vector<int>{1, 2, 2, 3},
			vector<int>{3, 2, 3, 4},
			vector<int>{2, 4, 5, 3},
			vector<int>{6, 7, 1, 4} };
		auto res = obj.pacificAtlantic_dfs(grid);
		vector<vector<int>> expected{
			vector<int>{0, 3},
			vector<int>{1, 3},
			vector<int>{2, 2},
			vector<int>{3, 0},
			vector<int>{3, 1} };
		EXPECT_EQ(res, expected);

		res = obj.pacificAtlantic_bfs(grid);
		EXPECT_EQ(res, expected);
	}
}