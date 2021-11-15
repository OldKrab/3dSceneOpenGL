#pragma once

#include "glad/glad.h"

namespace Engine {


	enum class BufferUsage {
		Static, Dynamic, Stream
	};

	GLenum BufferUsageToGLenum(BufferUsage usage);
};

