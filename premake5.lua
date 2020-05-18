workspace "Dooda"
	architecture "x86_64"
	startproject "Sandbox"
	
	configurations 
	{
		"Debug",
		"Release",
		"Dist"
	}
	
	flags
	{
		"MultiProcessorCompile"
	}
	 
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--Include diectories relitive to root folder
IncludeDir = {}
IncludeDir["GLFW"] = "Dooda/vendor/GLFW/include"
IncludeDir["Glad"] = "Dooda/vendor/Glad/include"
IncludeDir["ImGui"] = "Dooda/vendor/imgui"
IncludeDir["glm"] = "Dooda/vendor/glm"
IncludeDir["stb_image"] = "Dooda/vendor/stb_image"

--Group the depndancies together
group "Depedencies"
	include "Dooda/vendor/GLFW"
	include "Dooda/vendor/Glad"
	include "Dooda/vendor/imgui"
	include "Dooda/vendor/spdlog"
group ""


project "Dooda"

	location "Dooda"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "Ddpch.h"
	pchsource "Dooda/src/Ddpch.cpp"

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines 
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs 
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links 
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}
	
	filter "system:windows" 
		systemversion "latest"
		
		defines 
		{
			"DD_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "DD_DEBUG"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Release"
		defines "DD_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "DD_DIST"
		runtime "Release"
		optimize "on"


project "Sandbox"
	
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs 
	{
		"Dooda/vendor/spdlog/include",
		"Dooda/src",
		"Dooda/vendor",
		"%{IncludeDir.glm}"
	}

	links 
	{
		"Dooda"
	}

	filter "system:windows" 
		systemversion "latest"

		defines 
		{
			"DD_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "DD_DEBUG"
		runtime "debug"
		symbols "on"
		
	filter "configurations:Release"
		defines "DD_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "DD_DIST"
		runtime "Release"
		optimize "on"
