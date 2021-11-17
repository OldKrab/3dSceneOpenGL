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
		Texture& operator=(Texture&& other) noexcept;
		Texture operator=(const Texture&) = delete;

		void SetParameteri(GLenum name, GLint value) const;
		void Bind() const;
		static void UnBind();
		std::string type;
        std::string path;
	private:

		GLuint _id;
	};

	
}
