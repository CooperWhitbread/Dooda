#pragma once

#include "Dooda/Core/Core.h"

namespace Dooda {

	struct FramebufferSpecification
	{
		uint32_t Width = 0, Height = 0;
		// FramebufferFormat Format = 
		uint32_t Samples = 1;

		bool SwapChainTarget = false;
	};

	class Framebuffer
	{
	public:
		virtual ~Framebuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual UINT GetColorAttachmentRendererID() const = 0;
		virtual const FramebufferSpecification& GetSpecification() const = 0;

		virtual void Resize(UINT width, UINT height) = 0;

		static Ref<Framebuffer> Create(const FramebufferSpecification& spec);
	};
}
