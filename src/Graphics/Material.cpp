#include "Graphics/Material.h"


namespace SYCAMORE_NAMESPACE
{
	TMaterial::TMaterial()
		: Shader(nullptr)
	{
	}


	TMaterial::TMaterial(std::shared_ptr<TShader> shader)
		: Shader(shader)
	{
	}


	void TMaterial::SetTexture(std::string&& uniformName, int slot, std::shared_ptr<TTexture2D> texture)
	{
		TextureUniformNames[slot] = uniformName;
		Textures[slot] = texture;
	}
}