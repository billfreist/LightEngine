///
/// LICENSE
///

#include "pch.h"

namespace lite { namespace example_framework {

///
thread_local graphics::Scene * t_scene;

class ExampleFactory {
public:

    static ExampleFactory * Get ();

    void Register (ExampleBase::CreateFunc createCallback);

    ExampleBase * Create ();

private:

    std::vector<ExampleBase::CreateFunc> s_examples;
};

ExampleFactory * ExampleFactory::Get () {
    static ExampleFactory s_factory;
    return &s_factory;
}

void ExampleFactory::Register (ExampleBase::CreateFunc createCallback) {
    LITE_ASSERT(std::find(s_examples.begin(), s_examples.end(), createCallback) == s_examples.end());
    s_examples.push_back(createCallback);
}

ExampleBase * ExampleFactory::Create () {
    return s_examples.size () ? s_examples[0]() : nullptr;
}


graphics::Scene * ExampleBase::GetRenderScene () const {
    return t_scene;
}

void ExampleBase::Register (CreateFunc createCallback) {
    ExampleFactory::Get()->Register(createCallback);
}


class ExampleApp {
public:

    ExampleApp (ExampleFlags flags);

    int Run (int argc, char ** argsv);

private:

    ExampleFlags m_flags;
};

ExampleApp::ExampleApp (ExampleFlags flags)
    : m_flags(flags)
{
}

int ExampleApp::Run (int argc, char ** argsv) {
    LITE_REF(argc, argsv);

    // Create the window
    platform::Application * app    = platform::Application::Get();
    platform::WindowPtr     window = app->CreateWindow();

    // Create the render scene, passing the window handle to it for rendering
    graphics::Scene::Params sceneParams;
    sceneParams.windowHandle = window->GetHandle();
    graphics::Scene scene(sceneParams);
    t_scene = &scene;

    ExampleBase * example = nullptr;

    // Render loop
    int returnVal = 0;
    for (;;) {
        if (app->Update() || window->IsClosed()) {
            break;
        }

        // Pump the example
        if (!example)
            example = ExampleFactory::Get()->Create();

        if (example) {
            returnVal = example->Update();
            if (returnVal)
                break;
        }

        scene.Render();
    }
    if (example)
        LITE_DEL(example);
    t_scene = nullptr;

    return returnVal;
}

int RunExample (ExampleFlags flags, int argc, char ** argsv) {
    ExampleApp app(flags);
    return app.Run(argc, argsv);
}

}} // namespace lite::example_framework
