#ifndef RIGIDBODYCOMPONENT
#define RIGIDBODYCOMPONENT

#include "Vector2.h"
#include "ecs/ecs.h"

namespace TDS
{
	class RigidBody : public IComponent
	{
	public:
		RigidBody();
		~RigidBody() = default;
		virtual bool Deserialize(const rapidjson::Value& obj);
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;

		virtual void ImGuiDisplay();

		Vec2& GetAcceleration() { return mAcceleration; }
		void SetAcceleration(Vec2 acceleration) { mAcceleration = acceleration; }

		Vec2& GetVel() { return mVelocity; }
		void SetVel(Vec2 velocity) { mVelocity = velocity; }
		void SetVel(float velocityX, float velocityY) { mVelocity = Vec2(velocityX, velocityY); }

		Vec2& GetDirection() { return mDirection; }
		void SetDirection(Vec2 direction) { mDirection = direction; }
		void SetDirection(float directionX, float directionY) { mDirection = Vec2(directionX, directionY); }

		Vec2& GetNextPosition() { return mNextPosition; }
		void SetNextPosition(Vec2 nextPosition) { mNextPosition = nextPosition; }

		float& GetFriction() { return mFriction; }
		void SetFriction(float friction) { mFriction = friction; }

		float& GetRestitution() { return mRestitution; }
		void SetRestitution(float restitution) { mRestitution = restitution; }

	private:
		Vec2 mAcceleration;
		Vec2 mVelocity;
		Vec2 mDirection;
		Vec2 mNextPosition;
		float mFriction;
		float mRestitution;
	};

}

#endif //RIGIDBODYCOMPONENT