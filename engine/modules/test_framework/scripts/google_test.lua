
project "google_test"

    kind "StaticLib"

    files {
        path.join(GTEST_DIR, "include", "**.h"),
        path.join(GTEST_DIR, "src", "**.h"),
        path.join(GTEST_DIR, "src", "**.cc"),
    }

    excludes {
        path.join(GTEST_DIR, "src", "gtest-all.cc"),
        path.join(GTEST_DIR, "src", "gtest-main.cc"),
    }

    includedirs {
        path.join(GTEST_DIR),
        path.join(GTEST_DIR, "include"),
        path.join(GTEST_DIR, "src"),
    }

    defines {
        "GTEST_HAS_RTTI=0",
    }
