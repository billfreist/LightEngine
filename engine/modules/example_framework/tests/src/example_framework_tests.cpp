///
/// LICENSE
///

#include "pch.h"

namespace lite { namespace example_framework {


}} // namespace lite::example_framework

int LiteMain (int argc, char ** argsv) {
    testing::InitGoogleTest(&argc, argsv);
    return RUN_ALL_TESTS();
}
