#include "Ddpch.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace Dooda
{
	/////////////////
	//Vertex Buffer//
	/////////////////

	OpenGLVertexBuffer::OpenGLVertexBuffer(UINT size)
	{
		DD_PROFILE_FUNCTION();

		glCreateBuffers(1, &d_RendererID);

		// GL_ELEMENT_ARRAY_BUFFER is not valid without an actively bound VAO
		// Binding with GL_ARRAY_BUFFER allows the data to be loaded regardless of VAO state. 
		glBindBuffer(GL_ARRAY_BUFFER, d_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* verticies, UINT size)
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

	void OpenGLVertexBuffer::SetData(const void* data, UINT size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, d_RendererID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}


	////////////////
	//Index Buffer//
	////////////////

	OpenGLIndexBuffer::OpenGLIndexBuffer(UINT* indicies, UINT count)
		:
		d_Count(count)
	{
		DD_PROFILE_FUNCTION();

		glGenBuffers(1, &d_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, d_RendererID);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(UINT), indicies, GL_STATIC_DRAW);
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
