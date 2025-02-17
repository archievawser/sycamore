#pragma once

#include <vector>
#include <cstddef>
#include "GL/glew.h"
#include "Vertex.h"
#include "Core.h"


namespace SYCAMORE_NAMESPACE
{
	/**
	 * @brief A container for the data necessary to communicate geometric data to the graphics device
	 */
	class TGeometry
	{
	public:
		TGeometry(const TVertex* vertices, std::size_t vertexCount, const unsigned int* indices, std::size_t indexCount);

		TGeometry();

		TGeometry(TGeometry& other) = delete;

		TGeometry& operator=(TGeometry& other) = delete;

		~TGeometry();

		/**
		 * @brief Bind the vertex array of this geometry.
		 */
		FORCEINLINE void Bind()
		{
			glBindVertexArray(mVaoId);
		}

		FORCEINLINE std::size_t GetVertexCount() const
		{
			return mIndexCount;
		}

	private:
		std::size_t mIndexCount;
		GLuint mVaoId;
		GLuint mIboId;
		GLuint mVboId;
		bool mValid;
	};
}