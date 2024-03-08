#ifndef ANIMATION_H
#define ANIMATION_H

#include "AnimationInfo.h"
namespace TDS {

	class AnimationPlayer
	{
	public:
		DLL_API void setAnimation(const Animation& animation);
		void returnToBindPose();
		void Update(float dt, float speed);

		// get list of transforms for the all of the bones at the current point of the animation.
		std::vector<Mat4>* getCurrentBonesMatrices() { return &m_BonesMatrices; }
		const std::string& getName() { return m_pAnimation->m_name; }

	private:

		void processNode(const AnimationNodes& _animNode, Mat4 parentMat, bool animated);
		Mat4 boneTransform(const AnimationNodes& _animNode);

		std::vector<Mat4> m_BonesMatrices{};
		const Animation* m_pAnimation{};
		double m_CurrentTime{ 0 };
	};
}
#endif // !ANIMATION_H
