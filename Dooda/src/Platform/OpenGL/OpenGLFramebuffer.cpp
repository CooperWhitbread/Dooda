#include "Ddpch.h"
#include "OpenGLFramebuffer.h"

#include <glad/glad.h>

namespace Dooda {

	static const uint32_t s_MaxFramebufferSize = 8192;

	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& spec)
		: d_Specification(spec)
	{
		Invalidate();
	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		glDeleteFramebuffers(1, &d_RendererID);
		glDeleteTextures(1, &d_ColorAttachment);
		glDeleteTextures(1, &d_DepthAttachment);
	}

	void OpenGLFramebuffer::Invalidate()
	{
		if (d_RendererID)
		{
			glDeleteFramebuffers(1, &d_RendererID);
			glDeleteTextures(1, &d_ColorAttachment);
			glDeleteTextures(1, &d_DepthAttachment);
		}

		glCreateFramebuffers(1, &d_RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, d_RendererID);

		glCreateTextures(GL_TEXTURE_2D, 1, &d_ColorAttachment);
		glBindTexture(GL_TEXTURE_2D, d_ColorAttachment);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, d_Specification.Width, d_Specification.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, d_ColorAttachment, 0);

		glCreateTextures(GL_TEXTURE_2D, 1, &d_DepthAttachment);
		glBindTexture(GL_TEXTURE_2D, d_DepthAttachment);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, d_Specification.Width, d_Specification.Height);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, d_DepthAttachment, 0);

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

	void OpenGLFramebuffer::Resize(UINT width, UINT height)
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

}