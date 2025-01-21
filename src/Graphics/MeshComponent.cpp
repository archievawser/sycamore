#include "Graphics/MeshComponent.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"


namespace SYCAMORE_NAMESPACE
{
	TMeshComponent::TMeshComponent(std::shared_ptr<TGeometry> geometry, std::shared_ptr<TMaterial> material)
	{
		SetGeometry(geometry);

		if (material)
		{
			SetMaterial(material);
		}
	}


	TMeshComponent::TMeshComponent()
		: Geometry(), Material()
	{
	}


	TMeshComponent::~TMeshComponent()
	{
	}


	TMeshComponent* TMeshComponent::Load(std::string path)
	{
		static Assimp::Importer importer;

		// Load scene from file
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate);

		// Use first mesh found
		assert(("No meshes found within scene", scene->mNumMeshes > 0));
		aiMesh* mesh = scene->mMeshes[0];

		// Copy over indices (3 per face since triangulated)
		constexpr int indicesPerFace = 3;
		unsigned int* indices = new unsigned int[indicesPerFace * mesh->mNumFaces];

		for (int i = 0; i < mesh->mNumFaces; i++)
		{
			std::memcpy(indices + indicesPerFace * i, 
				mesh->mFaces[i].mIndices, 
				sizeof(unsigned int) * indicesPerFace);
		}

		// Generate vertices
		TVertex* vertices = new TVertex[mesh->mNumVertices];

		for (int i = 0; i < mesh->mNumVertices; i++)
		{
			// Copy over vertex assuming aiVector3D and glm::vec3 are identical in memory
			const glm::vec3 position = *(glm::vec3*)&mesh->mVertices[i];
			const glm::vec3 uv = *(glm::vec3*)&mesh->mTextureCoords[0][i];
			const glm::vec3 normal = *(glm::vec3*)&mesh->mNormals[i];

			vertices[i] = { position, uv, normal };
		}
		
		std::shared_ptr<TGeometry> geometry = std::make_shared<TGeometry>(vertices, mesh->mNumVertices, indices, indicesPerFace * mesh->mNumFaces);
		TMeshComponent* res = new TMeshComponent(geometry);

		delete[] indices;
		delete[] vertices;
		return res;
	}


	void TMeshComponent::SetGeometry(std::shared_ptr<TGeometry> geometry)
	{
		Geometry = geometry;
		geometry->Bind();
	}


	void TMeshComponent::SetMaterial(std::shared_ptr<TMaterial> material)
	{
		Material = material;
		Material->Shader->Bind();

		int positionAttribLocation = glGetAttribLocation(Material->Shader->GetId(), "position");
		glVertexAttribPointer(positionAttribLocation, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
		glEnableVertexAttribArray(positionAttribLocation);

		int normalAttribLocation = glGetAttribLocation(Material->Shader->GetId(), "normal");
		glVertexAttribPointer(normalAttribLocation, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (const void*)12);
		glEnableVertexAttribArray(normalAttribLocation);

		int uvAttribLocation = glGetAttribLocation(Material->Shader->GetId(), "uv");
		glVertexAttribPointer(uvAttribLocation, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (const void*)24);
		glEnableVertexAttribArray(uvAttribLocation);
	}
}