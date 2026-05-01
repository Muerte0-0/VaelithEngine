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
	"%{IncludeDir.BGFX}",
	"%{IncludeDir.BX}",
	"%{IncludeDir.BIMG}",
}

links {
	"GLFW",
	"bgfx",
	"bx",
	"bimg",
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
	defines "DEBUG"
	runtime "Debug"
	symbols "on"

filter "configurations:Release"
	defines "RELEASE"
	runtime "Release"
	optimize "on"

filter "configurations:Dist"
	defines "DIST"
	runtime "Release"
	optimize "on"