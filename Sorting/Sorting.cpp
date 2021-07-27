#include "Sorting.h"

int main()
{
	Sorting obj;

	// Selection sort
	{
		auto array = vector<int>{ 3, 2, 1 };
		auto res = obj.selectionSort(array);
		array = vector<int>{ 4, 2, -3, 6, 1 };
		res = obj.selectionSort(array);
		array = vector<int>{ 3, 5, 1, 2, 4, 8 };
		res = obj.selectionSort(array);
	}

	// Quick sort
	{
		// first pivot happens to be the true min (all other 5 elements will be partitioned into left)
		auto array = vector<int>{ 3, 5, 1, 2, 4, 8 };
		auto res = obj.quickSort(array);
		array = vector<int>{ 3, 5, 4, 2, 1, 8 };
		res = obj.quickSort(array);
		array = vector<int>{ 4, 2, -3, 6, 1 };
		res = obj.quickSort(array);
	}

	// Move zeros to the right (a quick sort problem)
	{
		auto array = vector<int>{ 0, 0, 1, 1, 0, 1, 0 };
		auto res = obj.moveZero(array);
	}

	// Rainbow sort (another quick sort problem)
	{
		auto nums = vector<int>{ 1, 0, 1, -1, 0 };
		auto res = obj.rainbowSort(nums);

		auto nums2 = vector<int>{ 1, 3, 0, 2, 0, 0, 1 };
		res = obj.rainbowSort2(nums2);
		nums2 = vector<int>{ 2, 0, 0, 1, 1 };
		res = obj.rainbowSort2(nums2);
	}

	// Insertion sort
	{
		auto res = obj.insertionSort(vector<int>{4, 2, -3, 6, 1});
	}

	// Meeting rooms
	{
		auto intervals = vector<vector<int>>{ vector<int>{0, 30}, vector<int>{5, 10}, vector<int>{15, 20} };
		auto res = obj.meetingRooms(intervals);
	}

	// Meeting rooms 2
	{
		auto intervals = vector<vector<int>>{ vector<int>{0, 30}, vector<int>{5, 10}, vector<int>{15, 20} };
		auto res = obj.meetingRooms2(intervals);
	}

	// Sleep sort
	{
		vector<int> nums{ 3, 2, 1, 4 };
		obj.sleepSort(nums);
		obj.wait(0);
	}

	cin.get();
	return 0;
}
