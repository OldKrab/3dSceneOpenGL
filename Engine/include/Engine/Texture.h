#pragma once
#include <string>
#include "glad/glad.h"

namespace Engine {

	class Texture {
	public:
		Texture(const std::string& texturePath);
		~Texture();

		Texture(Texture&&) noexcept;
		Texture(const Texture&) = delete;
		Texture operator=(Texture&&) = delete;
		Texture operator=(const Texture&) = delete;

		void SetParameteri(GLenum name, GLint value) const;
		void Bind() const;
		static void UnBind();

	private:

		GLuint _id;
	};

	
}
