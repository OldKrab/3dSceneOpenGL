#pragma once
#include "glad/glad.h"
#include "Engine/Shader/BufferLayout.h"

namespace Engine {

	class VertexBuffer {
	public:
		enum class Usage
		{
			Static, Dynamic, Stream
		};

		VertexBuffer(const void* data, size_t size, BufferLayout layout, Usage usage);
		~VertexBuffer();

		VertexBuffer(VertexBuffer&&) = delete;
		VertexBuffer(const VertexBuffer&) = delete;
		VertexBuffer operator=(VertexBuffer&&) = delete;
		VertexBuffer operator=(const VertexBuffer&) = delete;

		void Bind() const;
		static void UnBind();
		const BufferLayout& GetLayout() const { return _layout; }

	private:

		BufferLayout _layout;
		GLuint _id;
	};


}
