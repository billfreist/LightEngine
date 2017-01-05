

solution "light_engine"

    kind "ConsoleApp"

    -- Process configuration file
    dofile "config.lua"

    configuration {}

-- Core
dofile "../engine/modules/core/scripts/projects.lua"

-- Engine

    