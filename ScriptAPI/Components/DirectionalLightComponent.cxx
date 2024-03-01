#include "DirectionalLightComponent.hxx"
#include "../EngineInterface.hxx"

namespace ScriptAPI
{
	
	Vector4 DirectionalLightComponent::GetColour()
	{
		return colour;
	}

	Vector4 DirectionalLightComponent::GetDirection()
	{
		return direction;
	}

	void DirectionalLightComponent::SetColour(Vector4 value)
	{
		colour = value;
	}

	void DirectionalLightComponent::SetDirection(Vector4 value)
	{
		direction = value;
	}

	void DirectionalLightComponent::SetEntityID(TDS::EntityID ID)
	{
		entityID = ID;
		transform = TransformComponent(ID);
		gameObject = EngineInterface::GetGameObject(ID);
	}

	TDS::EntityID DirectionalLightComponent::GetEntityID()
	{
		return entityID;
	}

	void DirectionalLightComponent::SetEnabled(bool enabled)
	{
		TDS::setComponentIsEnable("DirectionalLight", GetEntityID(), enabled);
	}
	bool DirectionalLightComponent::GetEnabled()
	{
		return TDS::getComponentIsEnable("DirectionalLight", GetEntityID());
	}

	DirectionalLightComponent::DirectionalLightComponent(TDS::EntityID ID) : entityID(ID), transform(TransformComponent(ID))
	{
		gameObject = EngineInterface::GetGameObject(ID);
	}

	// Private
	Vector4 DirectionalLightComponent::colour::get()
	{
		return Vector4(TDS::GetDirLightComponent(entityID)->m_color.x, TDS::GetDirLightComponent(entityID)->m_color.y,
			TDS::GetDirLightComponent(entityID)->m_color.z, TDS::GetDirLightComponent(entityID)->m_color.w);
	}

	void DirectionalLightComponent::colour::set(Vector4 value)
	{
		TDS::GetDirLightComponent(entityID)->m_color.x = value.X;
		TDS::GetDirLightComponent(entityID)->m_color.y = value.Y;
		TDS::GetDirLightComponent(entityID)->m_color.z = value.Z;
		TDS::GetDirLightComponent(entityID)->m_color.w = value.W;
	}

	Vector4 DirectionalLightComponent::direction::get()
	{
		return Vector4(TDS::GetDirLightComponent(entityID)->m_Direction.x, TDS::GetDirLightComponent(entityID)->m_Direction.y,
			TDS::GetDirLightComponent(entityID)->m_Direction.z, TDS::GetDirLightComponent(entityID)->m_Direction.w);
	}

	void DirectionalLightComponent::direction::set(Vector4 value)
	{
		TDS::GetDirLightComponent(entityID)->m_Direction.x = value.X;
		TDS::GetDirLightComponent(entityID)->m_Direction.y = value.Y;
		TDS::GetDirLightComponent(entityID)->m_Direction.z = value.Z;
		TDS::GetDirLightComponent(entityID)->m_Direction.w = value.W;
	}

}