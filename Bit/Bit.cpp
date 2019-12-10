#include "Bit.h"

int main()
{
  BitOperation sol;

  // Power of two
  {
    auto res = sol.isPowerOfTwo(3);
    res = sol.isPowerOfTwo(16);
  }

  // Different bits
  {
    // 5 (0101), 8 (1000)
    auto res = sol.diffBits(5, 8);
    res = sol.diffBits(-1, 2147483647);
  }

  // All unique chars
  {
    auto res = sol.allUnique("abb");
    res = sol.allUnique("/b10{-aAM");
  }

  // Reverse 32 bit unsigned int
  {
    auto res = sol.reverse32bit(90L);
  }

  // Hex
  {
    auto res = sol.hex(30);
  }

  // Bitwise AND of numbers in range
  {
    auto res = sol.rangeBitwiseAnd(4, 7);
    res = sol.rangeBitwiseAnd(1212453, 1234530);
  }

  cin.get();
  return 0;
}
