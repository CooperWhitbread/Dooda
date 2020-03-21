#pragma once

namespace Dooda
{

	class GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

	public: //Static Functions
		static Scope<GraphicsContext> Create(void* window);
	};

}