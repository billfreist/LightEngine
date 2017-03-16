
-- Process individual module project scripts
PushGroup("physics")
    dofile "physics.lua"
    dofile "tests.lua"
PopGroup()
