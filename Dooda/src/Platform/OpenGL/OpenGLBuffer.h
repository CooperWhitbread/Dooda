#pragma once

#include "Dooda/Renderer/Buffer.h"

namespace Dooda 
{

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* verticies, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const;
		virtual void UnBind() const;

	public: //Getters
		virtual const BufferLayout& GetLayout() const override { return d_Layout; }

	public: //Setters
		virtual void SetLayout(const BufferLayout& layout) override { d_Layout = layout; }
		
	private: //Variables
		uint32_t d_RendererID;
		BufferLayout d_Layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indicies, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const;
		virtual void UnBind() const;

	public: //Getters
		virtual uint32_t GetCount() const { return d_Count; }

	private: //Variables
		uint32_t d_RendererID;
		uint32_t d_Count;
	};
}