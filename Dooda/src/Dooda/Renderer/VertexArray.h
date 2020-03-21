#pragma once

#include "Dooda/Renderer/Buffer.h"

namespace Dooda
{

	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;

	public: //Getters
		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

	public: //Setters
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

	public: //Static Functions
		static Ref<VertexArray> SD_Create();
	};

}