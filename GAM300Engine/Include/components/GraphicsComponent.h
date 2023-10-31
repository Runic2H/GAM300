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

		inline void								ToggleRender(bool condition) { m_ShowMesh = condition; }
		inline void								TogglePointLight(bool status) { m_Pointlight = status; }
		inline void								SetPointLightID(int ID) { m_PointLightID = ID; }
		inline void								SetColor(Vec4 Color) { m_Color = Color; }
		inline void								SetColor(float r, float g, float b, float a) { m_Color = { r,g,b,a }; }

		
		inline bool								ShowMesh() { return m_ShowMesh; }
		inline SingleTypeReference<AssetModel>& GetAsset() { return m_AssetReference; }
		inline SingleTypeReference<Texture>&	GetTexture() { return m_TextureReference; }
		inline bool&							IsPointLight() { return m_Pointlight; }
		inline int&								GetPointLightID() { return m_PointLightID; }
		inline Vec4&							GetColor() { return m_Color; }

		RTTR_ENABLE(IComponent);
		RTTR_REGISTRATION_FRIEND

	private:
		SingleTypeReference<AssetModel> m_AssetReference;
		SingleTypeReference<Texture>	m_TextureReference;
		bool							m_ShowMesh = true;
		Vec4							m_Color;
		int								m_PointLightID{ -1 };
		bool							m_Pointlight{ false };
		bool							m_Debug{ false };


	};
}