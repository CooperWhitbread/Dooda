#include "ddpch.h"
#include "OpenGLFramebuffer.h"

#include <glad/glad.h>

namespace Dooda 
{

	static const uint32_t s_MaxFramebufferSize = 8192;

	namespace Utils 
	{

		static GLenum TextureTarget(bool multisampled)
		{
			return multisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
		}

		static void CreateTextures(bool multisampled, uint32_t* outID, uint32_t count)
		{
			glCreateTextures(TextureTarget(multisampled), count, outID);
		}

		static void BindTexture(bool multisampled, uint32_t id)
		{
			glBindTexture(TextureTarget(multisampled), id);
		}

		static void AttachColorTexture(uint32_t id, int samples, GLenum internalFormat, GLenum format, uint32_t width, uint32_t height, int index)
		{
			bool multisampled = samples > 1;
			if (multisampled)
			{
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, internalFormat, width, height, GL_FALSE);
				//TODO set parameters
			}
			else
			{
				glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, TextureTarget(multisampled), id, 0);
		}

		static void AttachDepthTexture(uint32_t id, int samples, GLenum format, GLenum attachmentType, uint32_t width, uint32_t height)
		{
			bool multisampled = samples > 1;
			if (multisampled)
			{
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
				//TODO set parameters
			}
			else
			{
				glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}

			glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, TextureTarget(multisampled), id, 0);
		}

		static bool IsDepthFormat(FramebufferTextureFormat format)
		{
			switch (format)
			{
			case FramebufferTextureFormat::DEPTH24STENCIL8:  return true;
			}

			return false;
		}

		static GLenum DoodaFBTextureFormatToGL(FramebufferTextureFormat format)
		{
			switch (format)
			{
			case FramebufferTextureFormat::RGBA8:       return GL_RGBA8;
			case FramebufferTextureFormat::RED_INTEGER: return GL_RED_INTEGER;
			}

			DD_CORE_ASSERT(false);
			return 0;
		}
	}//Namespace Utils

	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& spec)
		: d_Specification(spec)
	{
		for (auto spec : d_Specification.Attachments.Attachments)
		{
			if (!Utils::IsDepthFormat(spec.TextureFormat))
				d_ColorAttachmentSpecifications.emplace_back(spec);
			else
				d_DepthAttachmentSpecification = spec;
		}

		Invalidate();
	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		glDeleteFramebuffers(1, &d_RendererID);
		glDeleteTextures((GLsizei)d_ColorAttachments.size(), d_ColorAttachments.data());
		glDeleteTextures(1, &d_DepthAttachment);
	}

	void OpenGLFramebuffer::Invalidate()
	{
		if (d_RendererID)
		{
			glDeleteFramebuffers(1, &d_RendererID);
			glDeleteTextures((GLsizei)d_ColorAttachments.size(), d_ColorAttachments.data());
			glDeleteTextures(1, &d_DepthAttachment);

			d_ColorAttachments.clear();
			d_DepthAttachment = 0;
		}

		glCreateFramebuffers(1, &d_RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, d_RendererID);
		bool multisample = d_Specification.Samples > 1;

		// Attachments
		if (d_ColorAttachmentSpecifications.size())
		{
			d_ColorAttachments.resize(d_ColorAttachmentSpecifications.size());
			Utils::CreateTextures(multisample, d_ColorAttachments.data(), d_ColorAttachments.size());

			for (size_t i = 0; i < d_ColorAttachments.size(); i++)
			{
				Utils::BindTexture(multisample, d_ColorAttachments[i]);
				switch (d_ColorAttachmentSpecifications[i].TextureFormat)
				{
				case FramebufferTextureFormat::RGBA8:
				{
					Utils::AttachColorTexture(d_ColorAttachments[(int)i], d_Specification.Samples, GL_RGBA8, GL_RGBA, d_Specification.Width, d_Specification.Height, i);
					break;
				}
				case FramebufferTextureFormat::RED_INTEGER:
				{
					Utils::AttachColorTexture(d_ColorAttachments[(int)i], d_Specification.Samples, GL_R32I, GL_RED_INTEGER, d_Specification.Width, d_Specification.Height, i);
					break;
				}
				}
			}
		}

		if (d_DepthAttachmentSpecification.TextureFormat != FramebufferTextureFormat::None)
		{
			Utils::CreateTextures(multisample, &d_DepthAttachment, 1);
			Utils::BindTexture(multisample, d_DepthAttachment);
			switch (d_DepthAttachmentSpecification.TextureFormat)
			{
			case FramebufferTextureFormat::DEPTH24STENCIL8:
			{
				Utils::AttachDepthTexture(d_DepthAttachment, d_Specification.Samples, GL_DEPTH24_STENCIL8, 
					GL_DEPTH_STENCIL_ATTACHMENT, d_Specification.Width, d_Specification.Height);
				break;
			}
			}
		}

		if (d_ColorAttachments.size() > 1)
		{
			DD_CORE_ASSERT(d_ColorAttachments.size() <= 4);
			GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
			glDrawBuffers((GLsizei)d_ColorAttachments.size(), buffers);
		}
		else if (d_ColorAttachments.empty())
		{
			// Only depth-pass
			glDrawBuffer(GL_NONE);
		}

		DD_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, d_RendererID);
		glViewport(0, 0, d_Specification.Width, d_Specification.Height);
	}

	void OpenGLFramebuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::Resize(uint32_t width, uint32_t height)
	{
		if (width == 0 || height == 0 || width > s_MaxFramebufferSize || height > s_MaxFramebufferSize)
		{
			DD_CORE_WARN("Attempted to rezize framebuffer to {0}, {1}", width, height);
			return;
		}
		d_Specification.Width = width;
		d_Specification.Height = height;

		Invalidate();
	}

	int OpenGLFramebuffer::ReadPixel(uint32_t attachmentIndex, int x, int y)
	{
		DD_CORE_ASSERT(attachmentIndex < d_ColorAttachments.size());

		glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex);
		int pixelData;
		glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData);
		return pixelData;

	}

	void OpenGLFramebuffer::ClearColourAttachment(uint32_t attachmentIndex, int value)
	{
		DD_CORE_ASSERT(attachmentIndex < d_ColorAttachments.size());

		auto& spec = d_ColorAttachmentSpecifications[attachmentIndex];
		glClearTexImage(d_ColorAttachments[attachmentIndex], 0,
			Utils::DoodaFBTextureFormatToGL(spec.TextureFormat), GL_INT, &value);
	}

}