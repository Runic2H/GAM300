#ifndef COMPONENT_RTTR_REGISTRATION
#define COMPONENT_RTTR_REGISTRATION

#include <rttr/registration>
#include <rttr/registration_friend>
#include <rttr/type>

#include "components/components.h"

using namespace TDS;

RTTR_REGISTRATION
{
	rttr::registration::class_<Vec2>("Vec2")
		.property("x", &Vec2::x)
		.property("y", &Vec2::y);
	rttr::registration::class_<Vec3>("Vec3")
		.property("x", &Vec3::x)
		.property("y", &Vec3::y)
		.property("z", &Vec3::z);
	rttr::registration::class_<Vec4>("Vec4")
		.property("x", &Vec4::x)
		.property("y", &Vec4::y)
		.property("z", &Vec4::z)
		.property("w", &Vec4::w);

	//rttr::registration::enumeration<NodeStatus>("NodeStatus")
	//(
	//	rttr::value("READY", NodeStatus::READY),
	//	rttr::value("RUNNING", NodeStatus::RUNNING),
	//	rttr::value("SUCCESS", NodeStatus::SUCCESS),
	//	rttr::value("FAILED", NodeStatus::FAILED)
	//);

	//rttr::registration::class_<Node>("Node")
	//	.property("parent", &Node::parent)
	//	.property("children", &Node::children)
	//	.property("childIndex", &Node::childIndex)
	//	.property("name", &Node::name);

	rttr::registration::class_<AI>("AI")
		//.method("GetBehaviourTreeIndex", &AI::GetBehaviourTreeIndex)
		//.method("SetBehaviourTreeIndex", &AI::SetBehaviourTreeIndex)
		//.property("BehaviourTreeIndex", &AI::mBehaviourTreeIndex)
		//.method("GetEntityCurrentStatus", &AI::GetEntityCurrentStatus)
		//.method("SetEntityCurrentStatus", &AI::SetEntityCurrentStatus)
		//.property("EntityCurrentStatus", &AI::mEntityCurrentStatus)
		//.method("GetCurrentNode", &AI::GetCurrentNode)
		//.method("SetCurrentNode", &AI::SetCurrentNode)
		//.method("CurrentNode", &AI::mCurrentNode)
		//.method("GetTimer", &AI::GetTimer)
		//.method("SetTimer", &AI::SetTimer)
		//.method("Timer", &AI::mTimer)
		.method("Serialize", &AI::Serialize)
		.method("Deserialize", &AI::Deserialize);

	rttr::registration::class_<BoxCollider>("Box Collider")
		.method("Serialize", &BoxCollider::Serialize)
		.method("Deserialize", &BoxCollider::Deserialize);

	rttr::registration::class_<CameraComponent>("Camera Component")
		.method("Serialize", &CameraComponent::Serialize)
		.method("Deserialize", &CameraComponent::Deserialize);
	
	rttr::registration::class_<CapsuleCollider>("Capsule Collider")
		.method("Serialize", &CapsuleCollider::Serialize)
		.method("Deserialize", &CapsuleCollider::Deserialize);

	rttr::registration::class_<GraphicsComponent>("Graphics Component")
		.method("Serialize", &GraphicsComponent::Serialize)
		.method("Deserialize", &GraphicsComponent::Deserialize);

	rttr::registration::class_<NameTag>("Name Tag")
		.method("GetNameTag", &NameTag::GetNameTag)
		.method("SetNameTag", &NameTag::SetNameTag)
		.property("Name", &NameTag::mName)
		.method("Serialize", &NameTag::Serialize)
		.method("Deserialize", &NameTag::Deserialize);

	rttr::registration::class_<PlayerAttributes>("Player Attributes")
		.method("Serialize", &PlayerAttributes::Serialize)
		.method("Deserialize", &PlayerAttributes::Deserialize);

	rttr::registration::class_<RigidBody>("Rigid Body")
		.method("Serialize", &RigidBody::Serialize)
		.method("Deserialize", &RigidBody::Deserialize);

	rttr::registration::class_<SphereCollider>("Sphere Collider")
		.method("Serialize", &SphereCollider::Serialize)
		.method("Deserialize", &SphereCollider::Deserialize);

	rttr::registration::class_<Sprite>("Sprite")
		.method("Serialize", &Sprite::Serialize)
		.method("Deserialize", &Sprite::Deserialize);

	rttr::registration::class_<Tag>("Tag")
		.method("GetTag", &Tag::GetTag)
		.method("SetTag", &Tag::SetTag)
		.property("Tag", &Tag::mTag)
		.method("GetTargetTag", &Tag::GetTargetTag)
		.method("SetTargetTag", &Tag::SetTargetTag)
		.property("mTargetTag", &Tag::mTargetTag)
		.method("Serialize", &Tag::Serialize)
		.method("Deserialize", &Tag::Deserialize);

	rttr::registration::class_<Transform>("Transform")
		.method("GetPosition", &Transform::GetPosition)
		.method("SetPosition", rttr::select_overload<void(Vec3)>(&Transform::SetPosition))
		.method("SetPosition", rttr::select_overload<void(float, float, float)>(&Transform::SetPosition))
		.property("Position", &Transform::mPosition)//, rttr::registration::private_access)
		.method("GetScale", &Transform::GetScale)
		.method("SetScale", rttr::select_overload<void(Vec3)>(&Transform::SetScale))
		.method("SetScale", rttr::select_overload<void(float, float, float)>(&Transform::SetScale))
		.property("Scale", &Transform::mScale)//, rttr::registration::private_access)
		.method("GetRotation", &Transform::GetRotation)
		.method("SetRotation", rttr::select_overload<void(Vec3)>(& Transform::SetRotation))
		.method("SetRotation", rttr::select_overload<void(float, float, float)>(& Transform::SetRotation))
		.property("Rotation", &Transform::mRotation)//, rttr::registration::private_access)
		.method("Serialize", &Transform::Serialize)
		.method("Deserialize", &Transform::Deserialize);

	rttr::registration::class_<WinData>("Win Data")
		.method("Serialize", &WinData::Serialize)
		.method("Deserialize", &WinData::Deserialize);
}


#endif //COMPONENT_RTTR_REGISTRATION