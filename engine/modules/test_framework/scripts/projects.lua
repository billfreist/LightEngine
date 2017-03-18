
GTEST_DIR = "../../../../../googletest/googletest"

-- Process individual module project scripts
PushGroup("test_framework")
    dofile "test_framework.lua"
    dofile "tests.lua"

    PushGroup("external")
        dofile "google_test.lua"
    PopGroup()
PopGroup()
