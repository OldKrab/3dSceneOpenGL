#pragma once
#include "glad/glad.h"

namespace Engine {

	class ShaderProgram {
	public:
		ShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource);
		~ShaderProgram();

		ShaderProgram(ShaderProgram&&) = delete;
		ShaderProgram(const ShaderProgram&) = delete;
		ShaderProgram operator=(ShaderProgram&&) = delete;
		ShaderProgram operator=(const ShaderProgram&) = delete;

		void Use() const;

	private:
		static GLuint CreateShader(const char* shaderSource, GLenum shaderType);
		static void DeleteShader(GLuint shaderId);
		void LinkShaders(GLuint vertexShaderId, GLuint fragShaderId) const;


		GLuint _shaderProgramId;
	};

	
}
