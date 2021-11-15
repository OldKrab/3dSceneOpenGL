
#include "Engine/Shader/ShaderProgram.h"

#include <stdexcept>

#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"

namespace Engine
{


	ShaderProgram::ShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource)
	{
		_id = glCreateProgram();
		const auto vertexShaderId = CreateShader(vertexShaderSource, GL_VERTEX_SHADER);
		const auto fragShaderId = CreateShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
		LinkShaders(vertexShaderId, fragShaderId);
		DeleteShader(vertexShaderId);
		DeleteShader(fragShaderId);
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(_id);
	}

	void ShaderProgram::Use() const
	{
		glUseProgram(_id);
	}

	void ShaderProgram::SetUniformMatrix4fv(const std::string property, const glm::mat4& data)
	{
		const GLint transformLoc = glGetUniformLocation(_id, property.c_str());
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(data));
	}

	GLuint ShaderProgram::CreateShader(const char* shaderSource, GLenum shaderType)
	{
		const GLuint shaderId = glCreateShader(shaderType);
		glShaderSource(shaderId, 1, &shaderSource, nullptr);
		glCompileShader(shaderId);
		GLint successCompile;
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &successCompile);
		if(successCompile == GL_FALSE)
		{
			char log[1024];
			glGetShaderInfoLog(shaderId, 1024, nullptr, log);
			throw std::runtime_error(std::string("Cant compile shader: ") + log);
		}

		return shaderId;
	}

	void ShaderProgram::DeleteShader(GLuint shaderId)
	{
		glDeleteShader(shaderId);
	}

	void ShaderProgram::LinkShaders(GLuint vertexShaderId, GLuint fragShaderId) const
	{
		glAttachShader(_id, vertexShaderId);
		glAttachShader(_id, fragShaderId);
		glLinkProgram(_id);
	}
}
