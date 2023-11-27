#ifndef EVENTHANDLER
#define EVENTHANDLER

#include "components/nameTag.h"
#include "components/transform.h"
#include "eventManager/eventmanager.h"

namespace TDS
{
	class EventHandler
	{
	public:
		// To change child transformation when parent moves
		static void childTransformationHandlerInit();
		static void childTransformationHandlerUpdate(const float dt, const std::vector<EntityID>& entities, Transform* transform);
		static void changeChildTransformation(EntityID childEntity, Vec3& positionChange, Vec3& scaleChange, Vec3& rotationChange);
		DLL_API static void postChildTransformationEvent(EntityID entityID, Vec3 oldPosition, Vec3 oldScale, Vec3 oldRotation);

		// To change child transformation when parent moves
		static void childEnableHandlerInit();
		static void childEnableHandlerUpdate(const float dt, const std::vector<EntityID>& entities, NameTag* nameTag);
		static void changeChildEnable(EntityID childEntity, bool enabled);
		//DLL_API static void postChildEnableEvent(EntityID entityID);
	};
}

#endif