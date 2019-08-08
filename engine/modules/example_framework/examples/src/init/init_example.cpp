///
/// LICENSE
///

#include "pch.h"

namespace lite::example_framework {

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

} // namespace lite::example_framework
