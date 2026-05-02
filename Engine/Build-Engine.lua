project "Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

targetdir (ProjectBinDir)
objdir (ProjectIntDir)

pchheader "vltpch.h"
pchsource "Source/vltpch.cpp"

-- Default: enable PCH
filter {}
    enablepch "on"

-- Disable PCH for C Files
filter "files:**.c"
    enablepch "off"
    compileas "C"

-- Disable PCH for Third Party CPP Files
filter "files:**/Vendor/**.cpp"
    enablepch "off"

filter {}

defines {
	"_CRT_SECURE_NO_WARNINGS",
	"NOMINMAX",
}

files {
	"Config/**.**",
	"Resources/**.**",
	
	"Source/**.h",
	"Source/**.cpp",
}

includedirs {
	"Source",
	"%{IncludeDir.GLFW}",
	"%{IncludeDir.GLM}",
	"%{IncludeDir.ImGui}",
	"%{IncludeDir.bx}",
	"%{IncludeDir.bimg}",
	"%{IncludeDir.bgfx}",
	"%{IncludeDir.spdlog}",
}

links {
	"GLFW",
	"ImGui",
	"bx",
	"bimg",
	"bgfx",
}

filter "system:windows"
	systemversion "latest"
	
defines {
	"WIN32_LEAN_AND_MEAN",
}

links {
	"Ws2_32.lib",
	"dxgi",
	"d3d11",
	"d3d12",
	"d3dcompiler",
	"gdi32",
}

filter "system:linux"
	systemversion "latest"

links {
	"X11",
}

filter "configurations:Debug"
	defines { "DEBUG", "BX_CONFIG_DEBUG=1" }
	runtime "Debug"
	symbols "on"

filter "configurations:Release"
	defines { "RELEASE", "BX_CONFIG_DEBUG=0" }
	runtime "Release"
	optimize "on"

filter "configurations:Dist"
	defines { "DIST", "BX_CONFIG_DEBUG=0" }
	runtime "Release"
	optimize "on"