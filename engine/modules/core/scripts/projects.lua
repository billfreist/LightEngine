
-- Process individual module project scripts
PushGroup("core")
    dofile "core.lua"
    dofile "tests.lua"
PopGroup()
