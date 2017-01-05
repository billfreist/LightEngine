-- Process configuration file
dofile "../../../../scripts/config.lua"

LightConsoleApp("core_tests", path.getabsolute("../tests"))
AddDependency("engine/modules/core")
