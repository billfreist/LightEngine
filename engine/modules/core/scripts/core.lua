
-- Process configuration file
dofile "../../../../scripts/config.lua"

local PROJ_PATH = path.getabsolute("..")

LightStaticLib("core", PROJ_PATH)
    files { path.join(PROJ_PATH, "src", "compress", "miniz", "*") }
    nopch { path.join(PROJ_PATH, "src", "compress", "miniz", "*") }

    configuration {}