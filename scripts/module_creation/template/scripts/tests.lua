
-- Process configuration file
dofile "../../../../scripts/config.lua"

LightConsoleApp("template_proj_tests", path.getabsolute("../tests"))
AddDependency("engine/modules/core")
AddDependency("engine/modules/template_proj")