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
    "bx/include/bx/*.h",
	"bx/include/bx/inline/*.inl",
    "bx/src/*.cpp",
}

excludes
{
	"bx/src/amalgamated.cpp",
    "bx/src/crtnone.cpp",
}

includedirs
{
    "bx/include",
    "bx/3rdparty",
}

filter "configurations:Debug"
    defines { "BX_CONFIG_DEBUG=1" }
    symbols "on"

filter "configurations:Release or configurations:Dist"
    defines { "BX_CONFIG_DEBUG=0" }
    optimize "on"

filter "action:vs*"
    defines { "_CRT_SECURE_NO_WARNINGS" }
	includedirs { "bx/include/compat/msvc", }

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
    "bimg/include/bimg/*.h",
    "bimg/src/image.cpp",
    "bimg/src/image_gnf.cpp",
    "bimg/src/*.h",
    "bimg/3rdparty/astc-encoder/**.cpp",
    "bimg/3rdparty/astc-encoder/**.h",
}

includedirs
{
	"bx/include",
    "bimg/include",
    "bimg/3rdparty/astc-encoder",
    "bimg/3rdparty/astc-encoder/include",
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
}

files
{
    "bgfx/include/**.h",
    "bgfx/src/*.cpp",
    "bgfx/src/*.h",
}

excludes
{
    "bgfx/src/amalgamated.cpp"
}

includedirs
{
    "bx/include",
    "bimg/include",
    "bgfx/include",
    "bgfx/3rdparty",
    "bgfx/3rdparty/khronos",
    "bgfx/3rdparty/dxsdk/include",
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
        "bgfx/src/glcontext_glx.cpp",
        "bgfx/src/glcontext_egl.cpp",
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
    files { "bgfx/src/*.mm", }

setBxCompat()