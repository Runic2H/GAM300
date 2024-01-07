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
#include "GameObject.hxx"
#include "Input.hxx"
#include "Time.hxx"
#include "HelperFunctions.hxx"
#include <iostream>
#include <chrono>
#include <thread>
#include <pplawait.h>
#include <algorithm>
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Threading;
using namespace System::Threading::Tasks;
using namespace System::Reflection;
using namespace concurrency;

#include "CustomAttributeHeaders.hxx"

namespace ScriptAPI
{
    public ref class Script abstract
    {
    public:
        void virtual Awake() {};
        void virtual OnEnable() {};
        void virtual Start() {};
        void virtual FixedUpdate() {};
        void virtual Update() {};
        void virtual LateUpdate() {};
        void virtual OnDisable() {};
        void virtual OnDestroy() {};

        void virtual OnTriggerEnter(ColliderComponent^ collider) {};
        void virtual OnTriggerStay(ColliderComponent^ collider) {};
        void virtual OnTriggerExit(ColliderComponent^ collider) {};

        void ToggleScript();

        generic <typename TResult>
        IAsyncEnumerable<TResult>^ Coroutine(Func<IAsyncEnumerable<TResult>^>^ func, int duration);
        
        GameObject^ GameObjectScriptFind(System::String^ name);

        [HideInInspector]
        GameObject^ gameObject;

        TransformComponent transform;

    internal:
        void SetFlags();
        bool isScriptEnabled();

        void setAwakeFlag();
        bool getAwakeFlag();

        void setStartFlag();
        bool getStartFlag();

    public:
        [HideInInspector]
        bool is_Enabled = true;
        [HideInInspector]
        bool is_Awake = false;
        [HideInInspector]
        bool is_Start = false;
    };

    public ref class ScriptSystem
    {
    public:
        generic <typename TResult>
        static IAsyncEnumerable<TResult>^ UnityCoroutine(Func<IAsyncEnumerable<TResult>^>^ func, int duration)
        {
            auto startTime = DateTime::Now;
            auto endTime = startTime + TimeSpan::FromMilliseconds(duration);

            while (DateTime::Now < endTime)
            {
                Thread::Sleep(1);
            }
            
            return func();
        }

        // Define a function that simulates an async operation and returns the result in a Task
        // Task<IAsyncEnumerable<TResult>^>^
        generic <typename TResult>
        static IAsyncEnumerable<TResult>^ UnityCoroutineC(Func<IAsyncEnumerable<TResult>^>^ func, std::chrono::milliseconds duration)
        {
            auto startTime = std::chrono::steady_clock::now();
            auto endTime = startTime + duration;

            // Continue with other work while waiting for the async operation to complete
            while (std::chrono::steady_clock::now() < endTime) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }

            // Call the provided custom async function
            /*IAsyncEnumerable<TResult>^ result = func();*/

            // Wrap the result in a Task
            /*return Task::FromResult(result);*/
            return func();
        }

    };
}