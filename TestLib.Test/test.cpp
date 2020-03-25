#include "gtest/gtest.h"
#include "../TestLib/TestLib.h"

namespace Example {

    TEST(TestLibTests, Sum_Valid) {
      TestLib obj;
      int sum = obj.Sum(1, 2);
      EXPECT_EQ(3, sum);
    }
}
