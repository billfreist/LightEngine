///
/// LICENSE
///

#include "pch.h"

#include <core/types.h>

namespace lite {

TEST(Vec3, Operators) {
    Vec3f a(2.0f);
    Vec3f b(1.0f);
    EXPECT_EQ(Vec3f(3.0f), a + b);
}

} // namespace lite
