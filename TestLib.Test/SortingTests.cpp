#include "TestFixture.h"
#include <Sorting/Sorting.h>

namespace SortingTests {

    Sorting obj;

    TEST(SortingTests, MergeSort) {
        auto array = vector<int>{ 3, 2, 1 };
        auto res = obj.mergeSort(array);
        vector<int> expected{ 1, 2, 3 };
        EXPECT_EQV(res, expected);

        array = vector<int>{ 4, 2, -3, 6, 1 };
        res = obj.mergeSort(array);
        expected = vector<int>{ -3, 1, 2, 4, 6 };
        EXPECT_EQV(res, expected);
    }

    TEST(SortingTests, kthSmallestInTwoSortedArrays) {
		vector<int> a{ 1, 3, 5, 7, 9, 11, 13 };
		vector<int> b{ 2, 4, 6, 8, 10, 12, 14, 16, 18, 20 };
		auto res = obj.kthSmallestInTwoSortedArrays(a, b, 8);
		EXPECT_EQ(res, 8);

		vector<int> c{ 1, 3, 5 };
		vector<int> d{ 2, 4, 6, 8, 10, 12, 14, 16, 18, 20 };
		res = obj.kthSmallestInTwoSortedArrays(c, d, 8);
		EXPECT_EQ(res, 10);

		vector<int> e{ 1 };
		vector<int> f{};
		res = obj.kthSmallestInTwoSortedArrays(e, f, 1);
		EXPECT_EQ(res, 1);

		vector<int> g{ 1, 2, 3, 4 };
		vector<int> h{ 5 };
		res = obj.kthSmallestInTwoSortedArrays(g, h, 5);
		EXPECT_EQ(res, 5);

		vector<int> i{ 1, 3, 5, 7 };
		vector<int> j{ 2, 4, 6, 8, 10, 12 };
		res = obj.kthSmallestInTwoSortedArrays(i, j, 6);
		EXPECT_EQ(res, 6);
    }

}
