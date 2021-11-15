#pragma once
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

		void AddBuffer(const VertexBuffer& buffer);

	private:
	
		GLuint _buffersCount;
		GLuint _id;
	};


}
