#include "components/graphicsComponent.h"

RTTR_REGISTRATION
{
	using namespace TDS;

	rttr::registration::class_<GraphicsComponent>("Graphics Component");
}

namespace TDS
{
	GraphicsComponent::GraphicsComponent(): m_AssetReference(),
											m_TextureReference(),
											m_ShowMesh(true)
	{ }

	GraphicsComponent::GraphicsComponent(GraphicsComponent&& toMove) noexcept: m_AssetReference(toMove.m_AssetReference), 
																			   m_TextureReference(toMove.m_TextureReference), 
																			   m_ShowMesh(toMove.m_ShowMesh)
	{ }
}