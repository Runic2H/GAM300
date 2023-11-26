#ifndef JPHLAYERS_H
#define JPHLAYERS_H

#include <Jolt/Physics/Collision/ObjectLayer.h>
#include <Jolt/Physics/Collision/BroadPhase/BroadPhaseLayer.h>
#include <Jolt/Physics/Body/BodyActivationListener.h>
#include <Jolt/Physics/Collision/ContactListener.h>
#include <Jolt/Physics/Body/Body.h>

namespace TDS
{
	// All Jolt symbols are in the JPH namespace
	using namespace JPH;
	using namespace JPH::literals;

	namespace Layers
	{
		static constexpr ObjectLayer NON_MOVING = 0;
		static constexpr ObjectLayer MOVING = 1;
		static constexpr ObjectLayer NUM_LAYERS = 2;
	};

	/// Class that determines if two object layers can collide
	class ObjectLayerPairFilterImpl : public ObjectLayerPairFilter
	{
	public:
		virtual bool					ShouldCollide(ObjectLayer inObject1, ObjectLayer inObject2) const override
		{
			switch (inObject1)
			{
			case Layers::NON_MOVING:
				return inObject2 == Layers::MOVING; // Non moving only collides with moving
			case Layers::MOVING:
				return true; // Moving collides with everything
			default:
				JPH_ASSERT(false);
				return false;
			}
		}
	};

	// Each broadphase layer results in a separate bounding volume tree in the broad phase. You at least want to have
	// a layer for non-moving and moving objects to avoid having to update a tree full of static objects every frame.
	// You can have a 1-on-1 mapping between object layers and broadphase layers (like in this case) but if you have
	// many object layers you'll be creating many broad phase trees, which is not efficient. If you want to fine tune
	// your broadphase layers define JPH_TRACK_BROADPHASE_STATS and look at the stats reported on the TTY.
	namespace BroadPhaseLayers
	{
		static constexpr BroadPhaseLayer NON_MOVING(0);
		static constexpr BroadPhaseLayer MOVING(1);
		static constexpr uint NUM_LAYERS(2);
	};

	// BroadPhaseLayerInterface implementation
	// This defines a mapping between object and broadphase layers.
	class BPLayerInterfaceImpl final : public BroadPhaseLayerInterface
	{
	public:
		BPLayerInterfaceImpl()
		{
			// Create a mapping table from object to broad phase layer
			mObjectToBroadPhase[Layers::NON_MOVING] = BroadPhaseLayers::NON_MOVING;
			mObjectToBroadPhase[Layers::MOVING] = BroadPhaseLayers::MOVING;
		}

		virtual uint					GetNumBroadPhaseLayers() const override
		{
			return BroadPhaseLayers::NUM_LAYERS;
		}

		virtual BroadPhaseLayer			GetBroadPhaseLayer(ObjectLayer inLayer) const override
		{
			JPH_ASSERT(inLayer < Layers::NUM_LAYERS);
			return mObjectToBroadPhase[inLayer];
		}

#if defined(JPH_EXTERNAL_PROFILE) || defined(JPH_PROFILE_ENABLED)
		virtual const char* GetBroadPhaseLayerName(BroadPhaseLayer inLayer) const override
		{
			switch ((BroadPhaseLayer::Type)inLayer)
			{
			case (BroadPhaseLayer::Type)BroadPhaseLayers::NON_MOVING:	return "NON_MOVING";
			case (BroadPhaseLayer::Type)BroadPhaseLayers::MOVING:		return "MOVING";
			default:													JPH_ASSERT(false); return "INVALID";
			}
		}
#endif // JPH_EXTERNAL_PROFILE || JPH_PROFILE_ENABLED

	private:
		BroadPhaseLayer					mObjectToBroadPhase[Layers::NUM_LAYERS];
	};

	/// Class that determines if an object layer can collide with a broadphase layer
	class ObjectVsBroadPhaseLayerFilterImpl : public ObjectVsBroadPhaseLayerFilter
	{
	public:
		virtual bool				ShouldCollide(ObjectLayer inLayer1, BroadPhaseLayer inLayer2) const override
		{
			switch (inLayer1)
			{
			case Layers::NON_MOVING:
				return inLayer2 == BroadPhaseLayers::MOVING;
			case Layers::MOVING:
				return true;
			default:
				JPH_ASSERT(false);
				return false;
			}
		}
	};

	// An example contact listener
	class MyContactListener : public ContactListener
	{
	public:
		// See: ContactListener
		ValidateResult GetLastResult() const { return lastResult; }
		bool GetSensorActivate() const { return sensorActivate; }
		uint32 getSensorBodyID() const { return sensorID; }
		virtual ValidateResult	OnContactValidate(const Body& inBody1, const Body& inBody2, RVec3Arg inBaseOffset, const CollideShapeResult& inCollisionResult) override
		{
			//// Expect body 1 to be dynamic (or one of the bodies must be a sensor)
			//if (!inBody1.IsDynamic() && !inBody1.IsSensor() && !inBody2.IsSensor())
			//{
			//	JPH_BREAKPOINT;		
			//}

			//ValidateResult result;
			//result = ContactListener::OnContactValidate(inBody1, inBody2, inBaseOffset, inCollisionResult);

			//Trace("Validate %u and %u result %d", inBody1.GetID().GetIndex(), inBody2.GetID().GetIndex(), (int)result);
			//lastResult = result;
			//return  result;
			//// Allows you to ignore a contact before it is created (using layers to not make objects collide is cheaper!)
			return ValidateResult::AcceptAllContactsForThisBodyPair;
		}

		virtual void			OnContactAdded(const Body& inBody1, const Body& inBody2, const ContactManifold& inManifold, ContactSettings& ioSettings) override
		{
			std::cout << "A contact was added" << std::endl;
		}

		virtual void			OnContactPersisted(const Body& inBody1, const Body& inBody2, const ContactManifold& inManifold, ContactSettings& ioSettings) override
		{
			if (inBody1.IsSensor() || inBody2.IsSensor())
			{
				sensorActivate = true;
				std::cout << "sensor activated" << '\n';
			}
			if (sensorActivate)
			{
				if (inBody1.IsSensor())
				{
					sensorID = inBody1.GetID().GetIndex();
				}
				else if (inBody2.IsSensor())
				{
					sensorID = inBody2.GetID().GetIndexAndSequenceNumber();
				}
			}

		}

		virtual void			OnContactRemoved(const SubShapeIDPair& inSubShapePair) override
		{
			if (sensorActivate)
			{
				sensorActivate = false;
			}
			std::cout << "A contact was removed" << std::endl;
		}
	private:
		ContactListener* mNext = nullptr;
		ValidateResult lastResult;
		bool sensorActivate;
		uint32 sensorID;
	};

	// An example activation listener
	class MyBodyActivationListener : public BodyActivationListener
	{
	public:
		virtual void		OnBodyActivated(const BodyID& inBodyID, uint64 inBodyUserData) override
		{
			//std::cout << "A body got activated" << std::endl;
		}

		virtual void		OnBodyDeactivated(const BodyID& inBodyID, uint64 inBodyUserData) override
		{
			//std::cout << "A body went to sleep" << std::endl;
		}
	};

	class JoltLayers
	{
	public:
		static ObjectLayer GetObjectLayer(int inLayer)
		{
			switch (inLayer)
			{
			case 0:
				return Layers::NON_MOVING;
			case 1:
			case 2:
				return Layers::MOVING;
			default:
				JPH_ASSERT(false);
				return Layers::NON_MOVING;
			}
		}
	};
}

#endif // !JPHLAYERS_H
