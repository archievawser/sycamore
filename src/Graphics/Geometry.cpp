#include "Graphics/Geometry.h"


TGeometry::TGeometry(const TVertex* vertices, std::size_t vertexCount)
	: mVaoId(0), mVboId(0), mValid(false), mVertexCount(vertexCount)
{
	glGenVertexArrays(1, &mVaoId);
	glBindVertexArray(mVaoId);

	glGenBuffers(1, &mVboId);
	glBindBuffer(GL_ARRAY_BUFFER, mVboId);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(TVertex), vertices, GL_STATIC_DRAW);

	mValid = true;
}


TGeometry::TGeometry()
	: mVaoId(0), mVboId(0), mValid(false), mVertexCount(0)
{ }


TGeometry::~TGeometry()
{
	mValid = false;

	glDeleteVertexArrays(1, &mVaoId);
	glDeleteBuffers(1, &mVboId);
}