#include "Model/ModelTransform.h"
namespace TDS
{
	ModelTransform Combine(const ModelTransform& a, const ModelTransform& b)
	{
		ModelTransform out;
		
		out.scale = a.scale * b.scale;
		out.rot = a.rot * b.rot;
		
		out.pos = a.rot * (a.scale * b.pos);
		out.pos = a.pos + out.pos;

		return out;
	}

	ModelTransform Inverse(const ModelTransform& t)
	{
		ModelTransform inv;
		
		inv.rot = Quat::inverse(inv.rot);

		inv.scale.x = Mathf::Abs(t.scale.x) < Mathf::Epsilon ? 0.0f : 1.0f / t.scale.x;
		inv.scale.y = Mathf::Abs(t.scale.y) < Mathf::Epsilon ? 0.0f : 1.0f / t.scale.y;
		inv.scale.z = Mathf::Abs(t.scale.z) < Mathf::Epsilon ? 0.0f : 1.0f / t.scale.z;
	
		Vec3 invTranslation = t.pos * -1.0f;
		inv.pos = inv.rot * (inv.scale * invTranslation);

		return inv;
	}

	ModelTransform Mix(const ModelTransform& a, const ModelTransform& b, float t)
	{
		Quat bRot = b.rot;
		if (Quat::dot(a.rot, bRot) < 0.0f)
		{
			bRot = -bRot;
		}
		return ModelTransform(
			Vec3::LerpUnclamped(a.pos, b.pos, t),
			Quat::nlerp(a.rot, bRot, t),
			Vec3::LerpUnclamped(a.pos, b.pos, t));
	}

	bool operator==(const ModelTransform& a, const ModelTransform& b)
	{
		return a.pos == b.pos &&
			a.rot == b.rot &&
			a.scale == b.scale;
	}

	bool operator!=(const ModelTransform& a, const ModelTransform& b)
	{
		return !(a == b);
	}

	Mat4 TransformToMat4(const ModelTransform& t)
	{
		Vec3 x = t.rot * Vec3(1, 0, 0);
		Vec3 y = t.rot * Vec3(0, 1, 0);
		Vec3 z = t.rot * Vec3(0, 0, 1);
		
		x *= t.scale.x;
		y *= t.scale.y;
		z *= t.scale.z;

		Vec3 p = t.pos;

		return Mat4(
			x.x, x.y, x.z, 0, // X basis (& Scale)
			y.x, y.y, y.z, 0, // Y basis (& scale)
			z.x, z.y, z.z, 0, // Z basis (& scale)
			p.x, p.y, p.z, 1  // Position
		);
	}

	ModelTransform Mat4ToTransform(const Mat4& mat)
	{
		ModelTransform out;
		out.pos = Vec3(mat[12], mat[13], mat[14]);
		out.rot - Mat4::toQuat(mat);
		
		Mat4 rotScaleMat(
			mat[0], mat[1], mat[2], 0,
			mat[4], mat[5], mat[6], 0,
			mat[8], mat[9], mat[10], 0,
			0, 0, 0, 1
		);

		Mat4 invRotMat = Quat::toMat4(Quat::inverse(out.rot));
		Mat4 scaleSkewMat = rotScaleMat * invRotMat;

		out.scale = Vec3(
			scaleSkewMat[0],
			scaleSkewMat[5],
			scaleSkewMat[10]
		);
		
		return out;
	}

	Vec3 TransformPoint(const ModelTransform& a, const Vec3& b)
	{
		Vec3 out;
		
		out = a.rot * (a.scale * b);
		out = a.pos + out;
		
		return out;
	}

	Vec3 TransformVector(const ModelTransform& a, const Vec3& b)
	{
		Vec3 out;

		out = a.rot * (a.scale * b);

		return out;
	}

} // namespace TDS
