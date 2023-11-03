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

	inline JPH::Float3 ToFloat3(const Vec3& v) { return JPH::Float3(v.x, v.y, v.z); }
	
	inline Quat ToQuat(const JPH::Quat& q) { return Quat(q.GetX(), q.GetY(), q.GetZ(), q.GetW()); }
	
	inline JPH::Quat ToQuat(const Quat& q) { return JPH::Quat(q.x, q.y, q.z, q.w); }

	inline JPH::EMotionType ToEMotionType(const RigidBody::MotionType& e)
	{
		switch (e)
		{
		case RigidBody::MotionType::STATIC:
			return JPH::EMotionType::Static;
		case RigidBody::MotionType::DYNAMIC:
			return JPH::EMotionType::Dynamic;
		case RigidBody::MotionType::KINEMATIC:
			return JPH::EMotionType::Kinematic;
		default:
			return JPH::EMotionType::Static;
		}
	}

	inline JPH::BodyID ToBodyID(RigidBody* body)
	{
		return JPH::BodyID(body->GetBodyID().GetIndexAndSequenceNumber());
	}

	inline JPH::BodyID* ToBodyID(JoltBodyID* bodyID)
	{
		return reinterpret_cast<JPH::BodyID*>(bodyID);
	}

}




#endif // !JOLTCONVERSIONUTILS_H
