#ifndef SKELETON_H
#define SKELETON_H

#include "Animation/Pose.h"
#include "TDSMath.h"


namespace TDS
{
class Skeleton
{
protected:
	Pose mRestPose;
	Pose mBindPose;
	std::vector<Mat4> mInvBindPose;
	std::vector<std::string> mJointNames;

	void UpdateInverseBindPose();

public:
	Skeleton();
	Skeleton(const Pose& rest, const Pose& bind, const std::vector<std::string>& names);
	
	void Set(const Pose& rest, const Pose& bind, const std::vector<std::string>& names);
	
	Pose& GetBindPose();
	Pose& GetRestPose();
	std::vector<Mat4>& GetInvBindPose();
	std::vector<std::string>& GetJointNames();
	std::string& GetJointName(unsigned int index);
	
};
	
}



#endif // !SKELETON_H
