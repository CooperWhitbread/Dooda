#pragma once

#include "Dooda/Renderer/Framebuffer.h"

namespace Dooda {

	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecification& spec);
		virtual ~OpenGLFramebuffer();

		void Invalidate();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual UINT GetColorAttachmentRendererID() const override { return d_ColorAttachment; }

		virtual const FramebufferSpecification& GetSpecification() const override { return d_Specification; }

		virtual void Resize(UINT width, UINT height) override;
	private:
		UINT d_RendererID = 0;
		UINT d_ColorAttachment = 0, d_DepthAttachment = 0;
		FramebufferSpecification d_Specification;
	};
}

