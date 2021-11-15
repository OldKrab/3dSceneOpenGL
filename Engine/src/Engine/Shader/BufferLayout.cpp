#include "Engine/Shader/BufferLayout.h"

#include "glad/glad.h"
#include <stdexcept>

namespace Engine
{
	BufferLayout::BufferLayout(std::vector<BufferElement> elements)
		:_elements(std::move(elements))
	{
		_stride = 0;
		for(auto&& elem:_elements){
			elem.offset = _stride;
			_stride += elem.size;
		}
	}
}
