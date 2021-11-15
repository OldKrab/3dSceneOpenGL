#pragma once
#include "glad/glad.h"

namespace Engine {

	struct BufferElement {
		BufferElement(GLenum type, GLint count);
		GLenum type;
		GLint count;
		GLsizei size;
		GLsizei offset;
	};
}
