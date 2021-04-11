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

		virtual uint32_t GetColorAttachmentRendererID() const override { return d_ColorAttachment; }

		virtual const FramebufferSpecification& GetSpecification() const override { return d_Specification; }
	private:
		uint32_t d_RendererID;
		uint32_t d_ColorAttachment, d_DepthAttachment;
		FramebufferSpecification d_Specification;
	};
}

