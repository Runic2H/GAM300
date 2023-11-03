#pragma once
#include "Components/BoxColliderComponent.hxx"
#include "Components/CapsuleColliderComponent.hxx"
#include "Components/NameTagComponent.hxx"
#include "Components/SphereColliderComponent.hxx"
#include "Components/TransformComponent.hxx"

namespace ScriptAPI
{
    public ref class GameObject
    {
    public:
        generic <typename T>
        T GetComponent();

        BoxColliderComponent GetBoxColliderComponent();
        CapsuleColliderComponent GetCapsuleColliderComponent();
        NameTagComponent GetNameTagComponent();
        SphereColliderComponent GetSphereColliderComponent();
        TransformComponent GetTransformComponent();

        int GetEntityID();

    internal:
        void SetEntityID(TDS::EntityID ID);
    private:

        //entityID and is_Enabled set at SetEntityID
        TDS::EntityID entityID;
    };
}