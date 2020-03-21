#pragma once

#include "Dooda/Renderer/Texture.h"

#include <glad/glad.h>

namespace Dooda {

	struct TextureInfo
	{
		uint32_t Width, Height;
		uint32_t RendererID;
		GLenum InternalFormat, DataFormat;
	};

	class OpenGLTexture2DManager : public Texture2DManager
	{
	public:
		OpenGLTexture2DManager();
		virtual ~OpenGLTexture2DManager();

		virtual void Bind(const std::string& name, uint32_t slot = 0) const override;
		virtual void AddTexture(const std::string& path, const std::string& name) override;
		virtual void AddTexture(uint32_t width, uint32_t height, void* data, uint32_t size, const std::string& name) override;

	public: //Getters
		virtual uint32_t GetWidth(const std::string& name) const override { return d_TextureInfo.find(name)->second.Width; }
		virtual uint32_t GetHeight(const std::string& name) const override { return d_TextureInfo.find(name)->second.Height; }
		virtual uint32_t GetRendererID(const std::string& name) const override { return d_TextureInfo.find(name)->second.RendererID; }

	public: //Setters
		virtual void SetData(void* data, uint32_t size, std::string& textureName) override;

	public: //Variables
		std::unordered_map<std::string, TextureInfo> d_TextureInfo;
	};

}