#pragma once
#include "ecs/ecs.h"
#include "ResourceManagement/ResourceRef.h"
namespace TDS
{
	class AssetModel;
	class Texture;
	class MeshController;



	typedef enum 
	{
		MAIN_ROOT,
		CHILD_ROOT,
		CHILD,
		NOT_CHILD_MESH
	}MESH_NODE_TYPE;

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
		DLL_API inline void						SetColor(float r, float g, float b, float a) { m_Color = { r,g,b,a }; }
		inline void								SetTextureName(std::string input) { m_TextureName = input; }
		inline void								ToggleDebug(bool status) { m_Debug = status; }
		inline void								SetView2D(bool status) { m_UsedIn2D = status; }
		
		inline bool								ShowMesh() { return m_ShowMesh; }
		inline bool								View2D() { return m_UsedIn2D; }
		inline TypeReference<AssetModel>& 		GetAsset() { return m_AssetReference; }
		inline TypeReference<Texture>&			GetTexture() { return m_TextureReference; }
		inline TypeReference<MeshController>&	GetModel() { return m_MeshControllerRef; }
		inline bool&							IsPointLight() { return m_Pointlight; }
		inline int&								GetPointLightID() { return m_PointLightID; }
		DLL_API inline Vec4						GetColor() { return m_Color; }
		inline std::string&						GetTextureName() { return m_TextureName; }
		inline std::string&						GetMeshName() { return m_MeshName; }
		inline bool&							IsDebugOn() { return m_Debug; }
		inline void								setDebug(bool input) { m_Debug = input; }
		inline void								SetModelName(std::string input) { m_ModelName = input; }
		inline std::string&						GetModelName() { return m_ModelName; }


		RTTR_ENABLE(IComponent);
		RTTR_REGISTRATION_FRIEND

		Vec4							m_Color;
	private:
		bool							m_ShowMesh = true;
		int								m_PointLightID{ -1 };
		bool							m_Pointlight{ false };
		bool							m_Debug{ false };
	public:
		TypeReference<AssetModel> 		m_AssetReference;
		TypeReference<Texture>			m_TextureReference;
		TypeReference<MeshController>	m_MeshControllerRef;
		std::string						m_ModelName = "";
		std::string						m_MeshName = "";
		std::string						m_MeshNodeName = "";
		std::string						m_TextureName = "";
		bool							m_UsedIn2D{ false };
		


	};
	DLL_API GraphicsComponent* GetGraphicsComponent(EntityID entityID);
}