
local PROJ_PATH = path.getabsolute("..")

LightStaticLib("test_framework", PROJ_PATH)

    includedirs {
        path.join(GTEST_DIR, "include"),
    }
