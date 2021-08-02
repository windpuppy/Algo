#include  "BinarySearch.h"

int main()
{
	BinarySearch obj;

	// Shift position
	{
		auto res = obj.shiftPosition(vector<int>{3, 4, 5, 1, 2});
		res = obj.shiftPosition(vector<int>{4, 5, 1, 2, 3});
		res = obj.shiftPosition(vector<int>{1, 2, 3, 4, 5});
	}

	cin.get();
	return 0;
}

