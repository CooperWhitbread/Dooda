#pragma once

#include "Dooda/Core/Core.h"

namespace Dooda 
{

	class UniformBuffer
	{
	public:
		virtual ~UniformBuffer() {}
		virtual void SetData(const void* data, UINT size, UINT offset = 0) = 0;

		static Ref<UniformBuffer> Create(UINT size, UINT binding);
	};

}
