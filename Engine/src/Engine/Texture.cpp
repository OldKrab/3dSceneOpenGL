#include "Engine/Texture.h"
#include "glad/glad.h"
#include <stdexcept>
#include "stb_image.h"

namespace Engine
{
	Texture::Texture(const std::string& texturePath)
	{
		_id = 0;
		glGenTextures(1, &_id);
		Bind();
		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			throw std::runtime_error("Failed to load texture");
		}
		stbi_image_free(data);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &_id);
	}

	Texture::Texture(Texture&& other) noexcept
	{
		_id = other._id;
		other._id = 0;
	}

	void Texture::SetParameteri(GLenum name, GLint value) const
	{
		Bind();
		glTexParameteri(GL_TEXTURE_2D, name, value);
	}

	void Texture::Bind() const
	{
		glBindTexture(GL_TEXTURE_2D, _id);
	}

	void Texture::UnBind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
