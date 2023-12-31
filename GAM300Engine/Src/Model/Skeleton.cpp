#include "Model/Skeleton.h"

namespace TDS
{
	Skeleton::Skeleton() {}
	Skeleton::Skeleton(const Pose& rest, const Pose& bind, const std::vector<std::string>& names)
	{
		Set(rest, bind, names);
	}
	
	void Skeleton::Set(const Pose& rest, const Pose& bind, const std::vector<std::string>& names)
	{
		mRestPose = rest;
		mBindPose = bind;
		mJointNames = names;
		UpdateInverseBindPose();
	}

	void Skeleton::UpdateInverseBindPose()
	{
		unsigned int size = mBindPose.Size();
		mInvBindPose.resize(size);

		for (unsigned int i = 0; i < size; ++i)
		{
			ModelTransform world = mBindPose.GetGlobalTransform(i);
			mInvBindPose[i] = TransformToMat4(world).inverse();
		}
	}

	Pose& Skeleton::GetBindPose() {
		return mBindPose;
	}

	Pose& Skeleton::GetRestPose() {
		return mRestPose;
	}

	std::vector<Mat4>& Skeleton::GetInvBindPose() {
		return mInvBindPose;
	}

	std::vector<std::string>& Skeleton::GetJointNames() {
		return mJointNames;
	}

	std::string& Skeleton::GetJointName(unsigned int idx) {
		return mJointNames[idx];
	}


	
} // namespace TDS
