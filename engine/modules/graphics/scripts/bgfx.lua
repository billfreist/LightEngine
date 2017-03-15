
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
    bgfxProject("", "StaticLib", "_CRT_SECURE_NO_WARNINGS")
    AddCompatIncludes()
