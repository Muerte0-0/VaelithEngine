include "ProjectDependencies.lua"

workspace "VaelithEngine"
	architecture "x86_64"
	startproject "Editor"
	configurations { "Debug", "Release", "Dist" }
	
filter "action:vs*"
	buildoptions { 
	"/utf-8",
	"/Zc:__cplusplus",
	"/Zc:preprocessor",
	}
	linkoptions { "/IGNORE:4006" }

linktimeoptimization ("Default")
multiprocessorcompile ("On")

OutputDir = "%{cfg.architecture}-%{cfg.buildcfg}-%{cfg.system}"

-- Project Build Directories
ProjectBinDir = "%{wks.location}/Binaries/" .. OutputDir .. "/%{prj.name}"
ProjectIntDir = "%{wks.location}/Intermediate/" .. OutputDir .. "/%{prj.name}"

-- Tools Build Directories
ToolsBinDir = "%{wks.location}/Binaries/" .. OutputDir .. "/Tools/%{prj.name}"
ToolsIntDir = "%{wks.location}/Intermediate/" .. OutputDir .. "/Tools/%{prj.name}"

-- Third Party Libraries Build Directories
ThirdPartyBinDir = "%{wks.location}/Binaries/" .. OutputDir .. "/ThirdParty/%{prj.name}"
ThirdPartyIntDir = "%{wks.location}/Intermediate/" .. OutputDir .. "/ThirdParty/%{prj.name}"

group "Apps"
include "Editor/Build-Editor.lua"
--include "ProjectBrowser/Build-ProjectBrowser.lua"
group ""

group "Core"
	include "Engine/Build-Engine.lua"
group ""

group "ThirdParty"
	include "Vendor/GLFW/Build-GLFW.lua"
	include "Vendor/bkaradzic/Build-BGFX.lua"
	include "Vendor/UI/Editor/Build-ImGui.lua"
group ""

group "Misc"
	
group ""