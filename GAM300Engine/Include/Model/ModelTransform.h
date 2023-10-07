#ifndef MODELTRANSFORM_H
#define MODELTRANSFORM_H

#include "TDSMath.h"
#include "dotnet/ImportExport.h"

namespace TDS
{
	struct ModelTransform
	{
		Vec3 pos;
		Quat rot;
		Vec3 scale;
		DLL_API ModelTransform() :
			pos(Vec3(0.f, 0.f, 0.f)),
			rot(Quat(0.f, 0.f, 0.f, 1.f)),
			scale(Vec3(1.f, 1.f, 1.f)) {}
		DLL_API ModelTransform(const Vec3& p, const Quat& r, const Vec3& s) :
			pos(p), rot(r), scale(s) {}
	};

	DLL_API ModelTransform Combine(const ModelTransform& a, const ModelTransform& b);
	DLL_API ModelTransform Inverse(const ModelTransform& t);
	DLL_API ModelTransform Mix(const ModelTransform& a, const ModelTransform& b, float t);

	DLL_API bool operator==(const ModelTransform& a, const ModelTransform& b);
	DLL_API bool operator!=(const ModelTransform& a, const ModelTransform& b);

	DLL_API Mat4 TransformToMat4(const ModelTransform& t);
	DLL_API ModelTransform Mat4ToTransform(const Mat4& m);
	DLL_API Vec3 TransformPoint(const ModelTransform& a, const Vec3& b);
	DLL_API Vec3 TransformVector(const ModelTransform& a, const Vec3& b);

}



#endif // MODELTRANSFORM_H
