
-- Constants
BX_DIR   = path.join(ROOT_DIR, "../bx/")
BGFX_DIR = path.join(ROOT_DIR, "../bgfx/")

-- Compat
function AddCompatIncludes ()
    configuration { "x64" }
        includedirs {
            path.join(ROOT_DIR, "engine/compat/windows"),
        }
    configuration { }
end

PushGroup("graphics")
    -- Process individual module project scripts
    dofile "graphics.lua"
    dofile "tests.lua"

    -- Process external projects
    PushGroup("external")
        dofile "bgfx.lua"
    PopGroup()
PopGroup()
