#pragma once

#include <memory>
#include <string>
#include <stdexcept>
#include <unordered_map>
#include <filesystem>
#include <fstream>
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "Graphics/Shader.h"
#include "Core.h"


namespace SYCAMORE_NAMESPACE
{
	/**
	 * @brief Manages runtime application resources like text files, shaders, textures, and 3D models.
	 * 
	 * File paths are relative to TAssetManager::Directory.
	 */
	class TAssetManager
	{
	public:
		/**
		 * @brief Loads an asset which will only exist as long as it's being used.
		 * For a resource which will be repeatedly loaded and is lightweight, use TAssetManager::Load
		 * @tparam TAsset
		 * @param path
		 * @return
		 */
		template<typename TAsset>
		static TAsset LoadTransient(std::string path)
		{
			//static_assert(false, "The request asset type is not loadable");
		}

		/**
		 * @brief Loads an asset once and stores it in memory for the lifetime of the application.
		 * @tparam TAsset
		 * @param path
		 * @return
		 */
		template<typename TAsset>
		static std::shared_ptr<TAsset> Load(std::string name)
		{
			// Store a single map of previously loaded paths and their assets per template instantiation
			static std::unordered_map<std::string, std::weak_ptr<TAsset>> loadedAssets;
			name = Directory + name;

#ifdef _DEBUG
			assert(("File not found, ensure it is relative to your assets directory.", std::filesystem::exists(name)));
#endif

			// If an asset of this type from this path hasn't been loaded yet
			// OR
			// The result from a previous load has been invalidated (freed), 
			// load it and store in map
			auto searchResult = loadedAssets.find(name);
			if (searchResult == loadedAssets.end() || (*searchResult).second.expired())
			{
				std::shared_ptr<TAsset> asset = std::shared_ptr<TAsset>(LoadInternal<TAsset>(Directory + name));

				// Store a weak reference to the loaded asset.
				loadedAssets[name] = asset;

				return asset;
			}

			// Store previously loaded asset if it was found
			return (*searchResult).second.lock();
		}

		static std::string Directory;

		template<typename TAsset>
		static TAsset* LoadInternal(std::string name)
		{
			//static_assert(false, "The request asset type is not loadable");
		}
	};


	std::string TAssetManager::Directory = "./assets/";


	/**
	 * @brief Load a shader file. Fragment and vertex sources should be indicated by the lines "#frag" and "#vert", with "#frag" seen first.
	 * @param name 
	 * @return 
	 */
	template<>
	TMaterial* TAssetManager::LoadInternal(std::string name)
	{
		// TODO: Use a faster file loading method
		std::ifstream file(name);
		std::string line;
		std::string fragSource;
		std::string vertSource;

		// Jump to fragment source
		while (std::getline(file, line) && line != "#frag");
		while (std::getline(file, line) && line != "#vert")
		{
			fragSource += line + '\n';
		}

		// Jump to vertex source
		while (std::getline(file, line))
		{
			vertSource += line + '\n';
		}

		return new TMaterial(new TShader(fragSource, vertSource));
	}


	/**
	 * @brief Loads and returns a text file's contents.
	 * @param name 
	 * @return 
	 */
	template<>
	FORCEINLINE std::string TAssetManager::LoadTransient(std::string name)
	{
		// TODO: Use a faster file loading method
		std::ifstream file(name);
		std::string line;
		std::string output;

		while (std::getline(file, line))
		{
			output += line + '\n';
		}

		return output;
	}


	/**
	 * @brief Load a mesh using Assimp
	 * @param name 
	 * @return 
	 */
	template<>
	FORCEINLINE TGeometry* TAssetManager::LoadInternal(std::string name)
	{
		static Assimp::Importer importer;

		// Load scene from file
		const aiScene* scene = importer.ReadFile(Directory + name, aiProcess_Triangulate);

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

		TGeometry* result = new TGeometry(vertices, mesh->mNumVertices, indices, indicesPerFace * mesh->mNumFaces);
		delete[] indices;
		delete[] vertices;
		return result;
	}
}