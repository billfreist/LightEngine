
-- Process configuration file
dofile "../../../../scripts/config.lua"

local PROJ_PATH = path.getabsolute("..")

LightStaticLib("physics", PROJ_PATH)
AddDependency("engine/modules/core")
