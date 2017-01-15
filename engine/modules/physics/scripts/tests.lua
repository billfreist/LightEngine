
-- Process configuration file
dofile "../../../../scripts/config.lua"

LightConsoleApp("physics_tests", path.getabsolute("../tests"))
AddDependency("engine/modules/core")
AddDependency("engine/modules/physics")
