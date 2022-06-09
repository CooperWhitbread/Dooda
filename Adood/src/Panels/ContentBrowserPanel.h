#pragma once

#include <filesystem>

#include "Dooda/Renderer/Texture.h"

namespace Dooda {

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
