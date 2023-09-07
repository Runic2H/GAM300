#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "TDSMath.h"

namespace TDS
{
	struct Transform
	{
		Vec3 pos;
		Quat rot;
		Vec3 scale;
		Transform() :
			pos(Vec3(0.f, 0.f, 0.f)),
			rot(Quat(0.f, 0.f, 0.f, 1.f)),
			scale(Vec3(1.f, 1.f, 1.f)) {}
		Transform(const Vec3& p, const Quat& r, const Vec3& s) :
			pos(p), rot(r), scale(s) {}
	};
	
	Transform Combine(const Transform& a, const Transform& b);
	Transform Inverse(const Transform& t);
	Transform Mix(const Transform& a, const Transform& b, float t);
	
	bool operator==(const Transform& a, const Transform& b);
	bool operator!=(const Transform& a, const Transform& b);
	
	Mat4 TransformToMat4(const Transform& t);
	Transform Mat4ToTransform(const Mat4& m);
	Vec3 TransformPoint(const Transform& a, const Vec3& b);
	Vec3 TransformVector(const Transform& a, const Vec3& b);
	
}



#endif // TRANSFORM_H
