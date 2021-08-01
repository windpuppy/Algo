#include "TestFixture.h"
#include <String/String.h>

namespace StringTests {

    String obj;

    TEST(StringTests, MissingNumber) {
        vector<int> input{ 12, 11, 10, 9, 4, 5, 6, 7, 1, 3, 8 };
        auto res = obj.missingNumber(input);
        EXPECT_EQ(res, 2);
    }
}
