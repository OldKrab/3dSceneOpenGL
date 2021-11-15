#include "Engine/Shader/VertexBuffer.h"

#include "glad/glad.h"
#include <stdexcept>

namespace Engine
{
		GLenum UsageToGLenum(VertexBuffer::Usage usage)
	{
		switch (usage)
		{
		case VertexBuffer::Usage::Static: return GL_STATIC_DRAW;
		case VertexBuffer::Usage::Dynamic: return GL_DYNAMIC_DRAW;
		case VertexBuffer::Usage::Stream: return GL_STREAM_DRAW;
		}
		throw std::runtime_error("Unknown usage draw!");
	}


	VertexBuffer::VertexBuffer(const void* data, size_t size, BufferLayout layout, Usage usage)
		:_layout(std::move(layout))
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

	void VertexBuffer::UnBind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}


}
