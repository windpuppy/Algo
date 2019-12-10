#include "Sorting.h"

int main()
{
  Sorting sol;

  // Selection sort
  {
    auto array = vector<int>{ 3, 2, 1 };
    auto res = sol.selectionSort(array);
    array = vector<int>{ 4, 2, -3, 6, 1 };
    res = sol.selectionSort(array);
    array = vector<int>{ 3, 5, 1, 2, 4, 8 };
    res = sol.selectionSort(array);
  }

  // Merge sort
  {
    auto array = vector<int>{ 3, 2, 1 };
    auto res = sol.mergeSort(array);
    array = vector<int>{ 4, 2, -3, 6, 1 };
    res = sol.mergeSort(array);
  }

  // Quick sort
  {
    // first pivot happens to be the true min (all other 5 elements will be partitioned into left)
    auto array = vector<int>{ 3, 5, 1, 2, 4, 8 };
    auto res = sol.quickSort(array);
    array = vector<int>{ 3, 5, 4, 2, 1, 8 };
    res = sol.quickSort(array);
    array = vector<int>{ 4, 2, -3, 6, 1 };
    res = sol.quickSort(array);
  }

  // Move zeros to the right (a quick sort problem)
  {
    auto array = vector<int>{ 0, 0, 1, 1, 0, 1, 0 };
    auto res = sol.moveZero(array);
  }

  // Rainbow sort (another quick sort problem)
  {
    auto array = vector<int>{ 1, 0, 1, -1, 0 };
    auto res = sol.rainbowSort(array);
  }

  // Insertion sort
  {
    auto res = sol.insertionSort(vector<int>{4, 2, -3, 6, 1});
  }

  // Kth smallest in two sorted arrays
  {
    vector<int> a{ 1, 3, 5, 7, 9, 11, 13 };
    vector<int> b{ 2, 4, 6, 8, 10, 12, 14, 16, 18, 20 };
    auto res = sol.kthSmallestInTwoSortedArrays(a, b, 8);

    vector<int> c{ 1, 3, 5 };
    vector<int> d{ 2, 4, 6, 8, 10, 12, 14, 16, 18, 20 };
    res = sol.kthSmallestInTwoSortedArrays(c, d, 8);

    vector<int> e{ 1 };
    vector<int> f{};
    res = sol.kthSmallestInTwoSortedArrays(e, f, 1);

    vector<int> g{ 1, 2, 3, 4 };
    vector<int> h{ 5 };
    res = sol.kthSmallestInTwoSortedArrays(g, h, 5);
  }

  // Meeting rooms
  {
    auto intervals = vector<vector<int>>{ vector<int>{0, 30}, vector<int>{5, 10}, vector<int>{15, 20} };
    auto res = sol.meetingRooms(intervals);
  }

  // Meeting rooms 2
  {
    auto intervals = vector<vector<int>>{ vector<int>{0, 30}, vector<int>{5, 10}, vector<int>{15, 20} };
    auto res = sol.meetingRooms2(intervals);
  }

  // Meeting rooms2


  // Sleep sort
  {
    vector<int> nums{ 3, 2, 1, 4 };
    sol.sleepSort(nums);
    sol.wait(0);
  }

  cin.get();
  return 0;
}
