///
/// LICENSE
///

#include "pch.h"

LITE_NAMESPACE_BEGIN(lite, example_framework)


LITE_NAMESPACE_END(lite, example_framework)

int LiteMain (int argc, char ** argsv) {
    testing::InitGoogleTest(&argc, argsv);
    return RUN_ALL_TESTS();
}
