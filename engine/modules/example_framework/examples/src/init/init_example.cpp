///
/// LICENSE
///

#include "pch.h"

LITE_NAMESPACE_BEGIN(lite, example_framework)

class Init : public ExampleBase {
public:

    Init () = default;
    ~Init () override = default;

    int Update () override;
};
LITE_EXAMPLE_DEFINITION(Init);

int Init::Update () {
    return 0;
}

LITE_NAMESPACE_END(lite, example_framework)
