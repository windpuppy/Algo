#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class BitOperation {
public:

  // e.g. 8 (1000), 7 (0111), their bit & is 0
  bool isPowerOfTwo(int n) {
    if (n <= 0) return false;
    auto res = n & (n - 1);
    return !res;
  }

  int diffBits(int a, int b) {
    // After XOR, all different bits will be 1
    a ^= b;

    int count = 0;

    // process right to left, bit by bit
    while (a != 0) {
      auto incre = a & 1; // last bit of a
      auto tmp = toBinary(a);
      auto tmp2 = toBinary(incre);
      count += incre;
      a >>= 1; // right shift

      if (a == -1) {
        count++;
        break;
      }

    }
    return count;
  }

  // Tips: split 0-255, in total of 256 chars into 32 x 32 matrix
  bool allUnique(string word) {
    vector<int> bit_vec(8, 0);

    for (int i = 0; i < (int)word.size(); ++i) {
      char ch = word[i];
      int row = ch / 32;
      int col = ch % 32;

      auto tmp1 = toBinary(bit_vec[row]);
      auto tmp2 = toBinary(1 << col);
      int matched = bit_vec[row] & (1 << col);
      if (matched != 0) // re-appearing chars
        return false;
      else
        bit_vec[row] |= (1 << col); // set bit_vec[row][col] to 1
    }

    return true;
  }

  long reverse32bit(long num) {
    for (int i = 0; i < 16; ++i) {
      long left = (num >> (31 - i)) & 1L; // get left bit
      long right = (num >> i) & 1L; // get right bit
      if (left != right) {
        swapBits(num, i, 31 - i);
      }
    }
    return num;
  }

  string hex(int number) {
    if (number == 0) return "0x0";

    string prefix("0x");
    string res = "";
    while (number > 0) {
      int rem = number % 16;
      res += rem < 10
        ? '0' + rem
        : 'A' + (rem - 10);
      //auto tmp = toBinary(number);
      number >>= 4; // number /= 16
    }

    reverse(res.begin(), res.end());
    return prefix + res;
  }

  int rangeBitwiseAnd(int a, int b) {
    if (a == 1 && b == 1) {
      return 1;
    }

    if ((int)log2(a) != (int)log2(b)) {
      return 0;
    }

    // keep all common bits between a and b from the left, and pad zeros to the right
    int nBits = (int)log2(a);
    while (nBits > 0) {
      // left to right keep searching, stops at the first different bit
      if (a >> nBits != b >> nBits) {
        return a >> nBits << nBits; // turn off last n bits of a
      }
      nBits--;
    }
    return 0;
  }



private:
  string toBinary(int n)
  {
    string out;
    while (n != 0) {
      out = (n % 2 == 0 ? "0" : "1") + out;
      n /= 2;
    }
    return out;
  }

  // use ^ to reverse bit
  // hint: 0 ^ 1 = 1, 1 ^ 1 = 0
  void swapBits(long& num, int i, int j) {
    num ^= 1L << i;
    num ^= 1L << (31 - i);
  }
};
