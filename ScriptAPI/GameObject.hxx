#pragma once
#include "Components/BoxColliderComponent.hxx"
#include "Components/CameraComponent.hxx"
#include "Components/CapsuleColliderComponent.hxx"
#include "Components/NameTagComponent.hxx"
#include "Components/RigidBodyComponent.hxx"
#include "Components/SphereColliderComponent.hxx"
#include "Components/TransformComponent.hxx"
#include "Components/UISpriteComponent.hxx"
namespace ScriptAPI
{
    public ref class GameObject
    {
    public:
        generic <typename T>
        T GetComponent();

        BoxColliderComponent GetBoxColliderComponent();
        CameraComponent GetCameraComponent();
        CapsuleColliderComponent GetCapsuleColliderComponent();
        NameTagComponent GetNameTagComponent();
        RigidBodyComponent GetRigidBodyComponent();
        SphereColliderComponent GetSphereColliderComponent();
        TransformComponent GetTransformComponent();
        UISpriteComponent GetUISpriteComponent();
        int GetEntityID();

        TransformComponent transform;

    internal:
        void SetEntityID(TDS::EntityID ID);
    private:

        //entityID and is_Enabled set at SetEntityID
        TDS::EntityID entityID;
    };
}