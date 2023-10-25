#pragma once
#include "ecs/ecs.h"
#include "ResourceManagement/ResourceManager.h"
namespace TDS
{
	class AssetModel;
	class Texture;

	class GraphicsComponent : public IComponent
	{
	public:
		DLL_API GraphicsComponent();
		DLL_API GraphicsComponent(GraphicsComponent&& toMove) noexcept;
		DLL_API ~GraphicsComponent() = default;

		inline void ToggleRender(bool condition)
		{
			m_ShowMesh = condition;
		}
		inline bool ShowMesh()
		{
			return m_ShowMesh;
		}
		inline SingleTypeReference<AssetModel>& GetAsset()
		{
			return m_AssetReference;
		}
		inline SingleTypeReference<Texture>& GetTexture()
		{
			return m_TextureReference;
		}

		RTTR_ENABLE(IComponent);
		RTTR_REGISTRATION_FRIEND

	private:
		SingleTypeReference<AssetModel> m_AssetReference;
		SingleTypeReference<Texture>	m_TextureReference;
		bool m_ShowMesh = true;
		

	};
}