#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <ctime>

using namespace std;

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

  int rand6() {
      //srand(time(0));
      return rand() % 6 + 1;
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

  void samplingTest()
  {
      int step = 0, loop = 0;
      std::vector<int> count(24, 0);
      srand(time(0));

      while (loop < 1000000) {
          step += rand6();
          if (step >= 24) {
              loop++;
              step -= 24;
          }
          count[step]++;
      }

      for (int n = 0; n < 24; ++n) {
          cout << n << ": " << count[n] / 100 << "%" << endl;
      }
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
