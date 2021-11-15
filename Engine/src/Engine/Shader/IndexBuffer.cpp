#include "Engine/Shader/IndexBuffer.h"
#include "glad/glad.h"
#include "Engine/Shader/VertexBuffer.h"

namespace Engine
{

	IndexBuffer::IndexBuffer(const void* data, size_t size, GLuint count, BufferUsage usage)
		:_count(count)
	{
		_id = 0;
		glGenBuffers(1, &_id);
		Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(size), data, BufferUsageToGLenum(usage));
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &_id);
	}

	void IndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
	}

	void IndexBuffer::UnBind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	}
}
