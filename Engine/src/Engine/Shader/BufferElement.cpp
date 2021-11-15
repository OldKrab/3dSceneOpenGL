#include "Engine/Shader/BufferElement.h"

#include "glad/glad.h"
#include <stdexcept>

namespace Engine
{
	GLsizei GLenumToSize(GLenum type)
	{
		switch (type)
		{
		case GL_FLOAT: return sizeof(GLfloat);
		case GL_INT: return sizeof(GLint);
		default:
			throw std::runtime_error("Unknown type!");
		}
	}

	BufferElement::BufferElement(GLenum type, GLint count)
		:type(type),
		count(count),
		size(count* GLenumToSize(type)),
		offset(0)
	{
	}
}
