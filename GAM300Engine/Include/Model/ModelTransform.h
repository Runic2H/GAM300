#ifndef MODELTRANSFORM_H
#define MODELTRANSFORM_H

#include "TDSMath.h"
#include "dotnet/ImportExport.h"

namespace TDS
{
	struct DLL_API ModelTransform
	{
		Vec3 pos;
		Quat rot;
		Vec3 scale;
		ModelTransform() :
			pos(Vec3(0.f, 0.f, 0.f)),
			rot(Quat(0.f, 0.f, 0.f, 1.f)),
			scale(Vec3(1.f, 1.f, 1.f)) {}
		ModelTransform(const Vec3& p, const Quat& r, const Vec3& s) :
			pos(p), rot(r), scale(s) {}
	};

	ModelTransform Combine(const ModelTransform& a, const ModelTransform& b);
	ModelTransform Inverse(const ModelTransform& t);
	ModelTransform Mix(const ModelTransform& a, const ModelTransform& b, float t);

	bool operator==(const ModelTransform& a, const ModelTransform& b);
	bool operator!=(const ModelTransform& a, const ModelTransform& b);

	Mat4 TransformToMat4(const ModelTransform& t);
	ModelTransform Mat4ToTransform(const Mat4& m);
	Vec3 TransformPoint(const ModelTransform& a, const Vec3& b);
	Vec3 TransformVector(const ModelTransform& a, const Vec3& b);

}



#endif // MODELTRANSFORM_H
