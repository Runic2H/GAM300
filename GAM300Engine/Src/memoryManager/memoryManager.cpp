/*!*************************************************************************
****
\file memoryManager.cpp
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 28-9-2023
\brief  This program defines the functions in the MemoryManager class
****************************************************************************
***/

#include <windows.h>

#include "memoryManager/memoryManager.h"

namespace TDS
{
	// Unique pointer to instance of Scene
	std::unique_ptr<MemoryManager> MemoryManager::m_instance;

	/*!*************************************************************************
	Returns an instance of the MemoryManager
	****************************************************************************/
	std::unique_ptr<MemoryManager>& MemoryManager::GetInstance()
	{
		if (m_instance == nullptr)
		{
			m_instance = std::make_unique<MemoryManager>();
		}
		return m_instance;
	}

	/*!*************************************************************************
	Sets the number of components (from ECS)
	****************************************************************************/
	void MemoryManager::setNumberOfComponent(std::uint32_t _numberOfComponents)
	{
		numberOfComponents = _numberOfComponents;
	}

	/*!*************************************************************************
	Adds a new book (Archetype)
	****************************************************************************/
	void MemoryManager::newBook(const ArchetypeID& archetypeID)
	{
		BookData newbook;
		newbook.reservedSize.resize(numberOfComponents);
		newbook.usedSize.resize(numberOfComponents);
		newbook.committedSize.resize(numberOfComponents);
		newbook.startOfComponent.resize(numberOfComponents);

		books[archetypeID] = newbook;
	}

	/*!*************************************************************************
	Adds a new page (Component) in given book using ArchetypeID & ComponentID 
	****************************************************************************/
	unsigned char* MemoryManager::newPage(const ArchetypeID& archetypeID, std::uint32_t componentID)
	{
		if (books.find(archetypeID) == books.end()) // book does not exist
		{
			return nullptr;
		}

		books[archetypeID].reservedSize[componentID] = PAGE_SIZE;
		books[archetypeID].usedSize[componentID] = 0;
		books[archetypeID].committedSize[componentID] = 0;

		unsigned char* pointer = reserve(PAGE_SIZE);

		books[archetypeID].startOfComponent[componentID] = pointer;

		return pointer;
	}

	/*!*************************************************************************
	Resizes the page (Component) in given book using ArchetypeID & ComponentID
	****************************************************************************/
	void MemoryManager::resizePage(const ArchetypeID& archetypeID, std::uint32_t componentID)
	{
		if (books.find(archetypeID) == books.end()) // book does not exist
		{
			return;
		}

		books[archetypeID].reservedSize[componentID] += PAGE_SIZE;

		reserve(books[archetypeID].reservedSize[componentID], books[archetypeID].startOfComponent[componentID]);
	}

	/*!*************************************************************************
	Commits the book (Archetypes) in given book using ArchetypeID
	****************************************************************************/
	void MemoryManager::commitBook(const ArchetypeID& archetypeID)
	{
		int componentID = 0;
		for (int componentID = 0; componentID < archetypeID.size(); ++componentID)
		{
			if (archetypeID[componentID] == '0')
			{
				continue;
			}

			commit(books[archetypeID].committedSize[componentID], books[archetypeID].startOfComponent[componentID]);
		}
	}

	/*!*************************************************************************
	Commits the page (Archetypes) in given book using ArchetypeID & ComponentID
	****************************************************************************/
	void MemoryManager::commitPage(const ArchetypeID& archetypeID, std::uint32_t componentID)
	{
		commit(books[archetypeID].committedSize[componentID], books[archetypeID].startOfComponent[componentID]);
	}

	/*!*************************************************************************
	Frees the book (Archetypes) in given book using ArchetypeID
	****************************************************************************/
	void MemoryManager::freeBook(const ArchetypeID& archetypeID)
	{
		int componentID = 0;
		for (int componentID = 0; componentID < archetypeID.size(); ++componentID)
		{
			if (archetypeID[componentID] == '0')
			{
				continue;
			}

			release(books[archetypeID].startOfComponent[componentID]);
		}
	}

	/*!*************************************************************************
	Frees the page (Component) in given pointer
	****************************************************************************/
	void MemoryManager::freePage(unsigned char* pointer)
	{
		release(pointer);
	}

	/*!*************************************************************************
	Reserve space in the given book (Archetypes) using ArchetypeID & ComponentID
	****************************************************************************/
	void MemoryManager::reserveComponentSpace(const ArchetypeID& archetypeID, std::uint32_t componentID, std::uint32_t componentSize)
	{
		books[archetypeID].committedSize[componentID] = componentSize;

		while (books[archetypeID].committedSize[componentID] > books[archetypeID].reservedSize[componentID])
		{
			resizePage(archetypeID, componentID);
		}
	}

	/*!*************************************************************************
	Getting the component data in the given book (Archetypes) using ArchetypeID 
	& ComponentID
	****************************************************************************/
	unsigned char* MemoryManager::getComponentData(ArchetypeID archetypeID, std::uint32_t componentID, std::uint32_t componentSize, std::uint32_t index)
	{
		if (books[archetypeID].committedSize[componentID] < (index * componentSize))
		{
			return nullptr; // out of memory
		}

		return books[archetypeID].startOfComponent[componentID] + index * componentSize;
	}

	/*!*************************************************************************
	Adding the component data in the given book (Archetypes) using ArchetypeID
	& ComponentID
	****************************************************************************/
	unsigned char* MemoryManager::addComponentData(ArchetypeID archetypeID, std::uint32_t componentID, std::uint32_t componentSize, std::uint32_t index)
	{
		books[archetypeID].usedSize[componentID] += componentSize;

		std::uint32_t& committedSize = books[archetypeID].committedSize[componentID];

		// Add check to make sure there is enough space
		if (committedSize < books[archetypeID].usedSize[componentID])
		{
			// If committedSize is less than the normal page size, then x2, if not then + PAGE_SIZE
			if (committedSize > PAGE_SIZE)
			{
				committedSize += PAGE_SIZE;
			}
			else
			{
				committedSize += committedSize;
			}

			if (books[archetypeID].reservedSize[componentID] < committedSize)
			{
				resizePage(archetypeID, componentID);
			}

			commit(committedSize, books[archetypeID].startOfComponent[componentID]);
		}

		return books[archetypeID].startOfComponent[componentID] + index * componentSize;
	}

	/*!*************************************************************************
	Removing the end the component data in the given book (Archetypes) using 
	ArchetypeID & ComponentID
	****************************************************************************/
	void MemoryManager::removeComponentEndData(ArchetypeID archetypeID, std::uint32_t componentID, std::uint32_t componentSize)
	{
		books[archetypeID].usedSize[componentID] -= componentSize;
	}

	/*!*************************************************************************
	Reserve memory using VirtualAlloc
	****************************************************************************/
	unsigned char* MemoryManager::reserve(std::uint32_t newPageSize, unsigned char* startingPointer)
	{
		return reinterpret_cast<unsigned char*>(VirtualAlloc(reinterpret_cast<void*>(startingPointer), newPageSize, MEM_RESERVE, PAGE_READONLY));
	}

	/*!*************************************************************************
	Coomit memory using VirtualAlloc
	****************************************************************************/
	unsigned char* MemoryManager::commit(std::uint32_t usedSize, unsigned char* startingPointer)
	{
		return reinterpret_cast<unsigned char*>(VirtualAlloc(reinterpret_cast<void*>(startingPointer), usedSize, MEM_COMMIT, PAGE_READWRITE));
	}

	/*!*************************************************************************
	Decommit memory using VirtualAlloc
	****************************************************************************/
	void MemoryManager::decommit(std::uint32_t componentSize, unsigned char* pointer)
	{
		VirtualFree(reinterpret_cast<void*>(pointer), componentSize, MEM_DECOMMIT);
	}

	/*!*************************************************************************
	Release memory using VirtualAlloc
	****************************************************************************/
	void MemoryManager::release(unsigned char* startingPointer)
	{
		VirtualFree(reinterpret_cast<void*>(startingPointer), 0, MEM_RELEASE);
	}
}
