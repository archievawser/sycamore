#include "Graphics/Geometry.h"
#include "Graphics/Vertex.h"


namespace SYCAMORE_NAMESPACE
{
	TGeometry::TGeometry(const TVertex* vertices, std::size_t vertexCount, const unsigned int* indices, std::size_t indexCount)
		: mVaoId(0), mVboId(0), mValid(false), mIndexCount(indexCount)
	{
		glGenVertexArrays(1, &mVaoId);
		glBindVertexArray(mVaoId);

		glGenBuffers(1, &mVboId);
		glBindBuffer(GL_ARRAY_BUFFER, mVboId);
		glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(TVertex), vertices, GL_STATIC_DRAW);

		glGenBuffers(1, &mIboId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIboId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indexCount, indices, GL_STATIC_DRAW);

		mValid = true;
	}


	TGeometry::TGeometry()
		: mVaoId(0), mVboId(0), mValid(false), mIndexCount(0)
	{ }


	TGeometry::~TGeometry()
	{
		mValid = false;

		glDeleteVertexArrays(1, &mVaoId);
		glDeleteBuffers(1, &mVboId);
		glDeleteBuffers(1, &mVaoId);
	}
}