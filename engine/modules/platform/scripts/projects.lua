
-- Process individual module project scripts
PushGroup("platform")
    dofile "platform.lua"
    dofile "examples.lua"
    dofile "tests.lua"
PopGroup()
