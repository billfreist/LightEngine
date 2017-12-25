
-- Constants
BX_DIR   = path.join(ROOT_DIR, "../bx/")
BIMG_DIR = path.join(ROOT_DIR, "../bimg/")
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
    dofile "examples.lua"
    dofile "tests.lua"

    -- Process external projects
    PushGroup("external")
        dofile "bgfx.lua"
    PopGroup()
PopGroup()
