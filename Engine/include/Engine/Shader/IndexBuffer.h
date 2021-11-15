#pragma once
#include "BufferUsage.h"
#include "glad/glad.h"

namespace Engine {

	class IndexBuffer {
	public:
		IndexBuffer(const void* data, size_t size, GLuint count, BufferUsage usage);
		~IndexBuffer();

		IndexBuffer(IndexBuffer&&) = delete;
		IndexBuffer(const IndexBuffer&) = delete;
		IndexBuffer operator=(IndexBuffer&&) = delete;
		IndexBuffer operator=(const IndexBuffer&) = delete;

		void Bind() const;
		static void UnBind();

		GLuint GetCount() const { return _count; }
	private:

		GLuint _id;
		GLuint _count;
	};


}
