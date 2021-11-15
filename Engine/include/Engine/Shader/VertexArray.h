#pragma once
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "glad/glad.h"

namespace Engine {

	class VertexArray {
	public:

		VertexArray();
		~VertexArray();

		VertexArray(VertexArray&&) = delete;
		VertexArray(const VertexArray&) = delete;
		VertexArray operator=(VertexArray&&) = delete;
		VertexArray operator=(const VertexArray&) = delete;

		void Bind() const;
		void UnBind() const;

		void AddVertexBuffer(const VertexBuffer& buffer);
		void SetIndexBuffer(const IndexBuffer& buffer);

		GLuint GetIndexesCount() const { return _indexesCount; }
	private:

		GLuint _vertexBuffersCount;
		GLuint _indexesCount = 0;
		GLuint _id;
	};


}
