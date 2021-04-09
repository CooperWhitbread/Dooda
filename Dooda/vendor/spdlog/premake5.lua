project "spdlog"
	language "C++"
	cppdialect "C++17"
	kind "StaticLib"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"include/spdlog/details/null_mutex.h",
		"include/spdlog/details/pattern_formatter.h",
		"include/spdlog/details/pattern_formatter-inl.h",
		"include/spdlog/fmt/bundled/core.h",
		"include/spdlog/fmt/bundled/format-inl.h"
	}

    disablewarnings
    {
        "6011",
        "28182",
        "6385",
        "C26812",
        "26451",
		"26495",
		"26819",
		"26439",
		"26498",
		"28020",
		"26444"
    }

	filter "system:windows"
		systemversion "latest"

	filter "system:linux"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
