/*!*************************************************************************
****
\file eventManager.h
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 28-9-2023
\brief  This program declares the functions in the eventManager class
****************************************************************************
***/

#ifndef EVENTMANAGER
#define EVENTMANAGER

#include <unordered_map>
#include <queue>
#include <vector>
#include <cstdarg>
#include "ecs/ecs.h"

namespace TDS
{
	// Enumeration for Event types
	enum class EventTypes
	{
		CHILD_TRANSFORMATION  // For changing child transformation based on parent
		//CHILD_ENABLE		  // For changing child enable / disable based on parent
	};

	// Base Event class
	class Event
	{
	public:
		EntityID id;
	};

	class ChildTransformationEvent : public Event
	{
	public:
		Vec3 positionChange;
		Vec3 scaleChange;
		Vec3 rotationChange;
	};

	// Event Manager Class
	class EventManager
	{
	public:
		/*!*************************************************************************
		Constructor of the EventManager class
		****************************************************************************/
		EventManager();
		/*!*************************************************************************
		Destructor of the EventManager class
		****************************************************************************/
		~EventManager();

		/*!*************************************************************************
		This function is called during initiailise to create a new queue
		****************************************************************************/
		template<typename U>
		void subscribe(U systemID);

		/*!*************************************************************************
		This function is called during initiailise to create a new queue
		****************************************************************************/
		template<typename T>
		inline void post(T event); // base function

		/*!*************************************************************************
		This function is called in runSystems to queue the events,
		splits the events into different queues here
		****************************************************************************/
		template<typename T, typename U, typename... S>
		inline void post(T event, U currentSystem, S... systemInput);

		/*!*************************************************************************
		This function is used to get the queue based on the SystemID
		****************************************************************************/
		template<typename U>
		std::vector<std::shared_ptr<Event>>& findQueue(U systemID);

		/*!*************************************************************************
		This function finds the entity in the queue
		****************************************************************************/
		template <typename T, typename U>
		std::shared_ptr<T> findEntity(U systemID, EntityID toFind);

		/*!*************************************************************************
		This function find event in the queue
		****************************************************************************/
		template <typename T, typename U>
		std::shared_ptr<T> findEvent(U systemID, int toFind);

		/*!*************************************************************************
		This function dequeues a queue
		****************************************************************************/
		template <typename U>
		void dequeue(U systemID, EntityID toRemove);

		/*!*************************************************************************
		This function removes an entity from the queue
		****************************************************************************/
		template <typename U>
		void removeFromQueue(U systemID, EntityID toRemove);

		/*!*************************************************************************
		This function removes an entity from all queues
		****************************************************************************/
		void removeFromQueues(EntityID toRemove);

		/*!*************************************************************************
		This function removes a queue
		****************************************************************************/
		template <typename U>
		void removeQueue(U systemID);

		/*!*************************************************************************
		This function adds a queue
		****************************************************************************/
		template <typename U>
		void addQueue(U systemID);

		/*!*************************************************************************
		This function clears a queue
		****************************************************************************/
		template<typename U>
		inline void clearQueue(U systemID);

		/*!*************************************************************************
		This function clears all queues
		****************************************************************************/
		void clearQueues();

	private:
		// Map of vectors of Events
		std::unordered_map<char, std::vector<std::shared_ptr<Event>>> masterQueue;
	};

	// Main event manager used throughout the engine
	extern EventManager eventManager;
}

#include "eventmanager/eventmanager.hpp"


#endif // EVENTMANAGER
