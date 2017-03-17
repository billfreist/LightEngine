
-- Process individual module project scripts
PushGroup("example_framework")
    dofile "example_framework.lua"
    dofile "examples.lua"
    dofile "tests.lua"
PopGroup()
