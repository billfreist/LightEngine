
local PROJ_PATH = path.getabsolute("..")
TRACY_DIR = path.join(PROJ_PATH, "../../../..", "Tracy")

LightStaticLib("core", PROJ_PATH)

    -- MiniZ integration
    files { path.join(PROJ_PATH, "src", "compress", "miniz", "*") }
    nopch { path.join(PROJ_PATH, "src", "compress", "miniz", "*") }

    -- Tracy profiler integration
    files {
        -- path.join(TRACY_DIR, "TracyClient.cpp"), -- Handled in profiler.cpp
        path.join(TRACY_DIR, "Tracy.hpp"),
    }
    vpaths {
        ["External/Tracy/*"] = { path.join(TRACY_DIR, "**") },
    }
    includedirs { TRACY_DIR }
    nopch       { path.join(TRACY_DIR, "**") }

    configuration {}
