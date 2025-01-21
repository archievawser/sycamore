#include "Graphics/Shader.h"
#include <fstream>
#include <filesystem>
#include "Core.h"
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"


namespace SYCAMORE_NAMESPACE
{
	TShader::TShader(std::string& fragSource, std::string& vertSource)
	{
		mFragId = CreateInternalShader<GL_FRAGMENT_SHADER>(fragSource);
		mVertId = CreateInternalShader<GL_VERTEX_SHADER>(vertSource);
		mId = CreateInternalShaderProgram(mFragId, mVertId);
	}


	TShader::~TShader()
	{
		glDeleteProgram(mId);
		glDeleteShader(mFragId);
		glDeleteShader(mVertId);
	}


	void TShader::ReadFileContentsInto(std::ifstream& fileStream, std::string& output)
	{
		std::string line;

		while (std::getline(fileStream, line))
		{
			output += line + '\n';
		}
	}


	std::shared_ptr<TShader> TShader::Load(const char* fragPath, const char* vertPath)
	{
		std::cout << (std::filesystem::current_path()) << std::endl;
		assert(std::filesystem::exists(fragPath));
		assert(std::filesystem::exists(vertPath));

		std::string fragSource, vertSource;
		std::ifstream fragFile(fragPath), vertFile(vertPath);

		ReadFileContentsInto(fragFile, fragSource);
		ReadFileContentsInto(vertFile, vertSource);

		return std::make_shared<TShader>(fragSource, vertSource);
	}


	void TShader::Bind()
	{
		glUseProgram(mId);
	}


	void TShader::SetUniform(std::string location, glm::mat4 value)
	{
		glUniformMatrix4fv(GetUniformLocation(location), 1, GL_FALSE, glm::value_ptr(value));
	}


	void TShader::SetUniform(std::string location, int value)
	{
		glUniform1i(GetUniformLocation(location), value);
	}


	void TShader::SetUniform(std::string location, glm::vec3 value)
	{
		glUniform3f(GetUniformLocation(location), value.x, value.y, value.z);
	}


	template<GLenum ShaderType>
	GLuint TShader::CreateInternalShader(const std::string& source)
	{
		const char* cstring = source.c_str();
		GLuint shader = glCreateShader(ShaderType);
		glShaderSource(shader, 1, &cstring, nullptr);
		glCompileShader(shader);

		int compileSuccess;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compileSuccess);

		if (!compileSuccess)
		{
			char infoLog[512];
			int logLength;

			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
			glGetShaderInfoLog(shader, logLength, NULL, infoLog);
		}

		return shader;
	}


	GLuint TShader::CreateInternalShaderProgram(GLuint fragId, GLuint vertId)
	{
		GLuint program = glCreateProgram();
		glAttachShader(program, vertId);
		glAttachShader(program, fragId);
		glLinkProgram(program);

		int linkSuccess;
		glGetProgramiv(program, GL_LINK_STATUS, &linkSuccess);

		if (!linkSuccess)
		{
			char infoLog[512];
			int logLength;

			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
			glGetProgramInfoLog(program, logLength, NULL, infoLog);
		}

		return program;
	}
}