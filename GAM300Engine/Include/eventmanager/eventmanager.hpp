/*!*************************************************************************
****
\file eventManager.hpp
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 28-9-2023
\brief  This program defines the functions in the eventManager class
****************************************************************************
***/

namespace TDS
{
	/*!*************************************************************************
	Constructor of the EventManager class
	****************************************************************************/
	inline EventManager::EventManager() { }
	/*!*************************************************************************
	Destructor of the EventManager class
	****************************************************************************/
	inline EventManager::~EventManager() { }

	/*!*************************************************************************
	This function is called during initiailise to create a new queue
	****************************************************************************/
	template<typename U>
	inline void EventManager::subscribe(U systemID)
	{
		char systemIDMask = static_cast<char>(systemID);
		// check if systemID is used
		if (masterQueue.contains(systemIDMask))
		{
			return;	// can't re-register a type
		}

		std::vector<std::shared_ptr<Event>> eventQueue;
		masterQueue.emplace(systemIDMask, eventQueue);
	}

	/*!*************************************************************************
	This function is called during initiailise to create a new queue
	****************************************************************************/
	template<typename T>
	inline void EventManager::post(T event) // base function
	{

	}

	/*!*************************************************************************
	This function is called in runSystems to queue the events,
	splits the events into different queues here
	****************************************************************************/
	template<typename T, typename U, typename... S>
	inline void EventManager::post(T event, U currentSystem, S... systemInput)
	{
		std::shared_ptr<Event> newEvent = std::make_shared<T>(event);

		// While each system
		char systemID = static_cast<char>(currentSystem);

		// Checking if entity exist inside queue
		//bool check = false;
		//for (int j = 0; j < masterQueue[systemID].size(); ++j)
		//{
		//	if (masterQueue[systemID][j]->id == newEvent->id)
		//	{
		//		masterQueue[systemID][j] = newEvent;
		//		check = true;
		//		break;
		//	}
		//}
		//if (!check)
		//{
			masterQueue[systemID].emplace_back(newEvent); // for now, allow multiple 
		//}

		post(event, systemInput...);
	}

	/*!*************************************************************************
	This function is used to get the queue based on the SystemID
	****************************************************************************/
	template<typename U>
	inline std::vector<std::shared_ptr<Event>>& EventManager::findQueue(U systemID)
	{
		return masterQueue[static_cast<char>(systemID)];
	}

	/*!*************************************************************************
	This function finds the entity in the queue
	****************************************************************************/
	template<typename T, typename U>
	inline std::shared_ptr<T> EventManager::findEntity(U systemID, EntityID toFind)
	{
		char id = static_cast<char>(systemID);

		for (int i = 0; i < masterQueue[id].size(); ++i)
		{
			if (masterQueue[id][i]->id == toFind)
			{
				std::shared_ptr<T> eventPop = static_pointer_cast<T>(masterQueue[id][i]);
				return eventPop;
			}
		}
		return nullptr;
	}

	/*!*************************************************************************
	This function find event in the queue
	****************************************************************************/
	template<typename T, typename U>
	inline std::shared_ptr<T> EventManager::findEvent(U systemID, int toFind)
	{
		char id = static_cast<char>(systemID);

		if (toFind >= masterQueue[id].size() || toFind < 0)
		{
			return nullptr;
		}

		std::shared_ptr<T> eventPop = static_pointer_cast<T>(masterQueue[id][toFind]);

		return eventPop;
	}

	/*!*************************************************************************
	This function dequeue the queue
	****************************************************************************/
	template<typename U>
	inline void EventManager::dequeue(U systemID, EntityID toRemove)
	{
		char id = static_cast<char>(systemID);

		for (int i = 0; i < masterQueue[id].size(); ++i)
		{
			if (masterQueue[id][i]->id == toRemove)
			{
				masterQueue[id].erase(masterQueue[id].begin() + i);
			}
		}
	}

	/*!*************************************************************************
	This function removes an entity from the queue
	****************************************************************************/
	template <typename U>
	inline void EventManager::removeFromQueue(U systemID, EntityID toRemove)
	{
		dequeue(systemID, toRemove);
	}

	/*!*************************************************************************
	This function removes an entity from all queues
	****************************************************************************/
	inline void EventManager::removeFromQueues(EntityID toRemove)
	{
		for (auto iter = masterQueue.begin(); iter != masterQueue.end(); ++iter)
		{
			dequeue(iter->first, toRemove);
		}
	}

	/*!*************************************************************************
	This function removes a queue
	****************************************************************************/
	template<typename U>
	void EventManager::removeQueue(U systemID)
	{
		char system = static_cast<char>(systemID);
		masterQueue.erase(system);
	}

	/*!*************************************************************************
	This function adds a queue
	****************************************************************************/
	template<typename U>
	void EventManager::addQueue(U systemID)
	{
		char system = static_cast<char>(systemID);
		masterQueue[system];
	}

	/*!*************************************************************************
	This function clears a queue
	****************************************************************************/
	template<typename U>
	inline void EventManager::clearQueue(U systemID)
	{
		char system = static_cast<char>(systemID);
		masterQueue[system].clear();
	}

	/*!*************************************************************************
	This function clears all queues
	****************************************************************************/
	inline void EventManager::clearQueues()
	{
		for (auto iter = masterQueue.begin(); iter != masterQueue.end(); ++iter)
		{
			masterQueue[iter->first].clear();
		}
	}
}
