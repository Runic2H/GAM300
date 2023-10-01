#ifndef COLLIDERCOMPONENT
#define COLLIDERCOMPONENT

#include "Vector3.h"
#include "ecs/ecs.h"

namespace TDS
{
	class DLL_API Collider : public IComponent
	{
	public:
		/*!*************************************************************************
		This is the list of collider types. Collider type also informs response behavior
		****************************************************************************/
		enum class ColliderType
		{
			NONE,
			CIRCLE,			// Circle
			RECTANGLE		// AABB
		};

		Collider();
		Collider(Collider&& toMove) noexcept;
		~Collider() = default;
		virtual bool Deserialize(const rapidjson::Value& obj);
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;

		ColliderType& GetColliderType() { return mColliderType; }
		void SetColliderType(ColliderType colliderType) { mColliderType = colliderType; }

		Vec3& GetColliderNormal() { return mCollisionNormal; }
		void SetColliderNormal(Vec3 collisionNormal) { mCollisionNormal = collisionNormal; }

		Vec3& GetMin() { return mMin; }
		void SetMin(Vec3 min) { mMin = min; }

		Vec3& GetMax() { return mMax; }
		void SetMax(Vec3 max) { mMax = max; }

		Vec3& GetOffset() { return mOffset; }
		void SetOffset(Vec3 offset) { mOffset = offset; }

		int& GetHit() { return mHit; }
		void SetHit(int hit) { mHit = hit; }

		float& GetRadius() { return mRadius; }
		void SetRadius(float radius) { mRadius = radius; }

		bool& GetAlive() { return mIsAlive; }
		void SetAlive(bool isAlive) { mIsAlive = isAlive; }

		bool& GetCollision() { return mCollision; }
		void SetCollision(bool collision) { mCollision = collision; }

	private:
		ColliderType mColliderType;
		Vec3 mCollisionNormal;
		Vec3 mMin;
		Vec3 mMax;
		Vec3 mOffset;
		int mHit;
		
		float mRadius;
		
		bool mIsAlive;
		bool mCollision;
	};
}

#endif // COLLIDERCOMPONENT