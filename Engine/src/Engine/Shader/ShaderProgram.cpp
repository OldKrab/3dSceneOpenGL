
#include "Engine/Shader/ShaderProgram.h"
#include "glad/glad.h"

namespace Engine
{


	ShaderProgram::ShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource)
	{
		_shaderProgramId = glCreateProgram();
		const auto vertexShaderId = CreateShader(vertexShaderSource, GL_VERTEX_SHADER);
		const auto fragShaderId = CreateShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
		LinkShaders(vertexShaderId, fragShaderId);
		DeleteShader(vertexShaderId);
		DeleteShader(fragShaderId);
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(_shaderProgramId);
	}

	void ShaderProgram::Use() const
	{
		glUseProgram(_shaderProgramId);
	}

	GLuint ShaderProgram::CreateShader(const char* shaderSource, GLenum shaderType)
	{
		const GLuint shaderId = glCreateShader(shaderType);
		glShaderSource(shaderId, 1, &shaderSource, nullptr);
		glCompileShader(shaderId);
		return shaderId;
	}

	void ShaderProgram::DeleteShader(GLuint shaderId)
	{
		glDeleteShader(shaderId);
	}

	void ShaderProgram::LinkShaders(GLuint vertexShaderId, GLuint fragShaderId) const
	{
		glAttachShader(_shaderProgramId, vertexShaderId);
		glAttachShader(_shaderProgramId, fragShaderId);
		glLinkProgram(_shaderProgramId);
	}
}
