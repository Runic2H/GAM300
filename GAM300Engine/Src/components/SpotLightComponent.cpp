#include "components/SpotLightComponent.h"
#include "components/CompReflectionMacro.h"


namespace TDS
{

	RTTR_REGISTRATION{
		RTTR_REGISTER_WITH_NAME(SpotLightComponent, "SpotLight")
		RTTR_REGISTER_PROPERTY(SpotLightComponent, Position)
		RTTR_REGISTER_PROPERTY(SpotLightComponent, direction)
		RTTR_REGISTER_PROPERTY(SpotLightComponent, color)
		RTTR_REGISTER_PROPERTY(SpotLightComponent, attenuation)
		RTTR_REGISTER_PROPERTY(SpotLightComponent, Angle);
	}

	void SpotLightComponent::SetColor(float x, float y, float z, float w)
	{
		m_color = Vec4(x, y, z, w);
	}
	void SpotLightComponent::GetColor(float& x, float& y, float& z, float& w)
	{
		x = m_color.x;
		y = m_color.y;
		z = m_color.z;
		w = m_color.w;
	}
	void SpotLightComponent::SetDirection(float x, float y, float z, float w)
	{
		m_direction = Vec4(x, y, z, w);
	}
	void SpotLightComponent::GetDirection(float& x, float& y, float& z, float& w)
	{
		x = m_direction.x;
		y = m_direction.y;
		z = m_direction.z;
		w = m_direction.w;
	}
	void SpotLightComponent::SetAttenuation(float x, float y, float z, float w)
	{
		m_attenuation = Vec4(x, y, z, w);
	}
	void SpotLightComponent::GetAttenuation(float& x, float& y, float& z, float& w)
	{
		x = m_attenuation.x;
		y = m_attenuation.y;
		z = m_attenuation.z;
		w = m_attenuation.w;
	}
	void SpotLightComponent::SetAngle(float angle)
	{
		m_Angle = angle;
	}
	float SpotLightComponent::GetAngle()
	{
		return m_Angle;
	}
	

	SpotLightComponent* GetSpotLightComponent(EntityID entityID)
	{
		return ecs.getComponent<SpotLightComponent>(entityID);
	}
	SpotLightComponent::SpotLightComponent() :m_Position(), m_direction(), m_color(), m_attenuation(), m_Angle()
	{
	}
	SpotLightComponent::SpotLightComponent(SpotLightComponent&& toMove) noexcept :m_Position(toMove.m_Position), m_direction(toMove.m_direction), m_color(toMove.m_color),
		m_attenuation(toMove.m_attenuation)
	{
	}
}