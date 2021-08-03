#include "TestFixture.h"
#include <BinarySearch/BinarySearch.h>

namespace BinarySearchTests {

	BinarySearch obj;

	TEST(BinarySearchTests, BinarySearchClassic) {
		vector<int> values({ 3, 4, 5, 6, 9, 16 });
		auto res = obj.binarySearch(values, 5);
		EXPECT_EQ(res, 2);
		res = obj.binarySearch(values, 7);
		EXPECT_EQ(res, -1);
	}

	TEST(BinarySearchTests, BinarySearchSortedMatrix) {
		vector<vector<int>> matrix{
			vector<int>{ 1, 2, 3, 4 },
			vector<int>{ 5, 6, 7, 8 },
			vector<int>{ 9, 10, 11, 12 }
		};
		auto res = obj.binarySearchSortedMatrix(matrix, 7);
		vector<int> expected{ 1, 2 };
		EXPECT_EQ(res, expected);
	}

	TEST(BinarySearchTests, ClosestElement) {
		vector<int> array{ 3, 4, 5, 6, 6, 12, 16 };
		auto res = obj.findClosest(array, 8);
		EXPECT_EQ(res, 4);
		res = obj.findClosest(array, 9);
		EXPECT_EQ(res, 5);
	}

	TEST(BinarySearchTests, FirstLastOccurance) {
		vector<int> array{ 1, 2, 2, 2, 2, 3, 4 };
		auto res = obj.firstOccurrence(array, 2);
		EXPECT_EQ(res, 1);

		array = vector<int>{ 1, 2, 3 };
		res = obj.firstOccurrence(array, 0);
		EXPECT_EQ(res, -1);

		array = vector<int>{ 1, 2, 2, 2, 2, 3, 4 };
		res = obj.lastOccurrence(array, 2);
		EXPECT_EQ(res, 4);

		array = vector<int>{ 1, 2, 3 };
		res = obj.lastOccurrence(array, 0);
		EXPECT_EQ(res, -1);
	}

	TEST(BinarySearchTests, TotalOccurances) {
		vector<int> array{ 1, 2, 3, 4, 4, 6, 8, 9 };
		auto res = obj.totalOccurrence(array, 4);
		EXPECT_EQ(res, 2);
	}

	TEST(BinarySearchTests, KClosest) {
		vector<int> array{ 1, 2, 3 };
		auto res = obj.kClosest(array, 2, 1);
		vector<int> expected{ 2 };
		EXPECT_EQ(res, expected);

		vector<int> array2{ 1, 3, 3, 6, 9, 9, 12, 15 };
		res = obj.kClosest(array2, 0, 3);
		expected = vector<int>{ 1, 3, 3 };
		EXPECT_EQ(res, expected);

		vector<int> array3{ 1 };
		res = obj.kClosest(array3, 0, 1);
		expected = vector<int>{ 1 };
		EXPECT_EQ(res, expected);
	}

	TEST(BinarySearchTests, SearchInShiftedArray) {
		vector<int> array{ 3, 4, 5, 1, 2 };
		auto res = obj.searchInShiftedSortedArray(array, 1);
		EXPECT_EQ(res, 3);
		res = obj.searchInShiftedSortedArray(array, 6);
		EXPECT_EQ(res, -1);

		// With dups
		array = vector<int>{ 3, 4, 5, 1, 1, 2 };
		res = obj.searchInShiftedSortedArrayDups(array, 1);
		EXPECT_EQ(res, 4);
	}


	TEST(BinarySearchTests, ShiftPosition) {
		auto res = obj.findShiftPosition(vector<int>{3, 4, 5, 1, 2});
		EXPECT_EQ(res, 3);
		res = obj.findShiftPosition(vector<int>{4, 5, 1, 2, 3});
		EXPECT_EQ(res, 2);
		res = obj.findShiftPosition(vector<int>{1, 2, 3, 4, 5});
		EXPECT_EQ(res, 0);
	}
}
