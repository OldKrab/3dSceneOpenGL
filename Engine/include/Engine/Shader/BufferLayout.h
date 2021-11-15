#pragma once
#include <vector>

#include "BufferElement.h"
#include "glad/glad.h"

namespace Engine {

	class BufferLayout {
	public:

		BufferLayout(std::vector<BufferElement> elements);

		GLsizei GetStride() const { return _stride; }

		const std::vector<BufferElement>& GetElements() const { return _elements; }

	private:

		std::vector<BufferElement> _elements;
		GLsizei _stride;
	};


}
