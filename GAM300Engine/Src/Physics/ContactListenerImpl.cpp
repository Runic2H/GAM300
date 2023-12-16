#include <Jolt/Physics/Body/Body.h>
#include <Jolt/Physics/Collision/CollideShape.h>
#include <Jolt/Core/QuickSort.h>

#include "Physics/ContactListenerImpl.h"
#include "Physics/PhysicsSystem.h"

namespace TDS
{
	ValidateResult MyContactListener::OnContactValidate(const Body& inBody1, const Body& inBody2, RVec3Arg inBaseOffset, const CollideShapeResult& inCollisionResult)
	{
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
	void MyContactListener::OnContactAdded(const Body& inBody1, const Body& inBody2, const ContactManifold& inManifold, ContactSettings& ioSettings)
	{
		// Expect bodies to be sorted
		if (!(inBody1.GetID() < inBody2.GetID()))
			JPH_BREAKPOINT;

		Trace("Contact added %u (%08x) and %u (%08x)", inBody1.GetID().GetIndex(), inManifold.mSubShapeID1.GetValue(), inBody2.GetID().GetIndex(), inManifold.mSubShapeID2.GetValue());
		if (inBody1.IsSensor())
		{
			//Trace("inbody1 1: %u", inBody1.GetID().GetIndex());
			//Trace("inbody1 2: %u", inBody2.GetID().GetIndex());
			auto sensorID = PhysicsSystem::findEntityByID(inBody1.GetID().GetIndex());
			if (sensorID.has_value())
			{
				GetRigidBody(sensorID.value())->setSensorActivate(true);
			}
		}
		else if (inBody2.IsSensor())
		{
			//Trace("inBody2 1: %u", inBody1.GetID().GetIndex());
			//Trace("inBody2 2: %u", inBody2.GetID().GetIndex());
			auto sensorID = PhysicsSystem::findEntityByID(inBody2.GetID().GetIndex());
			if (sensorID.has_value())
			{
				GetRigidBody(sensorID.value())->setSensorActivate(true);
			}
		}
		// Insert new manifold into state map
		{
			lock_guard lock(mStateMutex);
			SubShapeIDPair key(inBody1.GetID(), inManifold.mSubShapeID1, inBody2.GetID(), inManifold.mSubShapeID2);
			if (mState.find(key) != mState.end())
				JPH_BREAKPOINT; // Added contact that already existed
			mState[key] = StatePair(inManifold.mBaseOffset, inManifold.mRelativeContactPointsOn1);
		}

		if (mNext != nullptr)
			mNext->OnContactAdded(inBody1, inBody2, inManifold, ioSettings);
	}
	void MyContactListener::OnContactPersisted(const Body& inBody1, const Body& inBody2, const ContactManifold& inManifold, ContactSettings& ioSettings)
	{
		// Expect bodies to be sorted
		if (!(inBody1.GetID() < inBody2.GetID()))
			JPH_BREAKPOINT;

		Trace("Contact persisted %u (%08x) and %u (%08x)", inBody1.GetID().GetIndex(), inManifold.mSubShapeID1.GetValue(), inBody2.GetID().GetIndex(), inManifold.mSubShapeID2.GetValue());

		// Update existing manifold in state map
		{
			lock_guard lock(mStateMutex);
			SubShapeIDPair key(inBody1.GetID(), inManifold.mSubShapeID1, inBody2.GetID(), inManifold.mSubShapeID2);
			StateMap::iterator i = mState.find(key);
			if (i != mState.end())
				i->second = StatePair(inManifold.mBaseOffset, inManifold.mRelativeContactPointsOn1);
			else
				JPH_BREAKPOINT; // Persisted contact that didn't exist
		}

		if (mNext != nullptr)
			mNext->OnContactPersisted(inBody1, inBody2, inManifold, ioSettings);
	}
	void MyContactListener::OnContactRemoved(const SubShapeIDPair& inSubShapePair)
	{
		// Expect bodies to be sorted
		if (!(inSubShapePair.GetBody1ID() < inSubShapePair.GetBody2ID()))
			JPH_BREAKPOINT;

		Trace("Contact removed %u (%08x) and %u (%08x)", inSubShapePair.GetBody1ID().GetIndex(), inSubShapePair.GetSubShapeID1().GetValue(), inSubShapePair.GetBody2ID().GetIndex(), inSubShapePair.GetSubShapeID2().GetValue());
		auto sensorID1 = PhysicsSystem::findEntityByID(inSubShapePair.GetBody1ID().GetIndex());
		auto sensorID2 = PhysicsSystem::findEntityByID(inSubShapePair.GetBody2ID().GetIndex());
		if (sensorID1.has_value())
		{
			//std::cout << "1sensorID1: " << sensorID1.value() << std::endl;
			//std::cout << "1sensorID2: " << sensorID2.value() << std::endl;
			GetRigidBody(sensorID1.value())->setSensorActivate(false);
			GetRigidBody(sensorID2.value())->setSensorActivate(false);
		}
		else if (sensorID2.has_value())
		{
			//std::cout << "2sensorID1: " << sensorID1.value() << std::endl;
			//std::cout << "2sensorID2: " << sensorID2.value() << std::endl;
			GetRigidBody(sensorID1.value())->setSensorActivate(false);
			GetRigidBody(sensorID2.value())->setSensorActivate(false);
		}
		// Update existing manifold in state map
		{
			lock_guard lock(mStateMutex);
			StateMap::iterator i = mState.find(inSubShapePair);
			if (i != mState.end())
				mState.erase(i);
			else
				JPH_BREAKPOINT; // Removed contact that didn't exist
		}

		if (mNext != nullptr)
			mNext->OnContactRemoved(inSubShapePair);

	}
}