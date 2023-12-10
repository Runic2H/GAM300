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
	
	
	/*
	using namespace std;
	class MyContactListener : public ContactListener
	{
	public:
		// See: ContactListener
		virtual ValidateResult	OnContactValidate(const Body& inBody1, const Body& inBody2, RVec3Arg inBaseOffset, const CollideShapeResult& inCollisionResult) override
		{
			// Expect body 1 to be dynamic (or one of the bodies must be a sensor)
			if (!inBody1.IsDynamic() && !inBody1.IsSensor() && !inBody2.IsSensor())
				JPH_BREAKPOINT;

			ValidateResult result;
			if (mNext != nullptr)
				result = mNext->OnContactValidate(inBody1, inBody2, inBaseOffset, inCollisionResult);
			else
				result = ContactListener::OnContactValidate(inBody1, inBody2, inBaseOffset, inCollisionResult);

			Trace("Validate %u and %u result %d", inBody1.GetID().GetIndex(), inBody2.GetID().GetIndex(), (int)result);

			return result;
		}

		virtual void			OnContactAdded(const Body& inBody1, const Body& inBody2, const ContactManifold& inManifold, ContactSettings& ioSettings) override
		{
			cout << "A contact was added" << endl;
		}

		virtual void			OnContactPersisted(const Body& inBody1, const Body& inBody2, const ContactManifold& inManifold, ContactSettings& ioSettings) override
		{
			cout << "A contact was persisted" << endl;
		}

		virtual void			OnContactRemoved(const SubShapeIDPair& inSubShapePair) override
		{
			cout << "A contact was removed" << endl;
		}

	private:
		// Map that keeps track of the current state of contacts based on the contact listener callbacks
		using StatePair = pair<RVec3, ContactPoints>;
		using StateMap = UnorderedMap<SubShapeIDPair, StatePair>;
		Mutex					mStateMutex;
		StateMap				mState;

		ContactListener* mNext = nullptr;
	};
	*/
}

#endif // !CONTACTLISTENERIMPL_H

