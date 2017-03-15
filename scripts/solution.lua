
-- Setup solution
solution "light_engine"

    -- Process configuration file
    dofile "config.lua"

    -- Core
    dofile "../engine/modules/core/scripts/projects.lua"

    -- Engine
    dofile "../engine/modules/graphics/scripts/projects.lua"
    dofile "../engine/modules/physics/scripts/projects.lua"

    configuration {}
