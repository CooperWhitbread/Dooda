#include "ddpch.h"
#include "OpenGLTexture.h"

#include <stb_image.h>

namespace Dooda {

	OpenGLTexture2D::OpenGLTexture2D(UINT width, UINT height)
		: d_Width(width), d_Height(height)
	{
		DD_PROFILE_FUNCTION();

		d_InternalFormat = GL_RGBA8;
		d_DataFormat = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &d_RendererID);
		glTextureStorage2D(d_RendererID, 1, d_InternalFormat, d_Width, d_Height);

		glTextureParameteri(d_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(d_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureParameteri(d_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(d_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		: d_Path(path)
	{
		DD_PROFILE_FUNCTION();

		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = nullptr;
		{
			DD_PROFILE_SCOPE("stbi_load - OpenGLTexture2D::OpenGLTexture2D(const std::string&)");
			data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		}
		DD_CORE_ASSERT(data, "Failed to load image!");
		d_Width = width;
		d_Height = height;

		GLenum internalFormat = 0, dataFormat = 0;
		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		d_InternalFormat = internalFormat;
		d_DataFormat = dataFormat;

		DD_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");

		glCreateTextures(GL_TEXTURE_2D, 1, &d_RendererID);
		glTextureStorage2D(d_RendererID, 1, internalFormat, d_Width, d_Height);

		glTextureParameteri(d_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(d_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureParameteri(d_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(d_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(d_RendererID, 0, 0, 0, d_Width, d_Height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		DD_PROFILE_FUNCTION();

		glDeleteTextures(1, &d_RendererID);
	}

	void OpenGLTexture2D::SetData(void* data, UINT size)
	{
		DD_PROFILE_FUNCTION();

		UINT bpp = d_DataFormat == GL_RGBA ? 4 : 3;
		DD_CORE_ASSERT(size == d_Width * d_Height * bpp, "Data must be entire texture!");
		glTextureSubImage2D(d_RendererID, 0, 0, 0, d_Width, d_Height, d_DataFormat, GL_UNSIGNED_BYTE, data);
	}

	void OpenGLTexture2D::Bind(UINT slot) const
	{
		DD_PROFILE_FUNCTION();

		glBindTextureUnit(slot, d_RendererID);
	}
}
