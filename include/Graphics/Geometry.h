#pragma once
#include <vector>
#include <cstddef>
#include "GL/glew.h"
#include "Vertex.h"
#include "Core.h"


class TGeometry
{
public:
	TGeometry(const TVertex* vertices, std::size_t vertexCount);
	TGeometry();
	TGeometry(TGeometry& other) = delete;
	TGeometry& operator=(TGeometry& other) = delete;
	~TGeometry();

	FORCEINLINE std::size_t GetVertexCount() const
	{
		return mVertexCount;
	}

	FORCEINLINE void Bind()
	{
		glBindVertexArray(mVaoId);
	}

private:
	std::size_t mVertexCount;
	GLuint mVaoId;
	GLuint mVboId;
	bool mValid;
};