#pragma once

#include "Dooda/Renderer/Buffer.h"

namespace Dooda 
{

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(UINT size);
		OpenGLVertexBuffer(float* verticies, UINT size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const;
		virtual void UnBind() const;

	public: //Getters
		virtual const BufferLayout& GetLayout() const override { return d_Layout; }

	public: //Setters
		virtual void SetLayout(const BufferLayout& layout) override { d_Layout = layout; }
		virtual void SetData(const void* data, UINT size) override;
		
	private: //Variables
		UINT d_RendererID;
		BufferLayout d_Layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(UINT* indicies, UINT count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const;
		virtual void UnBind() const;

	public: //Getters
		virtual UINT GetCount() const { return d_Count; }

	private: //Variables
		UINT d_RendererID;
		UINT d_Count;
	};
}