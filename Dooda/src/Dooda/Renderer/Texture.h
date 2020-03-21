#pragma once

#include "Dooda/Core/Core.h"

namespace Dooda {

	class TextureManager
	{
	public:
		TextureManager() = default;
		virtual ~TextureManager() = default;

		virtual void Bind(const std::string & name, uint32_t slot = 0) const = 0;

		virtual void AddTexture(const std::string & path, const std::string & name) = 0;
		virtual void AddTexture(uint32_t width, uint32_t height, void* data, uint32_t size, const std::string & name) = 0;

	public: //Getters
		virtual uint32_t GetWidth(const std::string& name) const = 0;
		virtual uint32_t GetHeight(const std::string& name) const = 0;
		virtual uint32_t GetRendererID(const std::string& name) const = 0;

	public: //Setters
		virtual void SetData(void* data, uint32_t size, std::string& textureName) = 0;

	};

	class Texture2DManager : public TextureManager
	{
	public:
		//static Ref<Texture2D> Create(uint32_t width, uint32_t height);
		static void Create();
	};

	extern Ref<Texture2DManager> s_Texture2DManager;

}