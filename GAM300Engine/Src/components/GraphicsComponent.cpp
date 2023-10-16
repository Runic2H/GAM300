#include "components/GraphicsComponent.h"
namespace TDS
{
	GraphicsComponent::GraphicsComponent():m_AssetReference(),m_TextureReference(), m_ShowMesh(true)
	{
	}
	GraphicsComponent::GraphicsComponent(GraphicsComponent&& toMove) noexcept:m_AssetReference(toMove.m_AssetReference), m_TextureReference(toMove.m_TextureReference), m_ShowMesh(toMove.m_ShowMesh)
	{
	}
	DLL_API bool GraphicsComponent::Deserialize(const rapidjson::Value& obj)
	{
		obj;
		return true;
	}
	DLL_API bool GraphicsComponent::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		writer;
		return true;
	}
}