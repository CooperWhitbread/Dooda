#pragma once

#include "Dooda/Renderer/Framebuffer.h"

namespace Dooda 
{

	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecification& spec);
		virtual ~OpenGLFramebuffer();

		void Invalidate();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const override { DD_CORE_ASSERT(index < d_ColorAttachments.size()); return d_ColorAttachments[index]; }

		virtual const FramebufferSpecification& GetSpecification() const override { return d_Specification; }

		virtual void Resize(uint32_t width, uint32_t height) override;
		virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) override;

		virtual void ClearColourAttachment(uint32_t attachmentIndex, int value) override;
	private:
		uint32_t d_RendererID = 0;
		FramebufferSpecification d_Specification;

		std::vector<FramebufferTextureSpecification> d_ColorAttachmentSpecifications;
		FramebufferTextureSpecification d_DepthAttachmentSpecification = FramebufferTextureFormat::None;

		std::vector<uint32_t> d_ColorAttachments;
		uint32_t d_DepthAttachment = 0;
	};
}

