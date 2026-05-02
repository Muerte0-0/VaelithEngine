local BGFX_DIR = "bgfx"
local BIMG_DIR = "bimg"
local BX_DIR   = "bx"

-- =========================================================
-- bx compatibility
-- =========================================================
function setBxCompat()
    filter "action:vs*"
        includedirs { path.join(BX_DIR, "include/compat/msvc") }

    filter { "system:windows", "action:gmake" }
        includedirs { path.join(BX_DIR, "include/compat/mingw") }

    filter "system:macosx"
        includedirs { path.join(BX_DIR, "include/compat/osx") }
        buildoptions { "-x objective-c++" }

    filter {}
end

-- =========================================================
-- bx
-- =========================================================
project "bx"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"
    exceptionhandling "Off"
    rtti "Off"

targetdir (ThirdPartyBinDir)
objdir (ThirdPartyIntDir)

defines { "__STDC_FORMAT_MACROS" }

files
{
    path.join(BX_DIR, "include/bx/*.h"),
    path.join(BX_DIR, "include/bx/inline/*.inl"),
    path.join(BX_DIR, "src/*.cpp"),
}

excludes
{
    path.join(BX_DIR, "src/amalgamated.cpp"),
    path.join(BX_DIR, "src/crtnone.cpp"),
}

includedirs
{
    path.join(BX_DIR, "include"),
    path.join(BX_DIR, "3rdparty")
}

filter "configurations:Debug"
    defines { "BX_CONFIG_DEBUG=1" }
    symbols "on"

filter "configurations:Release or configurations:Dist"
    defines { "BX_CONFIG_DEBUG=0" }
    optimize "on"

filter "action:vs*"
    defines { "_CRT_SECURE_NO_WARNINGS" }

setBxCompat()

-- =========================================================
-- bimg
-- =========================================================
project "bimg"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"
    exceptionhandling "Off"
    rtti "Off"

targetdir (ThirdPartyBinDir)
objdir (ThirdPartyIntDir)

files
{
    path.join(BIMG_DIR, "include/bimg/*.h"),
    path.join(BIMG_DIR, "src/image.cpp"),
    path.join(BIMG_DIR, "src/image_gnf.cpp"),
    path.join(BIMG_DIR, "src/*.h"),
    path.join(BIMG_DIR, "3rdparty/astc-encoder/**.cpp"),
    path.join(BIMG_DIR, "3rdparty/astc-encoder/**.h"),
}

includedirs
{
    path.join(BX_DIR, "include"),
    path.join(BIMG_DIR, "include"),
    path.join(BIMG_DIR, "3rdparty/astc-encoder"),
    path.join(BIMG_DIR, "3rdparty/astc-encoder/include"),
}

links { "bx" }

filter "configurations:Debug"
    defines { "BX_CONFIG_DEBUG=1" }
    symbols "on"

filter "configurations:Release or configurations:Dist"
    defines { "BX_CONFIG_DEBUG=0" }
    optimize "on"

filter "action:vs*"
    defines { "_CRT_SECURE_NO_WARNINGS" }


setBxCompat()

-- =========================================================
-- bgfx
-- =========================================================
project "bgfx"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"
    exceptionhandling "Off"
    rtti "Off"

targetdir (ThirdPartyBinDir)
objdir (ThirdPartyIntDir)

defines
{
    "__STDC_FORMAT_MACROS",
    "BGFX_CONFIG_RENDERER_VULKAN=1" -- change later if needed
}

files
{
    path.join(BGFX_DIR, "include/bgfx/**.h"),
    path.join(BGFX_DIR, "src/*.cpp"),
    path.join(BGFX_DIR, "src/*.h")
}

excludes
{
    path.join(BGFX_DIR, "src/amalgamated.cpp")
}

includedirs
{
    path.join(BGFX_DIR, "include"),
    path.join(BIMG_DIR, "include"),
    path.join(BX_DIR, "include"),
    path.join(BGFX_DIR, "3rdparty"),
    path.join(BGFX_DIR, "3rdparty/khronos"),
    path.join(BGFX_DIR, "3rdparty/dxsdk/include"),
}

links { "bimg", "bx" }

filter "configurations:Debug"
    defines { "BX_CONFIG_DEBUG=1" }
    symbols "on"

filter "configurations:Release or configurations:Dist"
    defines { "BX_CONFIG_DEBUG=0" }
    optimize "on"

filter "action:vs*"
    defines { "_CRT_SECURE_NO_WARNINGS" }
    excludes
    {
        path.join(BGFX_DIR, "src/glcontext_glx.cpp"),
        path.join(BGFX_DIR, "src/glcontext_egl.cpp"),
    }
	
filter "system:windows"
    links
    {
        "gdi32",
        "user32",
        "kernel32",
        "psapi",
		"%{Library.Vulkan}",
    }

filter "system:macosx"
    files { path.join(BGFX_DIR, "src/*.mm") }

setBxCompat()