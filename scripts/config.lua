
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
    pchheader ("pch.h")
    pchsource (path.join(directory, "src", "pch.cpp"))

    includedirs {
        path.join(directory, "include"),
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
