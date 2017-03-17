
-- Process individual module project scripts
PushGroup("template_proj")
    dofile "template_proj.lua"
    dofile "examples.lua"
    dofile "tests.lua"
PopGroup()
