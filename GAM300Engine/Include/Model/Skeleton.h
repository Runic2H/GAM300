#ifndef SKELETON_H
#define SKELETON_H

#include <vector>
#include "TDSMath.h"
#include "Animation/Pose.h"
#include "dotnet/ImportExport.h"

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
		DLL_API Skeleton();
		DLL_API Skeleton(const Pose& rest, const Pose& bind, const std::vector<std::string>& names);

		DLL_API void Set(const Pose& rest, const Pose& bind, const std::vector<std::string>& names);

		DLL_API Pose& GetBindPose();
		DLL_API Pose& GetRestPose();
		DLL_API std::vector<Mat4>& GetInvBindPose();
		DLL_API std::vector<std::string>& GetJointNames();
		DLL_API std::string& GetJointName(unsigned int index);

	};

}



#endif // !SKELETON_H
