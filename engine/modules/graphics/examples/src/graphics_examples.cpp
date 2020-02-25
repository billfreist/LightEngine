///
/// LICENSE
///

#include "pch.h"

int LiteMain (int argc, char ** argsv) {
    return lite::example_framework::RunExample(
        lite::example_framework::ExampleFlag::kNone,
        argc,
        argsv
    );
}
