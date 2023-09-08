#ifndef EVENTMANAGER
#define EVENTMANAGER

#include "ecs/ecs.h"

namespace TDS
{
	// Enumeration for Systems
	enum Systems
	{
		AI = 0,
		COLLISION,
		PATHFINDING,
		PHYSICS,
		GRAPHICS,
		SOUND,
		ANIMATION
	};

	// Base Event class
	class Event
	{
	public:
		EntityID id;
	};

	// Event Manager Class
	class EventManager
	{
	public:
		EventManager();
		~EventManager();

		/*  _________________________________________________________________________*/
		/*! subscribe

		@param						System enumeration
		@return						None

		This function is called during initiailise to create a new queue
		*/
		template<typename U>
		void subscribe(U systemID);

		/*  _________________________________________________________________________*/
		/*! post

		@param						Templated to for derived event classes
		@return						None

		This function is called in runSystems to queue the events,
		splits the events into different queues here
		*/
		template<typename T>
		inline void post(T event); // base function

		template<typename T, typename U, typename... S>
		inline void post(T event, U currentSystem, S... systemInput);

		/*  _________________________________________________________________________*/
		/*! findQueue

		@param						System enumeration
		@return						Queue for the system

		This function is used to get the queue based on the SystemID
		*/
		template<typename U>
		std::vector<std::shared_ptr<Event>>& findQueue(U systemID);


		/*  _________________________________________________________________________*/
		/*! findEntity

		@param						System enumeration
		@return						Queue for the system

		This function is used to get the queue based on the SystemID
		*/
		template <typename T, typename U>
		std::shared_ptr<T> findEntity(U systemID, EntityID toFind);

		/*  _________________________________________________________________________*/
		/*! findEvent

		@param						System enumeration
		@return						Queue for the system

		This function is used to get the queue based on the SystemID
		*/
		template <typename T, typename U>
		std::shared_ptr<T> findEvent(U systemID, int toFind);

		/*  _________________________________________________________________________*/
		/*! dequeue

		@param						SystemID
		@param						toRemove
		@return						Pointer to the dequeued event

		This function is called in the systems to read and dequeue the queue
		*/
		template <typename U>
		void dequeue(U systemID, EntityID toRemove);

		template <typename U>
		void removeFromQueue(U systemID, EntityID toRemove);

		void removeFromQueues(EntityID toRemove);

		template <typename U>
		void removeQueue(U systemID);

		template <typename U>
		void addQueue(U systemID);

		/*  _________________________________________________________________________*/
		/*! clearQueues

		@return						Void

		This function is called to clear the queues of each system
		*/
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
