#pragma once

#include "Dooda/Renderer/Texture.h"

#include <glad/glad.h>

namespace Dooda 
{

	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(uint32_t width, uint32_t height);
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual void Bind(uint32_t slot = 0) const override;

		virtual bool IsLoaded() const override { return d_IsLoaded; }

	public: //Getters
		virtual uint32_t GetWidth() const override { return d_Width; }
		virtual uint32_t GetHeight() const override { return d_Height; }
		virtual uint32_t GetRendererID() const override { return d_RendererID; }

		virtual const std::string& GetPath() const override { return d_Path; }

	public: //Setters
		virtual void SetData(void* data, uint32_t size) override;

	public: //Operators
		virtual bool operator==(const Texture& other) const override
		{
			return d_RendererID == other.GetRendererID();
		}

	private: //Variables
		std::string d_Path;
		bool d_IsLoaded = false;
		uint32_t d_Width, d_Height;
		uint32_t d_RendererID;
		GLenum d_InternalFormat, d_DataFormat;
	};

}