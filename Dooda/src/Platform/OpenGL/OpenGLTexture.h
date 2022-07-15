#pragma once

#include "Dooda/Renderer/Texture.h"

#include <glad/glad.h>

namespace Dooda 
{

	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(UINT width, UINT height);
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual void Bind(UINT slot = 0) const override;

		virtual bool IsLoaded() const override { return d_IsLoaded; }

	public: //Getters
		virtual UINT GetWidth() const override { return d_Width; }
		virtual UINT GetHeight() const override { return d_Height; }
		virtual UINT GetRendererID() const override { return d_RendererID; }

	public: //Setters
		virtual void SetData(void* data, UINT size) override;

	public: //Operators
		virtual bool operator==(const Texture& other) const override
		{
			return d_RendererID == ((OpenGLTexture2D&)other).d_RendererID;
		}

	private: //Variables
		std::string d_Path;
		bool d_IsLoaded = false;
		UINT d_Width, d_Height;
		UINT d_RendererID;
		GLenum d_InternalFormat, d_DataFormat;
	};

}