#ifndef MEMORYMANAGER
#define MEMORYMANAGER

#include <cstdint>
#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include "dotnet/ImportExport.h"
namespace TDS
{
	class DLL_API MemoryManager // for ECS
	{
	private:
		typedef std::string ArchetypeID;

	public:
		/*!*************************************************************************
		Returns an instance of the MemoryManager
		****************************************************************************/
		static std::unique_ptr<MemoryManager>& GetInstance();

		struct BookData
		{
			// For reserved memory (total memory that can be committed)
			std::vector<std::uint32_t> reservedSize;
			// For memory committed / going to commit
			std::vector<std::uint32_t> usedSize;
			//
			std::vector<std::uint32_t> committedSize;
			// 
			std::vector<unsigned char*> startOfComponent;
		};

		void setNumberOfComponent(std::uint32_t _numberOfComponents);

		void newBook(const ArchetypeID& archetypeID);
		unsigned char* newPage(const ArchetypeID& archetypeID, std::uint32_t componentID);
		void resizePage(const ArchetypeID& archetypeID, std::uint32_t componentID);

		void commitBook(const ArchetypeID& archetypeID);
		void commitPage(const ArchetypeID& archetypeID, std::uint32_t componentID);

		void freeBook(const ArchetypeID& archetypeID);
		void freePage(unsigned char* pointer);

		// Reserving data space to commit
		void reserveComponentSpace(const ArchetypeID& archetypeID, std::uint32_t componentID, std::uint32_t componentSize);

		// Putting data into committed space
		unsigned char* getComponentData(ArchetypeID archetypeID, std::uint32_t componentID, std::uint32_t componentSize, std::uint32_t index);
		unsigned char* addComponentData(ArchetypeID archetypeID, std::uint32_t componentID, std::uint32_t componentSize, std::uint32_t index);
		void removeComponentEndData(ArchetypeID archetypeID, std::uint32_t componentID, std::uint32_t componentSize);

	private:
		// Unique pointer to MemoryManager
		static std::unique_ptr<MemoryManager> m_instance;

		const std::uint32_t PAGE_SIZE = 4096;
		std::uint32_t numberOfComponents;

		std::unordered_map<ArchetypeID, BookData> books;

		// VirtualAlloc functions
		unsigned char* reserve(std::uint32_t newPageSize, unsigned char* startingPointer = nullptr);
		unsigned char* commit(std::uint32_t usedSize, unsigned char* startingPointer = nullptr);
		void decommit(std::uint32_t componentSize, unsigned char* pointer);
		void release(unsigned char* startingPointer);
	};
}

#endif