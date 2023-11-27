#include "eventManager/eventHandler.h"

namespace TDS
{
	EventManager eventManager;

	void EventHandler::childTransformationHandlerInit()
	{
		eventManager.subscribe(EventTypes::CHILD_TRANSFORMATION);
	}
	void EventHandler::childTransformationHandlerUpdate(const float dt, const std::vector<EntityID>& entities, Transform* transform)
	{
		auto theQueue = eventManager.findQueue(EventTypes::CHILD_TRANSFORMATION);

		for (auto event : theQueue)
		{
			NameTag* nameTagComponent = ecs.getComponent<NameTag>(event->id);
		
			std::shared_ptr<ChildTransformationEvent> currentEvent = static_pointer_cast<ChildTransformationEvent>(event);
			
			for (auto childID : nameTagComponent->GetHierarchyChildren())
			{
				changeChildTransformation(childID, currentEvent->positionChange, currentEvent->scaleChange, currentEvent->rotationChange);
			}
		}
		eventManager.clearQueue(EventTypes::CHILD_TRANSFORMATION);
	}
	void EventHandler::changeChildTransformation(EntityID childEntity, Vec3& positionChange, Vec3& scaleChange, Vec3& rotationChange)
	{
		Transform* childTransform = GetTransform(childEntity);
		childTransform->SetPosition(childTransform->GetPosition() + positionChange);
		childTransform->SetScale(childTransform->GetScale() + scaleChange);
		childTransform->SetRotation(childTransform->GetRotation() + rotationChange);

		NameTag* childNameTag = GetNameTag(childEntity);

		for (auto childID : childNameTag->GetHierarchyChildren())
		{
			changeChildTransformation(childID, positionChange, scaleChange, rotationChange);
		}
	}
	void EventHandler::postChildTransformationEvent(EntityID entityID, Vec3 oldPosition, Vec3 oldScale, Vec3 oldRotation)
	{
		Transform* transformComponent =  ecs.getComponent<Transform>(entityID);

		ChildTransformationEvent newEvent;
		newEvent.id = entityID;
		newEvent.positionChange = transformComponent->GetPosition() - oldPosition;
		newEvent.scaleChange = transformComponent->GetScale() - oldScale;
		newEvent.rotationChange = transformComponent->GetRotation() - oldRotation;

		if (newEvent.positionChange != Vec3::zero() || newEvent.scaleChange != Vec3::zero() || newEvent.rotationChange != Vec3::zero())
		{
			eventManager.post(newEvent, EventTypes::CHILD_TRANSFORMATION);
		}
	}


	void EventHandler::childEnableHandlerInit()
	{
		eventManager.subscribe(EventTypes::CHILD_TRANSFORMATION);
	}
	void EventHandler::childEnableHandlerUpdate(const float dt, const std::vector<EntityID>& entities, NameTag* nameTag)
	{
		for (EntityID entity : entities)
		{
			if (ecs.getEntityIsEnabled(entity) != ecs.getEntityPreviouslyEnabled(entity))
			{
				bool enabled = ecs.getEntityIsEnabled(entity);
				NameTag* nameTagComponent = ecs.getComponent<NameTag>(entity);

				for (auto childID : nameTagComponent->GetHierarchyChildren())
				{
					changeChildEnable(childID, enabled);
				}
				ecs.setEntityPreviouslyEnabled(entity);
			}
		}
	}
	void EventHandler::changeChildEnable(EntityID childEntity, bool enabled)
	{
		ecs.setEntityIsEnabled(childEntity, enabled);
		ecs.setEntityPreviouslyEnabled(childEntity);

		NameTag* childNameTag = GetNameTag(childEntity);

		for (auto childID : childNameTag->GetHierarchyChildren())
		{
			changeChildEnable(childID, enabled);
		}
	}
	//void EventHandler::postChildEnableEvent(EntityID entityID, Vec3 oldPosition, Vec3 oldScale, Vec3 oldRotation)
	//{
	//	Transform* transformComponent =  ecs.getComponent<Transform>(entityID);

	//	ChildTransformationEvent newEvent;
	//	newEvent.id = entityID;
	//	newEvent.positionChange = transformComponent->GetPosition() - oldPosition;
	//	newEvent.scaleChange = transformComponent->GetScale() - oldScale;
	//	newEvent.rotationChange = transformComponent->GetRotation() - oldRotation;

	//	if (newEvent.positionChange != Vec3::zero() || newEvent.scaleChange != Vec3::zero() || newEvent.rotationChange != Vec3::zero())
	//	{
	//		eventManager.post(newEvent, EventTypes::CHILD_TRANSFORMATION);
	//	}
	//}
}