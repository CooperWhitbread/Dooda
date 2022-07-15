#pragma once

#include <Dooda/Renderer/Texture.h>

#include <filesystem>

namespace Dooda 
{

	class ContentBrowserPanel
	{
	public:
		ContentBrowserPanel();

		void OnImGuiRender();
	private:
		std::filesystem::path d_CurrentDirectory;

		Ref<Texture2D> d_DirectoryIcon;
		Ref<Texture2D> d_FileIcon;
	};

}
