#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "Core.h"


namespace SYCAMORE_NAMESPACE
{
	class TShader
	{
	public:
		TShader(std::string& fragSource, std::string& vertSource);
		TShader(TShader& other) = delete;
		TShader& operator=(TShader& other) = delete;
		~TShader();
	
		static std::shared_ptr<TShader> Load(const char* fragPath, const char* vertPath);
		void Bind();
		void SetUniform(std::string location, glm::mat4 value);
		void SetUniform(std::string location, int value);
		void SetUniform(std::string location, glm::vec3 value);

		FORCEINLINE GLuint GetId() const
		{
			return mId;
		}

	private:
		static void ReadFileContentsInto(std::ifstream& fileStream, std::string& output);
		/**
		* @tparam ShaderType Valid values are GL_FRAGMENT_SHADER or GL_VERTEX_SHADER
		* @return The internal compiled shader ID
		*/
		template<GLenum ShaderType>
		static _NODISCARD GLuint CreateInternalShader(const std::string& source);
		/**
		* @return An **unbound** program with both the fragment and vertex shader linked and attached
		*/
		static _NODISCARD GLuint CreateInternalShaderProgram(GLuint fragId, GLuint vertId);

		FORCEINLINE int GetUniformLocation(std::string location)
		{
			auto result = mUniformLocationCache.find(location);

			if (result == mUniformLocationCache.end())
			{
				int internalLocation = glGetUniformLocation(mId, location.c_str());
				mUniformLocationCache[location] = internalLocation;
				return internalLocation;
			}

			return result->second;
		}

		std::unordered_map<std::string, int> mUniformLocationCache;
		GLuint mFragId;
		GLuint mVertId;
		GLuint mId;
	};
}