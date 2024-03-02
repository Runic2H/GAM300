#pragma once
#include "ecs/ecs.h"
#include "Animation/AnimationLoader.h"
#include <string>
namespace TDS
{
	class AnimationComponent : public IComponent
	{
	public:
		DLL_API AnimationComponent();
		DLL_API ~AnimationComponent() = default;
		//setter
		inline void	setAnimationJsonFile(const std::string& input) { m_AnimationJson = input; }
		inline void ToggleAnimate(bool _animate) { m_Animate = _animate; }
		inline void setAnimateSpeed(float& _speed) { m_AnimationSpeed = _speed; }

		//getter
		inline bool& getAnimate() { return m_Animate; }
		inline std::string& getAnimationFile() { return m_AnimationJson; }
		inline float& getAnimateSpeed() { return m_AnimationSpeed; }
		inline AnimationData& getAnimationData() { return m_AnimationData; }
		RTTR_ENABLE(IComponent);
		RTTR_REGISTRATION_FRIEND

	public: 
		bool m_Animate{ false };//toggling to animate or not to animate the mesh
		std::string m_AnimationJson{};//json for bone and ticks information 
		float m_AnimationSpeed{ 0.f };//adjust on this speed * dt
		AnimationData m_AnimationData;

	};

	DLL_API AnimationComponent* GetAnimationComponent(EntityID entityID);
}