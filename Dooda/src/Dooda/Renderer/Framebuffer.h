#pragma once

#include "Dooda/Core/Core.h"

namespace Dooda 
{

	enum class FramebufferTextureFormat
	{
		None = 0,

		// Color
		RGBA8,
		RED_INTEGER,

		// Depth/stencil
		DEPTH24STENCIL8,

		// Defaults
		Depth = DEPTH24STENCIL8
	};

	struct FramebufferTextureSpecification
	{
		FramebufferTextureSpecification() = default;
		FramebufferTextureSpecification(FramebufferTextureFormat format)
			: TextureFormat(format) {}

		FramebufferTextureFormat TextureFormat = FramebufferTextureFormat::None;
		// TODO: filtering/wrap
	};

	struct FramebufferAttachmentSpecification
	{
		FramebufferAttachmentSpecification() = default;
		FramebufferAttachmentSpecification(std::initializer_list<FramebufferTextureSpecification> attachments)
			: Attachments(attachments) {}

		std::vector<FramebufferTextureSpecification> Attachments;
	};

	struct FramebufferSpecification
	{
		UINT Width = 0, Height = 0;
		FramebufferAttachmentSpecification Attachments;
		UINT Samples = 1;

		bool SwapChainTarget = false;
	};

	class Framebuffer
	{
	public:
		virtual ~Framebuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual UINT GetColorAttachmentRendererID(UINT index = 0) const = 0;
		virtual const FramebufferSpecification& GetSpecification() const = 0;

		virtual void Resize(UINT width, UINT height) = 0;
		virtual int ReadPixel(UINT attachmentIndex, int x, int y) = 0;

		virtual void ClearColourAttachment(UINT attachmentIndex, int value) = 0;

		static Ref<Framebuffer> Create(const FramebufferSpecification& spec);
	};
}
