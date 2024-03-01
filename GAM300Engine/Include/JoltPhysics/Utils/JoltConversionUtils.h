#ifndef JOLTCONVERSIONUTILS_H
#define JOLTCONVERSIONUTILS_H

#include "components/rigidBody.h"

#include <Jolt/Core/Color.h>
#include <Jolt/Physics/Body/MotionType.h>
#include <Jolt/Physics/Body/BodyID.h>

#include "JoltPhysics/Implementation/Body/JoltBodyID.h"

namespace TDS::JoltToTDS
{
	inline Vec3 ToVec3(const JPH::Vec3& v) { return Vec3(v.GetX(), v.GetY(), v.GetZ()); }

	inline Vec3 ToVec3(const JPH::Float3& v) { return Vec3(v.x, v.y, v.z); }
	
	inline Color ToColor(const JPH::ColorArg& c)
	{
		const JPH::Vec4 v4 = c.ToVec4();
		return Color(v4.GetX(), v4.GetY(), v4.GetZ(), v4.GetW());
	}

	inline JPH::Vec3 ToVec3(const Vec3& v) { return JPH::Vec3(v.x, v.y, v.z); }

	inline Vec4 ToVec4(const JPH::Vec4& v) { return Vec4(v.GetX(), v.GetY(), v.GetZ(), v.GetW()); }

	inline JPH::Vec4 ToVec4(const Vec4& v) { return JPH::Vec4(v.x, v.y, v.z, v.w); }

	inline JPH::Float3 ToFloat3(const Vec3& v) { return JPH::Float3(v.x, v.y, v.z); }
	
	inline Quat ToQuat(const JPH::Quat& q) { return Quat(q.GetX(), q.GetY(), q.GetZ(), q.GetW()); }
	
	inline JPH::Quat ToQuat(const Quat& q) { return JPH::Quat(q.x, q.y, q.z, q.w); }

	//inline JPH::Quat ToQuat(const Vec3& q) { Quat tmp(q); return JPH::Quat(tmp.x, tmp.y, tmp.z, tmp.w); }

	inline Mat4 ToMat4(const JPH::Mat44& m)
	{
		Vec4 c0 = ToVec4(m.GetColumn4(0));
		Vec4 c1 = ToVec4(m.GetColumn4(1));
		Vec4 c2 = ToVec4(m.GetColumn4(2));
		Vec4 c3 = ToVec4(m.GetColumn4(3));
		return Mat4(c0, c1, c2, c3);
	}

	inline JPH::Mat44 ToMat44(const Mat4& m)
	{
		JPH::Mat44 result;
		Vec4 c0(m.m[0][0], m.m[0][1], m.m[0][2], m.m[0][3]);
		Vec4 c1(m.m[1][0], m.m[1][1], m.m[1][2], m.m[1][3]);
		Vec4 c2(m.m[2][0], m.m[2][1], m.m[2][2], m.m[2][3]);
		Vec4 c3(m.m[3][0], m.m[3][1], m.m[3][2], m.m[3][3]);
		
		result.SetColumn4(0, ToVec4(c0));
		result.SetColumn4(1, ToVec4(c1));
		result.SetColumn4(2, ToVec4(c2));
		result.SetColumn4(3, ToVec4(c3));

		return result;
	}

	inline JPH::EMotionType ToEMotionType(const RigidBody::MotionType& e)
	{
		switch (e)
		{
		case RigidBody::MotionType::STATIC:
			return JPH::EMotionType::Static;
		case RigidBody::MotionType::DYNAMIC:
			return JPH::EMotionType::Dynamic;
		default:
			return JPH::EMotionType::Static;
		}
	}

	inline JPH::BodyID ToBodyID(RigidBody& body)
	{
		return JPH::BodyID(body.GetBodyID().GetIndexAndSequenceNumber());
	}

	inline JPH::BodyID* ToBodyID(JoltBodyID* body)
	{
		return reinterpret_cast<JPH::BodyID*>(body);
	}

}




#endif // !JOLTCONVERSIONUTILS_H
