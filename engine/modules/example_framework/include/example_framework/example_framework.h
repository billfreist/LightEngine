///
/// LICENSE
///

#pragma once

namespace lite { namespace graphics {

class Scene;

}} // namespace lite::graphics


namespace lite { namespace example_framework {

#define LITE_EXAMPLE_DEFINITION(t)                                                       \
    static class ExampleDecl {                                                           \
    public:                                                                              \
        ExampleDecl () {                                                                 \
            ::lite::example_framework::ExampleBase::Register(                            \
                []() -> ::lite::example_framework::ExampleBase * { return LITE_NEW(t); } \
            );                                                                           \
        }                                                                                \
    } LITE_CONCAT(s_example, __LINE__);

class ExampleBase {
public:

    virtual ~ExampleBase () = default;

protected:

    ExampleBase () = default;

    /// Main update loop. A non-zero return value will terminate the application.
    virtual int Update () = 0;

    ///
    graphics::Scene * GetRenderScene () const;

public:

    using CreateFunc = ExampleBase * (*)();

    static void Register (CreateFunc createFunc);

    friend class ExampleApp;
    friend class ExampleFactory;
};


enum class ExampleFlag : uint32_t {

};
LITE_DEFINE_ENUM_BIT_OPERATORS(ExampleFlag);
using ExampleFlags = Flags<ExampleFlag>;

int RunExample (ExampleFlags flags, int argc, char ** argsv);

}} // namespace lite::example_framework
