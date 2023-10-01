#ifndef RIGIDBODYCOMPONENT
#define RIGIDBODYCOMPONENT

#include "Vector3.h"
#include "ecs/ecs.h"

namespace TDS
{
	class DLL_API RigidBody : public IComponent
	{
	public:
		RigidBody();
		RigidBody(RigidBody&& toMove) noexcept;
		~RigidBody() = default;
		virtual bool Deserialize(const rapidjson::Value& obj);
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;

		Vec3& GetAcceleration() { return mAcceleration; }
		void SetAcceleration(Vec3 acceleration) { mAcceleration = acceleration; }

		Vec3& GetLinearVel() { return mLinearVelocity; }
		void SetLinearVel(Vec3 velocity) { mLinearVelocity = velocity; }
		void SetLinearVel(float velocityX, float velocityY, float velocityZ) { mLinearVelocity = Vec3(velocityX, velocityY, velocityZ); }
		
		Vec3& GetAngularVel() { return mAngularVelocity; }
		void SetAngularVel(Vec3 velocity) { mAngularVelocity = velocity; }
		void SetAngularVel(float velocityX, float velocityY, float velocityZ) { mAngularVelocity = Vec3(velocityX, velocityY, velocityZ); }

		Vec3& GetInputForce() { return mInputForce; }
		void SetInputForce(Vec3 inputForce) { mInputForce = inputForce; }
		void SetInputForce(float inputForceX, float inputForceY, float inputForceZ) { mInputForce = Vec3(inputForceX, inputForceY, inputForceZ); }

		Vec3& GetNormalizedForce() { return mNormalizedForce; }
		void SetNormalizedForce(Vec3 normalizedForce) { mNormalizedForce = normalizedForce; }
		void SetNormalizedForce(float normalizedForceX, float normalizedForceY, float normalizedForceZ) { mNormalizedForce = Vec3(normalizedForceX, normalizedForceY, normalizedForceZ); }

		Vec3& GetDirection() { return mDirection; }
		void SetDirection(Vec3 direction) { mDirection = direction; }
		void SetDirection(float directionX, float directionY, float directionZ) { mDirection = Vec3(directionX, directionY, directionZ); }

		Vec3& GetNextPosition() { return mNextPosition; }
		void SetNextPosition(Vec3 nextPosition) { mNextPosition = nextPosition; }
		
		float& GetFriction() { return mFriction; }
		void SetFrictionCoefficient(float friction) { mFriction = friction; }

		float& GetRestitution() { return mRestitution; }
		void SetRestitution(float restitution) { mRestitution = restitution; }

		float& GetMass() { return mMass; }
		void SetMass(float mass) { mMass = mass; }
		
		float& GetInverseMass() { return mInverseMass; }
		void setInverseMass(float mass) { mInverseMass = 1.0f / mass; }

		float& GetGravity() { return mGravity; }
		void SetGravity(float gravity) { mGravity = gravity; }
		

	private:
		Vec3 mAcceleration;
		Vec3 mLinearVelocity;
		Vec3 mAngularVelocity;
		Vec3 mDirection;
		Vec3 mNextPosition;
		Vec3 mInputForce;
		Vec3 mNormalizedForce;
		Vec3 mTotalForce;
		
		float mFriction;
		float mRestitution;
		float mMass;
		float mInverseMass;
		float mGravity;
	};

}

#endif //RIGIDBODYCOMPONENT