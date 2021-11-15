#include "Engine/Shader/VertexBuffer.h"

#include "glad/glad.h"
#include <stdexcept>

namespace Engine
{

	VertexBuffer::VertexBuffer(const void* data, size_t size, BufferLayout layout, BufferUsage usage)
		:_layout(std::move(layout))
	{
		_id = 0;
		glGenBuffers(1, &_id);
		Bind();
		glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(size), data, BufferUsageToGLenum(usage));
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
