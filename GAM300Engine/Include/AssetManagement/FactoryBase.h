#pragma once
#include "ResourceManagement/ResourceManager.h"
#include "GraphicsResource/AssetModel.h"
#include "GraphicsResource/TextureInfo.h"
namespace TDS
{
	template <typename T>
	inline constexpr bool always_false_v = false;

	template <typename T>
	class DLL_API AssetFactory
	{
	public:
		AssetFactory()
		{
			static_assert(always_false_v<T>, "AssetFactory is not available for this type");
		}
		void Preload(ResourceManager& resourceMgr);
		static void Load(std::string_view path, SingleTypeReference<T>& model, ResourceManager& resourceMgr);

	};

	struct GraphicsComponent
	{
		SingleTypeReference<AssetModel> m_Model;
		SingleTypeReference<Texture> m_Texture;
	};

}