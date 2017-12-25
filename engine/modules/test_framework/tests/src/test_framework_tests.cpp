///
/// LICENSE
///

#include "pch.h"

namespace lite { namespace test_framework {

TEST(TestFramework, Init) {
}

TEST(TestFramework, True) {
    EXPECT_TRUE(true);
}

TEST(TestFramework, Eq) {
    EXPECT_EQ(1, 1);
}

}} // namespace lite::test_framework

int LiteMain (int argc, char ** argsv) {
    testing::InitGoogleTest(&argc, argsv);
    return RUN_ALL_TESTS();
}
