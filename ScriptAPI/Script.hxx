/*!*****************************************************************************
 * \file          Script.hxx
 * \author        Elton Teo Zhe Wei
 * \par DP email: e.teo@digipen.edu
 * \par Course:   CSD3400
 * \par Section:  A
 * \date          01/10/2023
 * \brief         Virtual class for all script creation
 *******************************************************************************/
#pragma once

#include "IncludeFromEngine.hxx"
#include "Components/TransformComponent.hxx"
#include "Components/ColliderComponent.hxx"

namespace ScriptAPI
{
    public ref class Script abstract
    {
    public:
        void virtual Start() {};
        void virtual Update() {};
        void virtual OnDestroy() {};

        TransformComponent GetTransformComponent();
        ColliderComponent GetColliderComponent();

    internal:
        void SetEntityID(TDS::EntityID ID);
    private:
        TDS::EntityID entityID;
    };
}