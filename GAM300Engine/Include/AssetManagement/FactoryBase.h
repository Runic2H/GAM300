#pragma once
#include "ResourceManagement/ResourceManager.h"
#include "GraphicsResource/AssetModel.h"
#include "GraphicsResource/TextureInfo.h"
namespace TDS
{
	template <typename T>
	inline constexpr bool wrong_asset_type = false;

	template <typename T>
	class DLL_API AssetFactory
	{
	public:
		AssetFactory()
		{
			static_assert(wrong_asset_type<T>, "AssetFactory is not available for this type");
		}
		void Preload(ResourceManager& resourceMgr);
		static void Load(std::string_view path, SingleTypeReference<T>& model, ResourceManager& resourceMgr);

	};



}