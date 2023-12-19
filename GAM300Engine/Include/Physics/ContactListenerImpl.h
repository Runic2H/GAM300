#ifndef CONTACTLISTENERIMPL_H
#define CONTACTLISTENERIMPL_H

#include <Jolt/Physics/Collision/ContactListener.h>
#include <Jolt/Physics/StateRecorder.h>
#include <Jolt/Core/Mutex.h>
#include <Jolt/Core/UnorderedMap.h>

namespace TDS
{
	using namespace JPH;
	using namespace JPH::literals;

	// An example contact listener
	
	class MyContactListener : public ContactListener
	{
	public:
		virtual ValidateResult	OnContactValidate(const Body& inBody1, const Body& inBody2, RVec3Arg inBaseOffset, const CollideShapeResult& inCollisionResult) override;
		virtual void			OnContactAdded(const Body& inBody1, const Body& inBody2, const ContactManifold& inManifold, ContactSettings& ioSettings) override;
		virtual void			OnContactPersisted(const Body& inBody1, const Body& inBody2, const ContactManifold& inManifold, ContactSettings& ioSettings) override;
		virtual void			OnContactRemoved(const SubShapeIDPair& inSubShapePair) override;

	private:
		using StatePair = pair<RVec3, ContactPoints>;
		using StateMap = UnorderedMap<SubShapeIDPair, StatePair>;

		Mutex					mStateMutex;
		StateMap				mState;

		ContactListener* mNext = nullptr;
	};
	
}

#endif // !CONTACTLISTENERIMPL_H

