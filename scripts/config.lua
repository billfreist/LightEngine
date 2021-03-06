
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
    "Cpp17",
    "ExtraWarnings",
    "FatalWarnings",
    "NoEditAndContinue",
    "NoRTTI",
    "StaticRuntime",
    "Symbols",
}

configuration { "Debug" }
    defines {
        "DEBUG",
    }
    flags {
        "DebugRuntime",
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
        "/wd4324",  -- warning C4324: structure was padded due to alignment specifier
        "/wd4595",  -- warning C4595: 'operator new': non-member operator new or delete functions may not be declared inline
        "/wd26495", -- warning C26495: Variable '' is uninitialized. Always initialize a member variable
        "/wd26812", -- warning C26812: The enum type 'enum' is unscoped. Prefer 'enum class' over 'enum'
        "/wd28251", -- warning C28251: Inconsistent annotation for 'new'
    }

configuration { "vs*", "x32 or x64", "Release" }
    buildoptions {
        "/wd4189", -- warning C4324: local variable is initialized but not referenced
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
    pchheader ("pch.h")
    pchsource (path.join(directory, "src", "pch.cpp"))

    includedirs {
        path.join(directory, "include"),
        path.join(directory, "src"),
    }

    files {
        path.join(directory, "include", "**.h"),
        path.join(directory, "include", "**.inl"),
        path.join(directory, "natvis", "**.natvis"),
        path.join(directory, "scripts", "**.lua"),
        path.join(directory, "src", "**.h"),
        path.join(directory, "src", "**.inl"),
        path.join(directory, "src", "**.cpp"),
    }

    vpaths {
        ["include/*"] = { path.join(directory, "include", "**") },
        ["src/*"]     = { path.join(directory, "src", "**") },
        ["genie/*"]   = { path.join(directory, "scripts", "**") },
        ["natvis/*"]  = { path.join(directory, "natvis", "**") },
    }

    configuration {}
end

function AddDepsLib (params, toProcess)
    for _, v in ipairs(toProcess) do
        if table.contains(params.Finished, v) == false then
            table.insert(params.Finished, v)
            includedirs {
                path.join(ROOT_DIR, v, "include")
            }

            -- Recurse through
            dofile (path.join(ROOT_DIR, v, "scripts", "deps.lua"))
        end
    end
end

function AddDepsApplication (params, toProcess)
    for _, v in ipairs(toProcess) do
        if table.contains(params.Finished, v) == false then
            table.insert(params.Finished, v)
            includedirs {
                path.join(ROOT_DIR, v, "include")
            }
            links {
                path.getname(v)
            }

            -- Process externals
            dofile (path.join(ROOT_DIR, v, "scripts", "externals.lua"))

            -- Recurse through @@BILL At some point this will need to append
            -- unique entries to the list and *then* sort based on weights
            -- to ensure proper link order
            dofile (path.join(ROOT_DIR, v, "scripts", "deps.lua"))
        end
    end
end

local _GROUP_STACK = {}
function PushGroup (name)
    table.insert(_GROUP_STACK, name)
    local fullName = table.concat(_GROUP_STACK, "/")
    group(fullName)
end

function PopGroup ()
    table.remove(_GROUP_STACK, #_GROUP_STACK)
    local fullName = table.concat(_GROUP_STACK, "/")
    group(fullName)
end

function LightStaticLib (name, directory)
    project (name)
        uuid (os.uuid(name))
        kind "StaticLib"

        _CommonProjectConfig(name, directory)

        -- Process deps
        DEPS_PARAMS = {
            Callback = AddDepsLib,
            Finished = {}
        }
        dofile (path.join(ROOT_DIR, directory, "scripts", "deps.lua"))
        DEPS_PARAMS = nil
end

function LightConsoleApp (name, directory)
    project (name)
        uuid (os.uuid(name))
        kind "ConsoleApp"

        _CommonProjectConfig(name, directory)

        -- Process deps
        DEPS_PARAMS = {
            Callback = AddDepsApplication,
            Finished = {}
        }
        dofile (path.join(ROOT_DIR, directory, "scripts", "deps.lua"))
        DEPS_PARAMS = nil
end

function LightWindowedApp (name, directory)
    project (name)
        uuid (os.uuid(name))
        kind "WindowedApp"

        _CommonProjectConfig(name, directory)

        -- Process deps
        DEPS_PARAMS = {
            Callback = AddDepsApplication,
            Finished = {}
        }
        dofile (path.join(ROOT_DIR, directory, "scripts", "deps.lua"))
        DEPS_PARAMS = nil
end

function LightTestApp (name, directory)
    LightConsoleApp(name, directory)
        local GTEST_INCLUDE = path.join(ROOT_DIR, "../googletest/googletest/include")
        includedirs {
            GTEST_INCLUDE,
        }
end
