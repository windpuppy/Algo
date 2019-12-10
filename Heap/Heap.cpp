#include "Heap.h"

int main()
{
  Heap sol;

  // Heapify
  {
    vector<int> values{ 3, 6, 4, 7, 1, 5, 8, 2, 9 };
    auto res = sol.heapify(values); // 1 2 4 3 6 5 8 7 9 
  }

  // Offer heap
  {
    vector<int> values{ 2, 3, 4, 0 }; // last element unused
    auto res = sol.offerHeap(values, 1); // 1 2 4 3 
  }

  // Heap update
  {
    vector<int> values{ 1, 2, 3, 4 };
    auto res = sol.updateHeap(values, 1, 5);
  }

  // Heap sort
  {
    vector<int> values{ 3, 6, 4, 7, 1, 5, 8, 2, 9 };
    auto res = sol.heapsort(values); // 1 2 4 3 6 5 8 7 9 
  }

  // Heap sort - almost sorted
  {
    vector<int> values{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
    auto res = sol.heapsort(values); // 0 1 2 4 3 6 5 8 7 9
  }

  // is min heap - array
  {
    vector<int> values{ 3, 6, 4, 7, 1, 5, 8, 2, 9 };
    auto minHeap = sol.heapify(values); // 1 2 4 3 6 5 8 7 9;
    auto res = sol.isMinHeap(minHeap);
  }

  // is min heap - binary tree
  {

  }

  cin.get();
  return 0;
}

