#include "Engine/Shader/VertexArray.h"
#include "glad/glad.h"

namespace Engine
{
	VertexArray::VertexArray()
	{
		_id = 0;
		_buffersCount = 0;
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

		for (auto&& elem : buffer.GetLayout().GetElements())
		{
			glEnableVertexAttribArray(_buffersCount);
			glVertexAttribPointer(
				_buffersCount,
				elem.count,
				elem.type,
				GL_FALSE,
				buffer.GetLayout().GetStride(),
				reinterpret_cast<GLvoid*>(elem.offset)
			);
			++_buffersCount;
		}



	}
}
