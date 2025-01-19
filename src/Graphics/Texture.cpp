#include "Graphics/Texture.h"
#include <string>
#include <memory>
//#include "stb/stb_image.h"
#include "Core.h"


template TTexture<GL_TEXTURE_1D>;
template TTexture<GL_TEXTURE_2D>;
template TTexture<GL_TEXTURE_3D>;
template TTexture<GL_TEXTURE_RECTANGLE>;


template<GLenum Type>
TTexture<Type>::TTexture(GLint internalFormat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* data)
{
	glGenTextures(1, &mId);
	Bind();

	glTexParameteri(Type, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(Type, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(Type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(Type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	SetData(0, internalFormat, width, height, format, type, data);
}


template<GLenum Type>
TTexture<Type>::~TTexture()
{
	Unbind();
	glDeleteTextures(1, &mId);
}


template<GLenum Type>
std::shared_ptr<TTexture<Type>> TTexture<Type>::Load(const char* path)
{
	int width, height;
	int channels;
	//const stbi_uc* data = stbi_load(path, &width, &height, &channels, 4);

	//std::shared_ptr<TTexture<Type>> tex = std::make_shared<TTexture<Type>>(GL_BGRA, width, height, GL_BGRA, GL_UNSIGNED_BYTE, data);
	//stbi_image_free((void*)data);

	return nullptr; //tex;
}


template<>
void TTexture<GL_TEXTURE_1D>::SetData(GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* data)
{
	// TODO: implement
}


template<>
void TTexture<GL_TEXTURE_2D>::SetData(GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* data)
{
	glTexImage2D(GL_TEXTURE_2D, level, internalFormat, width, height, 0, format, type, data);
}


template<>
void TTexture<GL_TEXTURE_RECTANGLE>::SetData(GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* data)
{
	glTexImage2D(GL_TEXTURE_RECTANGLE, level, internalFormat, width, height, 0, format, type, data);
}


template<>
void TTexture<GL_TEXTURE_3D>::SetData(GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* data)
{
	// TODO: implement
}