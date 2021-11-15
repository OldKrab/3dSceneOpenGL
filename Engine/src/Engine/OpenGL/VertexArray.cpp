#include "Engine/OpenGL/VertexArray.h"
#include "glad/glad.h"

namespace Engine
{
	VertexArray::VertexArray()
	{
		_id = 0;
		glGenVertexArrays(1, &_id);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &_id);
	}

	void VertexArray::Bind() const
	{
		glBindVertexArray(_id);
	}

	void VertexArray::UnBind() const
	{
		glBindVertexArray(0);
	}

	void VertexArray::AddBuffer(const VertexBuffer& buffer)
	{
		Bind();
		buffer.Bind();

		glEnableVertexAttribArray(_buffersCount);
		glVertexAttribPointer(_buffersCount, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		++_buffersCount;
	}
}
