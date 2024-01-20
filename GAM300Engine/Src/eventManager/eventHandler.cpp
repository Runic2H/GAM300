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
			Transform* parentComp = ecs.getComponent<Transform>(event->id);
			std::shared_ptr<ChildTransformationEvent> currentEvent = static_pointer_cast<ChildTransformationEvent>(event);
			
			Mat4 parenttransform = parentComp->GetTransformMatrix();
			for (auto childID : nameTagComponent->GetHierarchyChildren())
			{
				changeChildTransformation(childID, currentEvent->positionChange, currentEvent->scaleChange, currentEvent->rotationChange, parenttransform);
			}
		}
		eventManager.clearQueue(EventTypes::CHILD_TRANSFORMATION);
	}
	void EventHandler::changeChildTransformation(EntityID childEntity,  Vec3& positionChange,  Vec3& scaleChange,  Vec3& rotationChange, Mat4& parentTransform)
	{
		Transform* childTransform = GetTransform(childEntity);

		Mat4 parentRotation = Mat4::Rotate(rotationChange);
		Mat4 childRotation = Mat4::Rotate(childTransform->GetRotation());

		Mat4 combined = parentRotation * childRotation;
		Vec3 totalScale = Vec3(childTransform->GetScale().x * scaleChange.x, childTransform->GetScale().y * scaleChange.y, childTransform->GetScale().z * scaleChange.z);

		//Vec3 newPosition = childTransform->GetPosition();
		//Vec3 newScale = childTransform->GetScale();
		//Vec3 newRotation = childTransform->GetRotation();

		//newPosition = parentTransform * newPosition;
		//newScale = parentTransform * newScale;
		//newRotation = parentTransform * newRotation;
		
		//newPosition += positionChange;
		//newScale += scaleChange;
		//newRotation += rotationChange;
		childTransform->SetPosition(childTransform->GetPosition() + positionChange);
		childTransform->SetScale(totalScale);
		childTransform->SetRotation(combined.GetRotation());

		Mat4 newTransform{};
		if (childTransform->GetScale().x <= 0 || childTransform->GetScale().y <= 0 || childTransform->GetScale().z <= 0) {
		}
		else {
			newTransform = childTransform->GenerateTransform();
		}
		NameTag* childNameTag = GetNameTag(childEntity);

		for (auto childID : childNameTag->GetHierarchyChildren())
		{
			changeChildTransformation(childID, positionChange, scaleChange, rotationChange, newTransform);
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