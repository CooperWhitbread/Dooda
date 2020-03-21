#include "Ddpch.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace Dooda
{
	/////////////////
	//Vertex Buffer//
	/////////////////

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* verticies, uint32_t size)
	{
		DD_PROFILE_FUNCTION();

		glGenBuffers(1, &d_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, d_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, verticies, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		DD_PROFILE_FUNCTION();

		glDeleteBuffers(1, &d_RendererID);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		DD_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, d_RendererID);
	}

	void OpenGLVertexBuffer::UnBind() const
	{
		DD_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	////////////////
	//Index Buffer//
	////////////////

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indicies, uint32_t count)
		:
		d_Count(count)
	{
		DD_PROFILE_FUNCTION();

		glGenBuffers(1, &d_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, d_RendererID);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indicies, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		DD_PROFILE_FUNCTION();

		glDeleteBuffers(1, &d_RendererID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		DD_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, d_RendererID);
	}

	void OpenGLIndexBuffer::UnBind() const
	{
		DD_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}
