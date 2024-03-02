#include "components/animationComponent.h"
#include "components/CompReflectionMacro.h"

RTTR_REGISTRATION
{
	using namespace TDS;
	rttr::registration::class_<AnimationComponent>("AnimationComponent")
		.property("Filename", &AnimationComponent::m_AnimationJson)
		.property("isAnimated", &AnimationComponent::m_Animate)
		.property("Speed", &AnimationComponent::m_AnimationSpeed);
}
namespace TDS
{

	AnimationComponent::AnimationComponent() : m_Animate(false), m_AnimationJson(), m_AnimationSpeed(0.f)
	{

	}
	DLL_API AnimationComponent* GetAnimationComponent(EntityID entityID)
	{
		return ecs.getComponent<AnimationComponent>(entityID);
	}

}