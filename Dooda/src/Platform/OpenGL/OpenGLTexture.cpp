#include "Ddpch.h"
#include "OpenGLTexture.h"

#include <stb_image.h>

#include <glad/glad.h>

namespace Dooda {

	OpenGLTexture2DManager::OpenGLTexture2DManager()
	{
	}

	OpenGLTexture2DManager::~OpenGLTexture2DManager()
	{
		DD_PROFILE_FUNCTION();

		for (auto i = d_TextureInfo.begin(); i != d_TextureInfo.end(); i++)
		{
			glDeleteTextures(1, &i->second.RendererID);
		}
	}

	void OpenGLTexture2DManager::SetData(void* data, uint32_t size, std::string& textureName)
	{
		DD_PROFILE_FUNCTION();

		auto Find = d_TextureInfo.find(textureName);
		if (Find != d_TextureInfo.end())
		{
			glBindTexture(GL_TEXTURE_2D, Find->second.RendererID);
			uint32_t bpp = Find->second.DataFormat == GL_RGBA ? 4 : 3;
			DD_CORE_ASSERT(size == Find->second.Width * Find->second.Height * bpp, "Data must be entire texture!"); 
			glTextureSubImage2D(GL_TEXTURE_2D, 0, 0, 0, Find->second.Width, Find->second.Height, Find->second.DataFormat, GL_UNSIGNED_BYTE, data);
		}
	}

	void OpenGLTexture2DManager::Bind(const std::string& name, uint32_t slot) const
	{
		DD_PROFILE_FUNCTION();

		glActiveTexture(GL_TEXTURE0);
		auto Find = d_TextureInfo.find(name);
		if (Find != d_TextureInfo.end())
		{
			glBindTexture(GL_TEXTURE_2D, Find->second.RendererID);
		}
	}
	void OpenGLTexture2DManager::AddTexture(const std::string& path, const std::string& name)
	{
		DD_PROFILE_FUNCTION();

		//Variables
		int width, height, channels;
		TextureInfo TempTexture;
		GLenum internalFormat = 0, dataFormat = 0;

		stbi_set_flip_vertically_on_load(1);

		stbi_uc* data = nullptr;
		{
			DD_PROFILE_SCOPE("stbi_load - OpenGLTexture2DManager::AddTexture(const std::string& path, const std::string& name)")
			data = stbi_load(path.c_str(), &width, &height, &channels, 4);
		}
		DD_CORE_ASSERT(data, "Failed to load image!");

		TempTexture.Width = width;
		TempTexture.Height = height;

		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB;
			dataFormat = GL_RGBA;

		}

		TempTexture.InternalFormat = internalFormat;
		TempTexture.DataFormat = dataFormat;

		DD_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");

		//Generate the texture
		glGenTextures(1, &TempTexture.RendererID);
		glBindTexture(GL_TEXTURE_2D, TempTexture.RendererID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, TempTexture.Width, TempTexture.Height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, TempTexture.Width, TempTexture.Height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
		d_TextureInfo.emplace(name, TempTexture);
	}
	void OpenGLTexture2DManager::AddTexture(uint32_t width, uint32_t height, void* data, uint32_t size, const std::string& name)
	{
		DD_PROFILE_FUNCTION();

		TextureInfo TempTexture;
		TempTexture.Width = width;
		TempTexture.Height = height;

		TempTexture.InternalFormat = GL_RGBA8;
		TempTexture.DataFormat = GL_RGBA;

		//Generate the texture
		glGenTextures(1, &TempTexture.RendererID);
		glBindTexture(GL_TEXTURE_2D, TempTexture.RendererID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
		
		uint32_t bpp = TempTexture.DataFormat == GL_RGBA ? 4 : 3;
		DD_CORE_ASSERT(size == TempTexture.Width * TempTexture.Height * bpp, "Data must be entire texture!");

		glTexImage2D(GL_TEXTURE_2D, 0, TempTexture.InternalFormat, TempTexture.Width, TempTexture.Height, 0, TempTexture.DataFormat, GL_UNSIGNED_BYTE, data);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, TempTexture.Width, TempTexture.Height, TempTexture.DataFormat, GL_UNSIGNED_BYTE, data);

		d_TextureInfo.emplace(name, TempTexture);
	}
}