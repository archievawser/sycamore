#pragma once

#include <unordered_map>
#include <string>
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"


namespace SYCAMORE_NAMESPACE
{
	class TMaterial
	{
	public:
		TMaterial();

		TMaterial(TShader* shader);

		void SetTexture(std::string&& uniformName, int slot, std::shared_ptr<TTexture2D> texture);

		TShader* Shader;
		/**
		 * Maps the texture slot of a texture to the texture object
		 */
		std::unordered_map<int, std::shared_ptr<TTexture2D>> Textures;
		/**
		 * Maps the texture's slot index to its uniform sampler name
		 */
		std::unordered_map<int, std::string> TextureUniformNames;
	};
}