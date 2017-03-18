///
/// LICENSE
///

#include "pch.h"

LITE_NAMESPACE_BEGIN(lite, test_framework)

TEST(TestFramework, Init) {
}

TEST(TestFramework, True) {
    EXPECT_TRUE(true);
}

TEST(TestFramework, Eq) {
    EXPECT_EQ(1, 1);
}

LITE_NAMESPACE_END(lite, test_framework)

int LiteMain (int argc, char ** argsv) {
    testing::InitGoogleTest(&argc, argsv);
    return RUN_ALL_TESTS();
}
