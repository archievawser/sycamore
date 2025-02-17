#pragma once

#include <string>
#include <memory>
#include "GL/glew.h"
#include "Core.h"


namespace SYCAMORE_NAMESPACE
{
	template<GLenum Type>
	class TTexture
	{
	public:
		TTexture(GLint internalFormat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* data);

		TTexture(TTexture& other) = delete;

		TTexture& operator=(TTexture& other) = delete;

		~TTexture();

		static std::shared_ptr<TTexture<Type>> Load(const char* path);

		/**
		* @param level - The texture's level of detail / mip-map level
		* @param internalFormat - The number of components in each pixel
		* @param width
		* @param height
		* @param format - The pixel format (e.g GL_RGBA)
		* @param type - Data-type of the pixel data (e.g GL_FLOAT)
		*/
		void SetData(GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* data);

		void Bind()
		{
			glBindTexture(Type, mId);
		}

		static void Unbind()
		{
			glBindTexture(Type, 0);
		}

	private:
		GLuint mId;
	};


	typedef TTexture<GL_TEXTURE_1D> TTexture1D;
	typedef TTexture<GL_TEXTURE_2D> TTexture2D;
	typedef TTexture<GL_TEXTURE_3D> TTexture3D;
	typedef TTexture<GL_TEXTURE_RECTANGLE> TTextureRect;
}