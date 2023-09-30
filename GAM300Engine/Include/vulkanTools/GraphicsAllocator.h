#pragma once
#include <vma/vk_mem_alloc.h>
#include "dotnet/ImportExport.h"
namespace TDS
{
	template <typename T>
	inline constexpr bool always_false_v = false;

	class VulkanInstance;
	class GraphicsAllocator
	{
	public:
		static GraphicsAllocator m_instance;

		static inline GraphicsAllocator& GetInstance()
		{
			return m_instance;
		}

		DLL_API GraphicsAllocator();
		DLL_API ~GraphicsAllocator();

		void DLL_API Init(VulkanInstance& instance);
		template <typename T>
		static void MapMemory(T* RequestSpace, VmaAllocation allocation)
		{
			vmaMapMemory(GraphicsAllocator::GetInstance().GetAllocator(), allocation, (void**)(RequestSpace));

		}
		static void DLL_API UnMapMemory(VmaAllocation allocation);

		inline VmaAllocator& GetAllocator()
		{
			return m_VulkanAllocator;
		}
		inline size_t GetTotalAllocationInBytes()
		{
			return m_TotalAllocatedBytes;
		}
		inline void AddAllocationBytes(VkDeviceSize bytes)
		{
			m_TotalAllocatedBytes += bytes;
		}

		template <typename T>
		static VmaAllocation Allocate(void* CreateInfo, VmaMemoryUsage usage, T*& buffer)
		{
			static_assert(always_false_v<T>, "Cant allocate is this type");
			return nullptr;
		}


		template <>
		static VmaAllocation Allocate<VkBuffer>(void* CreateInfo, VmaMemoryUsage usage, VkBuffer*& buffer)
		{
			VmaAllocationCreateInfo bufferAlocateInfo{};

			bufferAlocateInfo.usage = usage;

			VmaAllocation newAllocation{};
			VmaAllocationInfo allocationinfo{};

			vmaCreateBuffer(GraphicsAllocator::GetInstance().GetAllocator(), (VkBufferCreateInfo*)CreateInfo, &bufferAlocateInfo,
				buffer, &newAllocation, &allocationinfo);

			GraphicsAllocator::GetInstance().AddAllocationBytes(allocationinfo.size);
			return newAllocation;

		}

		template <>
		static VmaAllocation Allocate<VkImage>(void* CreateInfo, VmaMemoryUsage usage, VkImage*& buffer)
		{
			VmaAllocationCreateInfo bufferAlocateInfo{};

			bufferAlocateInfo.usage = usage;

			VmaAllocation newAllocation{};
			VmaAllocationInfo allocationinfo{};

			vmaCreateImage(GraphicsAllocator::GetInstance().GetAllocator(), (VkImageCreateInfo*)CreateInfo, &bufferAlocateInfo,
				buffer, &newAllocation, &allocationinfo);


			GraphicsAllocator::GetInstance().AddAllocationBytes(allocationinfo.size);
			return newAllocation;
		}

		static void DLL_API FreeMemory(VmaAllocation alloc);

		template <typename T>
		void FreeBuffer(T memBuffer, VmaAllocation allocation)
		{
			static_assert(always_false_v<T>, "Cant allocate is this type");
		}

		template <>
		void FreeBuffer<VkBuffer>(VkBuffer buffer, VmaAllocation allocation)
		{
			vmaDestroyBuffer(GraphicsAllocator::GetInstance().GetAllocator(), buffer, allocation);
		}

		template <>
		void FreeBuffer<VkImage>(VkImage image, VmaAllocation allocation)
		{
			vmaDestroyImage(GraphicsAllocator::GetInstance().GetAllocator(), image, allocation);
		}

	private:
		VkDeviceSize m_TotalAllocatedBytes;
		VmaAllocator m_VulkanAllocator;

	};
}