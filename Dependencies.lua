
-- Dooda Dependencies

VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["stb_image"] =				"%{wks.location}/Dooda/vendor/stb_image"
IncludeDir["yaml_cpp"] =				"%{wks.location}/Dooda/vendor/yaml-cpp/include"
IncludeDir["Box2D"] =					"%{wks.location}/Dooda/vendor/Box2D/include"
IncludeDir["GLFW"] =					"%{wks.location}/Dooda/vendor/GLFW/include"
IncludeDir["Glad"] =					"%{wks.location}/Dooda/vendor/Glad/include"
IncludeDir["ImGui"] =					"%{wks.location}/Dooda/vendor/ImGui"
IncludeDir["ImGuizmo"] =				"%{wks.location}/Dooda/vendor/ImGuizmo"
IncludeDir["glm"] =						"%{wks.location}/Dooda/vendor/glm"
IncludeDir["entt"] =					"%{wks.location}/Dooda/vendor/entt/include"
IncludeDir["shaderc"] =					"%{wks.location}/Dooda/vendor/shaderc/include"
IncludeDir["SPIRV_Cross"] =				"%{wks.location}/Dooda/vendor/SPIRV-Cross"
IncludeDir["VulkanSDK"] =				"%{VULKAN_SDK}/Include"

LibraryDir = {}
LibraryDir["VulkanSDK"] =				"%{VULKAN_SDK}/Lib"

Library = {}
Library["Vulkan"] =						"%{LibraryDir.VulkanSDK}/vulkan-1.lib"
Library["VulkanUtils"] =				"%{LibraryDir.VulkanSDK}/VkLayer_utils.lib"

Library["ShaderC_Debug"] =				"%{LibraryDir.VulkanSDK}/shaderc_sharedd.lib"
Library["SPIRV_Cross_Debug"] =			"%{LibraryDir.VulkanSDK}/spirv-cross-cored.lib"
Library["SPIRV_Cross_GLSL_Debug"] =		"%{LibraryDir.VulkanSDK}/spirv-cross-glsld.lib"
Library["SPIRV_Tools_Debug"] =			"%{LibraryDir.VulkanSDK}/SPIRV-Toolsd.lib"

Library["ShaderC_Release"] =			"%{LibraryDir.VulkanSDK}/shaderc_shared.lib"
Library["SPIRV_Cross_Release"] =		"%{LibraryDir.VulkanSDK}/spirv-cross-core.lib"
Library["SPIRV_Cross_GLSL_Release"] =	"%{LibraryDir.VulkanSDK}/spirv-cross-glsl.lib"
