#ifndef COLLIDERCOMPONENT
#define COLLIDERCOMPONENT

#include "Vector2.h"
#include "ecs/ecs.h"

namespace TDS
{
	class Collider : public IComponent
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
		~Collider() = default;
		virtual bool Deserialize(const rapidjson::Value& obj);
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;

		virtual void ImGuiDisplay();

		ColliderType& GetColliderType() { return mColliderType; }
		void SetColliderType(ColliderType colliderType) { mColliderType = colliderType; }

		Vec2& GetColliderNormal() { return mCollisionNormal; }
		void SetColliderNormal(Vec2 collisionNormal) { mCollisionNormal = collisionNormal; }

		Vec2& GetMin() { return mMin; }
		void SetMin(Vec2 min) { mMin = min; }

		Vec2& GetMax() { return mMax; }
		void SetMax(Vec2 max) { mMax = max; }

		Vec2& GetOffset() { return mOffset; }
		void SetOffset(Vec2 offset) { mOffset = offset; }

		int& GetHit() { return mHit; }
		void SetHit(int hit) { mHit = hit; }

		float& GetRadius() { return mRadius; }
		void SetRadius(float radius) { mRadius = radius; }

		bool& GetAlive() { return mIsAlive; }
		void SetAlive(bool isAlive) { mIsAlive = isAlive; }

	private:
		ColliderType mColliderType;
		Vec2 mCollisionNormal;
		Vec2 mMin;
		Vec2 mMax;
		Vec2 mOffset;
		int mHit;
		float mRadius;
		bool mIsAlive;
	};
}

#endif // COLLIDERCOMPONENT