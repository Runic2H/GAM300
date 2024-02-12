#include "SpotlightComponent.hxx"
#include "../TypeConversion.hxx"
#include "../EngineInterface.hxx"
#

namespace ScriptAPI
{
	SpotlightComponent::SpotlightComponent(TDS::EntityID ID) : entityID(ID), transform(TransformComponent(ID))
	{
		gameObject = EngineInterface::GetGameObject(ID);
	}

	Vector4 SpotlightComponent::GetDirection()
	{
		if (!TDS::GetSpotLightComponent(entityID))
		{
			// throw error instead (not sure how)
			return Vector4();
		}
		float x, y, z, w;
		TDS::GetSpotLightComponent(entityID)->GetDirection(x, y, z, w);

		return Vector4(x, y, w, z);

	}

	void SpotlightComponent::SetDirection(Vector4 value)
	{
		if (!TDS::GetSpotLightComponent(entityID))
		{
			// throw error instead (not sure how)
			return;
		}
		TDS::GetSpotLightComponent(entityID)->SetDirection(value.X, value.Y, value.Z, value.W);

		
	}

	Vector4 SpotlightComponent::GetColor()
	{
		if (!TDS::GetSpotLightComponent(entityID))
		{
			// throw error instead (not sure how)
			return Vector4();;
		}

		float x, y, z, w;
		TDS::GetSpotLightComponent(entityID)->GetColor(x, y, z, w);

		return Vector4(x, y, z, w);
	}

	void SpotlightComponent::SetColor(Vector4 value)
	{
		if (!TDS::GetSpotLightComponent(entityID))
		{
			// throw error instead (not sure how)
			return;
		}
		TDS::GetSpotLightComponent(entityID)->SetColor(value.X, value.Y, value.Z, value.W);
	}

	Vector4 SpotlightComponent::GetAttenuation()
	{
		if (!TDS::GetSpotLightComponent(entityID))
		{
			// throw error instead (not sure how)
			return Vector4();;
		}

		float x, y, z, w;
		TDS::GetSpotLightComponent(entityID)->GetAttenuation(x, y, z, w);

		return Vector4(x, y, z, w);
	}

	void SpotlightComponent::SetAttenuation(Vector4 value)
	{
		if (!TDS::GetSpotLightComponent(entityID))
		{
			// throw error instead (not sure how)
			return;
		}
		TDS::GetSpotLightComponent(entityID)->SetAttenuation(value.X, value.Y, value.Z, value.W);
	}

	float SpotlightComponent::GetAngle()
	{
		if (!TDS::GetSpotLightComponent(entityID))
		{
			// throw error instead (not sure how)
			return float();
		}
		return TDS::GetSpotLightComponent(entityID)->m_Angle;
	}

	void SpotlightComponent::SetAngle(float Angle)
	{
		if (!TDS::GetSpotLightComponent(entityID))
		{
			// throw error instead (not sure how)
			return;
		}
		TDS::GetSpotLightComponent(entityID)->m_Angle = Angle;
	}

	TDS::EntityID SpotlightComponent::GetEntityID()
	{
		return entityID;
	}

	void SpotlightComponent::SetEntityID(TDS::EntityID ID)
	{
		entityID = ID;
		transform = TransformComponent(ID);
		gameObject = EngineInterface::GetGameObject(ID);
	}

	void SpotlightComponent::SetEnabled(bool enabled)
	{
		TDS::setComponentIsEnable("SpotLight", GetEntityID(), enabled);
	}

	bool SpotlightComponent::GetEnabled()
	{
		return TDS::getComponentIsEnable("SpotLight", GetEntityID());
	}

}