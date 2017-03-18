
-- Setup solution
solution "light_engine"

    -- Process configuration file
    dofile "config.lua"

    PushGroup("modules")

    -- Core
    dofile "../engine/modules/core/scripts/projects.lua"

    -- Framework
    dofile "../engine/modules/example_framework/scripts/projects.lua"
    dofile "../engine/modules/test_framework/scripts/projects.lua"

    -- Engine
    dofile "../engine/modules/graphics/scripts/projects.lua"
    dofile "../engine/modules/physics/scripts/projects.lua"
    dofile "../engine/modules/platform/scripts/projects.lua"

    PopGroup()

    configuration {}
