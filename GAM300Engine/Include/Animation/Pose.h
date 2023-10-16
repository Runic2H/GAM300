#ifndef POSE_H
#define POSE_H

#include "Model/ModelTransform.h"
#include "dotnet/ImportExport.h"

namespace TDS
{
	class Pose
	{
	protected:
		std::vector<ModelTransform> mJoints;
		std::vector<int> mParents;

	public:
		DLL_API Pose();
		DLL_API Pose(const Pose& p);
		DLL_API Pose& operator=(const Pose& p);
		DLL_API Pose(unsigned int numJoints);
		DLL_API void Resize(unsigned int size);
		DLL_API unsigned int Size();
		DLL_API ModelTransform GetLocalTransform(unsigned int index);
		DLL_API void SetLocalTransform(unsigned int index, const ModelTransform& t);
		DLL_API ModelTransform GetGlobalTransform(unsigned int index);
		DLL_API ModelTransform operator[](unsigned int index);
		DLL_API void GetMatrixPalette(std::vector<Mat4>& out);
		DLL_API int GetParent(unsigned int index);
		DLL_API void SetParent(unsigned int index, int parent);

		DLL_API bool operator==(const Pose& other);
		DLL_API bool operator!=(const Pose& other);
	};


} // namespace TDS



#endif // !POSE_H
