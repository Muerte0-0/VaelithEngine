project "Editor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

targetdir (ProjectBinDir)
objdir (ProjectIntDir)

defines {
	
}

files {
	"Source/**.h",
	"Source/**.cpp",
}

externalincludedirs {
	"%{IncludeDir.spdlog}",
	"%{wks.location}/Engine/Source",
	"%{wks.location}/Vendor/",
	"%{IncludeDir.GLFW}",
	"%{IncludeDir.GLM}",
	"%{IncludeDir.ImGui}",
}

links {
	"Engine",
	"GLFW",
	"ImGui",
}

filter "system:windows"
	systemversion "latest"

defines {
	"WIN32_LEAN_AND_MEAN",
}

links {
	"Ws2_32.lib",
}

filter "system:linux"
systemversion "latest"

filter "configurations:Debug"
        defines { "DEBUG", "_DEBUG" }
        symbols "On"
        runtime "Debug"
        optimize "Off"

filter "configurations:Release"
    defines { "NDEBUG", "RELEASE" }
	linktimeoptimization "On"
    symbols "On"
    runtime "Release"
    optimize "Speed"
	

filter "configurations:Dist"
    defines { "NDEBUG", "DIST" }
	linktimeoptimization "On"
    symbols "Off"
    runtime "Release"
    optimize "Speed"