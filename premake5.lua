include "./vendor/premake/premake_customization/solution_items.lua"
include "Dependencies.lua"

workspace "Dooda"
	architecture "x64"
	startproject "Adood"
	
	configurations 
	{
		"Debug",
		"Release",
		"Dist"
	}

	solution_items
	{
		".editorconfig"
	}
	
	flags
	{
		"MultiProcessorCompile"
	}
	 
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--Group the depndancies together
group "Depedencies"
	include "vendor/premake"
	include "Dooda/vendor/Box2D"
	include "Dooda/vendor/GLFW"
	include "Dooda/vendor/Glad"
	include "Dooda/vendor/imgui"
	include "Dooda/vendor/spdlog"
	include "Dooda/vendor/yaml-cpp"
group ""

include "Dooda"
include "Sandbox"
include "Adood"
