#ifndef POSE_H
#define POSE_H

#include "Model/ModelTransform.h"
#include "dotnet/ImportExport.h"

namespace TDS
{
	class DLL_API Pose
	{
	protected:
		std::vector<ModelTransform> mJoints;
		std::vector<int> mParents;

	public:
		Pose();
		Pose(const Pose& p);
		Pose& operator=(const Pose& p);
		Pose(unsigned int numJoints);
		void Resize(unsigned int size);
		unsigned int Size();
		ModelTransform GetLocalTransform(unsigned int index);
		void SetLocalTransform(unsigned int index, const ModelTransform& t);
		ModelTransform GetGlobalTransform(unsigned int index);
		ModelTransform operator[](unsigned int index);
		void GetMatrixPalette(std::vector<Mat4>& out);
		int GetParent(unsigned int index);
		void SetParent(unsigned int index, int parent);

		bool operator==(const Pose& other);
		bool operator!=(const Pose& other);
	};


} // namespace TDS



#endif // !POSE_H
