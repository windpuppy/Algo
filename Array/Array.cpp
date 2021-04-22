#include "Array.h"

int main()
{
    Array sol;

    // 2 Sum 2 arrays
    {
        auto res = sol.TwoSumTwoArrays(vector<int>{3, 1, 5}, vector<int>{2, 8}, 7);
    }

    // 3 Sum
    {
        auto res = sol.ThreeSum(vector<int>{1, 2, 2, 3, 2, 4}, 8);
    }

    // 3 Sum 3 arrays
    {
        auto res = sol.ThreeSumThreeArrays(vector<int>{1, 3, 5}, vector<int>{8, 2}, vector<int>{3}, 14);
    }

    // 4 Sum
    {
        auto res = sol.FourSum(vector<int>{1, 2, 2, 3, 4}, 9);
    }

    // 2 Diff
    {
        auto res = sol.TwoDiff(vector<int>{1, 2}, -1);
        res = sol.TwoDiff(vector<int>{1, 2, 3, 4}, -3);
        res = sol.TwoDiff(vector<int>{1, 2, 3, 4, 5}, 0);
        res = sol.TwoDiff(vector<int>{1, 4, 4, 8, 14}, 0);
    }

    // Longest subarray sum K
    {
        auto res = sol.longestSubArraySumK(vector<int>{1, -1, 5, -2, 3}, 3); // 4
    }

    // Product except itself
    {
        auto res = sol.productExceptSelf(vector<int>{1, 2, 3, 4});
    }

    // Celebrity problem
    {
        vector<vector<int>> matrix{ { 0, 1, 1 },{ 0, 0, 0 },{ 1, 1, 0 } };
        auto res = sol.celebrity(matrix); // 1
    }

    // Get count array
    {
        vector<int> input{ 4, 1, 3, 2 };
        auto res = sol.getCountArray(input);
    }

    // Largest and second largest
    {
        vector<int> input{ 2, 1, 3, 4 };
        auto res = sol.largestAndSecondLargest(input);
        vector<int> input2{ 2, 1, 5, 3, 4 };
        res = sol.largestAndSecondLargest(input2);
        res = sol.largestAndSecondLargest(vector<int>{5, 4, 2, 1, 3, 6});
    }

    // Least swaps
    {
        vector<int> input{ 5, 2, 3, 1, 4 };
        auto res = sol.leastSwaps(input);

        vector<int> input2{-282, -69, 421, 270, -236, -180, -267, -486, 147, 235, 108, -415, -258, 477, 0, -304, -191, -206, -173, -229, 362, -280, 68, 473, -339, 143, 384, -332, -231, -320, 212, -9, -78, -116, -447, 7, -261, -79, -211, 340, -252, -209, 481, -234, 67, -411, 223, -166, -430, -41, -178, -310, -133, -365, -205, -269, -172, 318, -109, -349, -72, -449, -41, -112, 439, -472, 166, 433, 322, 159, -155, 463, 473, -376, -89, -472, 31, -159, -386, 95, -295, 141, -63, 341, -146};
        res = sol.leastSwaps(input2);
    }

    // Merge k sorted arrays
    {
        vector<vector<int>> arrays{ {3}, {1, 2, 3, 4, 5} };
        auto res = sol.mergeKSortedArrays(arrays);
    }

    // Max values of size K sliding windows
    {
        vector<int> input{ 1, 2, 3, 2, 4, 2, 1 };
        auto res = sol.maxValueOfSizeKSlidingWindows(input, 3);
        vector<int> input2{ 3, 2, 1, 2, 4, 2, 1 };
        res = sol.maxValueOfSizeKSlidingWindows(input2, 3);
    }

    // Array dedup - sorted
    {
        vector<int> input{ 1, 2, 2, 3 };
        auto res = sol.arrayDedup(input);
    }

    // Array dedup 2 - sorted, keep 2 of the dups
    {
        vector<int> input{ 1, 2, 2, 2, 3, 3 };
        auto res = sol.arrayDedup2(input);
        vector<int> input2{ 1, 1, 1 };
        res = sol.arrayDedup2(input2);
    }

    // Array dedup 3 - sorted, remove all dups
    {
        vector<int> input{ 1, 2, 2, 3, 3, 3 };
        auto res = sol.arrayDedup3(input); // { 1 }
        vector<int> input2{ 1, 1, 1 };
        res = sol.arrayDedup3(input2); // { }
        vector<int> input3{ 1, 2, 3 };
        res = sol.arrayDedup3(input3); // { }
    }

    // Array dedup 4 - unsored, remove all dups
    {
        vector<int> input{ 1, 2, 3, 3, 3, 2, 2 };
        auto res = sol.arrayDedup4(input); // { 1 c
        vector<int> input2{ 1, 1, 2, 3, 3, 3, 2, 1, 6 };
        res = sol.arrayDedup4(input2); // { 1 }
    }

    // Next greater 2
    {
        auto res = sol.nextGreater2(vector<int>{1, 1, 1, 1, 1});
    }

    // Next greater 3
    {
        auto res = sol.nextGreater3(13542); // 14235
        res = sol.nextGreater3(19999999999); // -1
        res = sol.nextGreater3(11111);
    }

    // Subarray sum to target
    {
        auto res = sol.subArraySumToTarget(vector<int>{1, 5, 2, 4}, 7);
    }

    // Minimum size subarray sum
    {
        auto res = sol.minimumSizeSubarraySum(vector<int>{ 1, 1 }, 3);
        res = sol.minimumSizeSubarraySum(vector<int>{ 2, 3, 1, 2, 4, 3 }, 7);
    }

    // Partition to two parts of equal sum
    {
        vector<int> nums{ 3, 3, 3, 4, 5 };
        auto res = sol.canPartition(nums);
        res = sol.canPartition2(nums);
        res = sol.canPartition3(nums);
    }

    // Equal sum partitions (look for the smallest sum, not the fewest partition!)
    {
        vector<int> nums{ 2, 5, 1, 3, 3, 7 };
        auto res = sol.minEqualSumPartition(nums); // 7
        vector<int> nums2{ 1, 1, 1, 1, 1 };
        res = sol.minEqualSumPartition(nums2); // 1
        vector<int> nums3{ 1, 2, 3, 4 };
        res = sol.minEqualSumPartition(nums3); // 10
    }

    // Partition array for maximum sum
    {
        vector<int> nums{ 1, 15, 7, 9, 2, 5, 10 };
        auto res = sol.maxSumPartition(nums, 3);
    }

    // Happy number
    {
            auto res = sol.HappyNumber(19); // true
            res = sol.HappyNumber(2); // false
    }

    cin.get();
    return 0;
}

