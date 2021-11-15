
#include "Engine/OpenGL/VertexBuffer.h"

#include "glad/glad.h"
#include <stdexcept>

namespace Engine
{
	VertexBuffer::VertexBuffer(const void* data, const size_t size, Usage usage)
	{
		_id = 0;
		glGenBuffers(1, &_id);
		Bind();
		glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(size), data, UsageToGLenum(usage));
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &_id);
	}

	void VertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, _id);
	}

	void VertexBuffer::UnBind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}

	GLenum VertexBuffer::UsageToGLenum(Usage usage)
	{
		switch (usage)
		{
		case Usage::Static: return GL_STATIC_DRAW;
		case Usage::Dynamic: return GL_DYNAMIC_DRAW;
		case Usage::Stream: return GL_STREAM_DRAW;
		}
		throw std::runtime_error("Unknown usage draw!");
	}
}
