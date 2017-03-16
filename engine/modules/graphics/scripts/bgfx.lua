
-- Include BX
dofile (path.join(BX_DIR, "scripts", "bx.lua"))
    defines {
        "_CRT_SECURE_NO_WARNINGS",
    }
    AddCompatIncludes()

-----------------------------------------------------------
-- Include BGFX
-----------------------------------------------------------
function copyLib ()
end

dofile (path.join(BGFX_DIR, "scripts", "bgfx.lua"))
    bgfxProject("", "StaticLib", "")
    files {
        path.join(BGFX_DIR, "examples/common", "bounds.*"),
        path.join(BGFX_DIR, "examples/common/debugdraw", "debugdraw.*"),
    }
    AddCompatIncludes()

    defines {
        "_CRT_SECURE_NO_WARNINGS",
        "BGFX_CONFIG_RENDERER_NOOP=1",
    }

    configuration { "x64" }
        defines {
            "BGFX_CONFIG_RENDERER_DIRECT3D9=1",
            "BGFX_CONFIG_RENDERER_DIRECT3D11=1",
            "BGFX_CONFIG_RENDERER_DIRECT3D12=1",
            "BGFX_CONFIG_RENDERER_OPENGL=1",
        }

    configuration { }
