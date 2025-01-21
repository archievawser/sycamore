#pragma once

#include <vector>
#include <cstddef>
#include "GL/glew.h"
#include "Vertex.h"
#include "Core.h"


namespace SYCAMORE_NAMESPACE
{
	class TGeometry
	{
	public:
		TGeometry(const TVertex* vertices, std::size_t vertexCount, const unsigned int* indices, std::size_t indexCount);
		TGeometry();
		TGeometry(TGeometry& other) = delete;
		TGeometry& operator=(TGeometry& other) = delete;
		~TGeometry();

		FORCEINLINE std::size_t GetVertexCount() const
		{
			return mIndexCount;
		}

		FORCEINLINE void Bind()
		{
			glBindVertexArray(mVaoId);
		}

	private:
		std::size_t mIndexCount;
		GLuint mVaoId;
		GLuint mIboId;
		GLuint mVboId;
		bool mValid;
	};
}