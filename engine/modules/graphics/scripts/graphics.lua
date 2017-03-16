
local PROJ_PATH = path.getabsolute("..")

LightStaticLib("graphics", PROJ_PATH)

    -- External Deps
    AddCompatIncludes()
    includedirs {
        path.join(BGFX_DIR, "include"),
        path.join(BGFX_DIR, "examples"),
        path.join(BX_DIR, "include"),
    }
