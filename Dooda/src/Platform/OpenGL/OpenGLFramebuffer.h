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

		virtual UINT GetColorAttachmentRendererID(UINT index = 0) const override { DD_CORE_ASSERT(index < d_ColorAttachments.size()); return d_ColorAttachments[index]; }

		virtual const FramebufferSpecification& GetSpecification() const override { return d_Specification; }

		virtual void Resize(UINT width, UINT height) override;
		virtual int ReadPixel(UINT attachmentIndex, int x, int y) override;

		virtual void ClearColourAttachment(UINT attachmentIndex, int value) override;
	private:
		UINT d_RendererID = 0;
		FramebufferSpecification d_Specification;

		std::vector<FramebufferTextureSpecification> d_ColorAttachmentSpecifications;
		FramebufferTextureSpecification d_DepthAttachmentSpecification = FramebufferTextureFormat::None;

		std::vector<uint32_t> d_ColorAttachments;
		UINT d_DepthAttachment = 0;
	};
}

