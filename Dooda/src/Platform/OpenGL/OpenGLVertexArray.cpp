#include "Ddpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Dooda
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		DD_PROFILE_FUNCTION();

		switch (type)
		{
		case ShaderDataType::Float:		return GL_FLOAT;
		case ShaderDataType::Float2:	return GL_FLOAT;
		case ShaderDataType::Float3:	return GL_FLOAT;
		case ShaderDataType::Float4:	return GL_FLOAT;
		case ShaderDataType::Mat3:		return GL_FLOAT;
		case ShaderDataType::Mat4:		return GL_FLOAT;
		case ShaderDataType::Int:		return GL_INT;
		case ShaderDataType::Int2:		return GL_INT;
		case ShaderDataType::Int3:		return GL_INT;
		case ShaderDataType::Int4:		return GL_INT;
		case ShaderDataType::Bool:		return GL_BOOL;
		}

		DD_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		DD_PROFILE_FUNCTION();

		glGenVertexArrays(1, &d_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		DD_PROFILE_FUNCTION();

		glDeleteVertexArrays(1, &d_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		DD_PROFILE_FUNCTION();

		glBindVertexArray(d_RendererID);
	}

	void OpenGLVertexArray::UnBind() const
	{
		DD_PROFILE_FUNCTION();

		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		DD_PROFILE_FUNCTION();

		DD_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(d_RendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(d_VertexBufferIndex);
			glVertexAttribPointer(d_VertexBufferIndex,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			d_VertexBufferIndex++;
		}

		d_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		DD_PROFILE_FUNCTION();

		glBindVertexArray(d_RendererID);
		indexBuffer->Bind();

		d_IndexBuffer = indexBuffer;
	}

}
