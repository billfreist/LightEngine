///
/// LICENSE
///

#include "pch.h"

LITE_NAMESPACE_BEGIN(lite)

TEST(Vec3, Operators) {
    Vec3f a(2.0f);
    Vec3f b(1.0f);
    EXPECT_EQ(Vec3f(3.0f), a + b);
}

LITE_NAMESPACE_END(lite)
