#pragma once

#include "Dooda/Renderer/Texture.h"

#include <glad/glad.h>

namespace Dooda {

	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(uint32_t width, uint32_t height);
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual void Bind(uint32_t slot = 0) const override;

	public: //Getters
		virtual uint32_t GetWidth() const override { return d_Width; }
		virtual uint32_t GetHeight() const override { return d_Height; }

	public: //Setters
		virtual void SetData(void* data, uint32_t size) override;

	public: //Operators
		virtual bool operator==(const Texture& other) const override
		{
			return d_RendererID == ((OpenGLTexture2D&)other).d_RendererID;
		}

	private: //Variables
		std::string d_Path;
		uint32_t d_Width, d_Height;
		uint32_t d_RendererID;
		GLenum d_InternalFormat, d_DataFormat;
	};

}