#pragma once
#include <string>
#include <glm/glm.hpp>

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

		void SetUniformMat4(const std::string property, const glm::mat4& data);
		void SetUniformFloat(const std::string property, float value);
		void SetUniformVec3(const std::string property,  const glm::vec3& v);

		GLuint GetId() const {return _id;}

	private:
		static GLuint CreateShader(const char* shaderSource, GLenum shaderType);
		static void DeleteShader(GLuint shaderId);
		void LinkShaders(GLuint vertexShaderId, GLuint fragShaderId) const;


		GLuint _id;
	};

	
}
