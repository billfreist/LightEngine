///
/// LICENSE
///

#include "pch.h"

namespace lite { namespace platform {


}} // namespace lite::platform

int LiteMain (int argc, char ** argsv) {
    testing::InitGoogleTest(&argc, argsv);
    return RUN_ALL_TESTS();
}
