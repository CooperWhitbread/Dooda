include "./vendor/premake/premake_customization/solution_items.lua"

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

--Include diectories relitive to root folder
IncludeDir = {}IncludeDir["GLFW"] = "%{wks.location}/Dooda/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/Dooda/vendor/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/Dooda/vendor/imgui"
IncludeDir["glm"] = "%{wks.location}/Dooda/vendor/glm"
IncludeDir["stb_image"] = "%{wks.location}/Dooda/vendor/stb_image"
IncludeDir["entt"] = "%{wks.location}/Dooda/vendor/entt/include"
IncludeDir["yaml_cpp"] = "%{wks.location}/Dooda/vendor/yaml-cpp/include"

--Group the depndancies together
group "Depedencies"
	--include "vendor/premake"
	include "Dooda/vendor/GLFW"
	include "Dooda/vendor/Glad"
	include "Dooda/vendor/imgui"
	include "Dooda/vendor/spdlog"
	include "Dooda/vendor/yaml-cpp"
group ""

include "Dooda"
include "Sandbox"
include "Adood"
