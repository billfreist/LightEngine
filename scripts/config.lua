
ROOT_DIR = path.getabsolute("..")

configurations {
    "Debug",
    "Release",
}

platforms {
    "x64",
}

language "C++"

-- Disable iterator debugging, and allow CRT mismatches
defines {
    "_ALLOW_ITERATOR_DEBUG_LEVEL_MISMATCH=1",
    "_ALLOW_RUNTIME_LIBRARY_MISMATCH=1",
    "_HAS_ITERATOR_DEBUGGING=0",
    "_ITERATOR_DEBUG_LEVEL=0",
}

flags {
    "ExtraWarnings",
    "FatalWarnings",
    "NoRTTI",
    "StaticRuntime",
}

configuration { "Debug" }
    defines {
        "DEBUG",
    }
    flags {
        "DebugRuntime",
        "Symbols",
    }

configuration { "Release" }
    defines {
        "NDEBUG",
    }
    flags {
        "OptimizeSpeed",
        "ReleaseRuntime",
    }

configuration { "vs*", "x32 or x64" }
    buildoptions {
        "/wd4324", -- warning C4324: structure was padded due to alignment specifier
    }

configuration { "x64" }
    location  (path.join(ROOT_DIR, ".build", "projects", "windows", _ACTION, "x64"))

configuration { "Debug", "x64" }
    targetdir (path.join(ROOT_DIR, ".build", "target", "windows", _ACTION, "x64", "Debug"))
    objdir    (path.join(ROOT_DIR, ".build", "projects", "windows", _ACTION, "x64", "obj", "Debug"))

configuration { "Release", "x64" }
    targetdir (path.join(ROOT_DIR, ".build", "target", "windows", _ACTION, "x64", "Release"))
    objdir    (path.join(ROOT_DIR, ".build", "projects", "windows", _ACTION, "x64", "obj", "Release"))

configuration {}

-- Common project configurations
local function _CommonProjectConfig (name, directory)
    pchheader (name .. "_pch.h")
    pchsource (path.join(directory, "src", name .. "_pch.cpp"))

    includedirs {
        path.join(directory, "include"),
    }

    files {
        path.join(directory, "include", "**.h"),
        path.join(directory, "include", "**.inl"),
        path.join(directory, "natvis", "**.natvis"),
        path.join(directory, "src", "**.h"),
        path.join(directory, "src", "**.inl"),
        path.join(directory, "src", "**.cpp"),
    }

    vpaths {
        ["include/*"] = { path.join(directory, "include", "**") },
        ["src/*"]     = { path.join(directory, "src", "**") },
        ["natvis/*"]  = { path.join(directory, "natvis", "**") },
    }

    configuration {}
end

function AddDependency (modulePath)
    includedirs {
        path.join(ROOT_DIR, modulePath, "include"),
    }
    links {
        path.getname(modulePath)
    }
end

function LightStaticLib (name, directory)
    project (name)
        uuid (os.uuid(name))
        kind "StaticLib"

        _CommonProjectConfig(name, directory)
end

function LightConsoleApp (name, directory)
    project (name)
        uuid (os.uuid(name))
        kind "ConsoleApp"

        printf("test %s, %s", name, directory)
        _CommonProjectConfig(name, directory)
end
