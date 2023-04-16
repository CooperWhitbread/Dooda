#pragma once

#include "Dooda/Renderer/VertexArray.h"

namespace Dooda
{

	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;

	public: //Getters
		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override{ return d_VertexBuffers; }
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const override { return d_IndexBuffer; }

	public: //Setters
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

	private: //Variables
		uint32_t d_RendererID;
		std::vector<Ref<VertexBuffer>> d_VertexBuffers;
		Ref<IndexBuffer> d_IndexBuffer; 
		uint32_t d_VertexBufferIndex = 0;
	};

}