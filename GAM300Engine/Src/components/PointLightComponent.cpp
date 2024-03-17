#include "components/PointLightComponent.h"
#include "components/CompReflectionMacro.h"

RTTR_REGISTRATION
{
	using namespace TDS;
	RTTR_REGISTER_WITH_NAME(PointLightComponent, "PointLight")
		RTTR_REGISTER_PROPERTY(PointLightComponent, Position)
		RTTR_REGISTER_PROPERTY(PointLightComponent, color)
		RTTR_REGISTER_PROPERTY(PointLightComponent, Attenuation);
}

namespace TDS
{

	PointLightComponent* GetPointLightComponent(EntityID entityID)
	{
		return ecs.getComponent<PointLightComponent>(entityID);
	}

	PointLightComponent::PointLightComponent() :m_Position(), m_color(), m_Attenuation()
	{
	}
	PointLightComponent::PointLightComponent(PointLightComponent&& toMove) noexcept :m_Position(toMove.m_Position), m_color(toMove.m_color), m_Attenuation(toMove.m_Attenuation)
	{
	}

	 void PointLightComponent::SetPointLightColor(float x, float y, float z, float w)
	{
		m_color = Vec4(x, y, z, w);
	}
	 void PointLightComponent::GetPointLightColorValues(float& x, float& y, float& z, float& w)
	{
		x = m_color.x;
		y = m_color.y;
		z = m_color.z;
		w = m_color.w;
	}
	 void PointLightComponent::SetPointLightAttenuation(float x, float y, float z, float w)
	{
		m_Attenuation = Vec4(x, y, z, w);
	}
	 void PointLightComponent::GetPointLightAttenuation(float& x, float& y, float& z, float& w)
	{
		x = m_Attenuation.x;
		y = m_Attenuation.y;
		z = m_Attenuation.z;
		w = m_Attenuation.w;
	}
}