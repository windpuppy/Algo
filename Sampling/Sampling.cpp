#include <iostream>
#include <vector>
#include <queue>
#include <ctime>

using namespace std;

// We use two heaps
// left: store smaller values, using a max heap
// right: store larger values, using a min heap
// IMPORTANT: we keep left size > right size by 1, ALL THE TIME
//   so that when we query for median, we can always take the top of the left
class MedianTracker {
private:
  priority_queue<int, vector<int>, less<int>> left;    // smaller half, max heap
  priority_queue<int, vector<int>, greater<int>> right;  // larger half, min heap

public:
  // ctor
  MedianTracker() {}

  void read(int i) {
    // If empty, push left
    // if smaller than L max, push left
    if (left.empty() || i <= left.top())
      left.push(i);
    else
      right.push(i);

    // after the insertion, in two situations we need to adjust the heaps
    // 1) if L is 2 more than R - move L to R
    // 2) if L is less than R - move R to L
    if (left.size() >= right.size() + 2) {
      right.push(left.top());
      left.pop();
    }
    else if (left.size() < right.size()) {
      left.push(right.top());
      right.pop();
    }
  }

  double median() {
    int size = left.size() + right.size();
    if (size == 0)
      return INT_MIN;
    return size % 2 == 0
      ? (left.top() + right.top()) / 2.0
      : (double)left.top();
  }
};

class Sampling {
public:
  void perfectShuffle(vector<int>& input) {
    const int size = input.size();
    if (size <= 1) return;
    srand(time(0));
    for (int i = 0; i < size; ++i) {
      int index = rand() % (size - i);
      swap(input[i], input[i + index]); // note: we are NOT swapping i and index, but i and i + index
    }
  }

  int rand5() {
    srand(time(0));
    return rand() % 5;
  }

  int rand7byRand5() {
    srand(time(0));
    while (true) {
      int res = rand5() * 5 + rand5();
      if (res < 21)
        return res % 7;
    }
  }

  int ninetyFivePercentile(vector<int> values) {
    // build histogram
    // max val is 4096, we allocate one more, so we can record 0 - 4096
    vector<int> hist(4097, 0);
    for (auto& v : values)
      hist[v]++;

    int sum = 0, len = 4097;
    int targetSize = (int)(0.05 * values.size());
    while (sum <= targetSize)
      sum += hist[--len];
    return len;
  }

  int ninetyFivePercentile_cheat(vector<int> values) {
    const long size = values.size() * 5L / 100 + 1;
    priority_queue<int, vector<int>, greater<int>> minHeap;

    for (auto& v : values) {
      minHeap.push(v);

      // throw away 95% of smallest elements, the remaining heap will be our 5% largest ones
      if (minHeap.size() > size) minHeap.pop();
    }

    return minHeap.top();
  }
};

class GenralizedSampling {
private:
  int m_size;
  int m_count;
  vector<int> m_samples;

public:
  GenralizedSampling(int size) {
    if (size <= 0)
      throw std::exception();

    m_size = size;
    m_count = 0;
  }

  vector<int> sample() {
    return m_samples;
  }

  void read(int i) {
    m_count++;
    if (m_count <= m_size)
      m_samples.push_back(i);
    else {
      int r = rand() % m_count;
      if (r < m_size)
        m_samples[r] = i;
    }
  }
};

int main()
{
  Sampling sol;

  {
    vector<int> values;
    for (int i = 1; i <= 100; ++i) values.push_back(i);
    auto res = sol.ninetyFivePercentile(values);
    res = sol.ninetyFivePercentile_cheat(values);
  }
  


  cin.get();
  return 0;
}

