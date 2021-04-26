project "Adood"

	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"%{wks.location}/Dooda/vendor/spdlog/include",
		"%{wks.location}/Dooda/src",
		"%{wks.location}/Dooda/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}"
	}

	links
	{
		"Dooda"
	}

	filter "system:windows"
		systemversion "latest"

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