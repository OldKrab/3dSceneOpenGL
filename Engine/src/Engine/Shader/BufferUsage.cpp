#include "Engine/Shader/BufferUsage.h"

#include "glad/glad.h"
#include <stdexcept>

namespace Engine
{
	GLenum BufferUsageToGLenum(BufferUsage usage)
	{
		switch (usage)
		{
		case BufferUsage::Static: return GL_STATIC_DRAW;
		case BufferUsage::Dynamic: return GL_DYNAMIC_DRAW;
		case BufferUsage::Stream: return GL_STREAM_DRAW;
		}
		throw std::runtime_error("Unknown usage draw!");
	}
}
