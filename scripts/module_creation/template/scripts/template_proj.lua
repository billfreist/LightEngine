
-- Process configuration file
dofile "../../../../scripts/config.lua"

local PROJ_PATH = path.getabsolute("..")

LightStaticLib("template_proj", PROJ_PATH)
AddDependency("engine/modules/core")