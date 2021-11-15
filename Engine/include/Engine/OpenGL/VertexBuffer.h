#pragma once
#include "glad/glad.h"

namespace Engine {

	class VertexBuffer {
	public:
		enum class Usage
		{
			Static, Dynamic, Stream
		};

		VertexBuffer(const void* data, const size_t size, Usage usage);
		~VertexBuffer();

		VertexBuffer(VertexBuffer&&) = delete;
		VertexBuffer(const VertexBuffer&) = delete;
		VertexBuffer operator=(VertexBuffer&&) = delete;
		VertexBuffer operator=(const VertexBuffer&) = delete;

		void Bind() const;
		void UnBind() const;

	private:
		GLenum UsageToGLenum(Usage usage);

		GLuint _id;
	};


}
