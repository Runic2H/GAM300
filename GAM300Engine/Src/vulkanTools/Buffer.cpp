/*!*************************************************************************
****
\file Buffer.cpp
\author Ng Zuo Xian Amadeus
\par DP email: ng.z@digipen.edu
\par Course: CSD3400
\par Section: a
\date 22-9-2023
\brief  Function definitions of the Buffer Class
****************************************************************************
***/
#include "vulkanTools/Buffer.h"

namespace TDS {

	//gets the alignment in the logical device
	VkDeviceSize Buffer::getAlignment(VkDeviceSize InstanceSize, VkDeviceSize minOffsetAlignment)
	{
		if (minOffsetAlignment > 0) return (InstanceSize + minOffsetAlignment - 1) & ~(minOffsetAlignment - 1);
		return InstanceSize;
	}

	//Buffer constructor
	Buffer::Buffer(VulkanInstance& Instance, VkDeviceSize InstanceSize, uint32_t InstanceCount, VkBufferUsageFlags UsageFlags, VkMemoryPropertyFlags memoryPropertyFlag, VkDeviceSize minOffsetAlignment)
		: m_Instance(Instance), m_InstanceSize(InstanceSize), m_InstanceCount(InstanceCount), m_UsageFlags(UsageFlags), m_MemoryPropertyFlag(memoryPropertyFlag)
	{
		m_AlignmentSize = getAlignment(InstanceSize, minOffsetAlignment);
		m_BufferSize = m_AlignmentSize * m_InstanceCount;
		Instance.createBuffers(m_BufferSize, m_UsageFlags, m_MemoryPropertyFlag, m_Buffer, m_memory);
	}

	//Buffer destructor
	Buffer::~Buffer()
	{
		unmap();
		vkDestroyBuffer(m_Instance.getVkLogicalDevice(), m_Buffer, nullptr);
		vkFreeMemory(m_Instance.getVkLogicalDevice(), m_memory, nullptr);
	}

	//map data to buffer
	VkResult Buffer::map(VkDeviceSize size, VkDeviceSize offset) {
		assert(m_Buffer && m_memory && "Called map before creation of buffer");
		return vkMapMemory(m_Instance.getVkLogicalDevice(), m_memory, offset, size, 0, &m_pMapped);
	}

	//unmap data to buffer
	void Buffer::unmap() {
		if (m_pMapped) {
			vkUnmapMemory(m_Instance.getVkLogicalDevice(), m_memory);
			m_pMapped = nullptr;
		}
	}

	//copy specified size of data to buffer, writes whole buffer range by default
	void Buffer::WritetoBuffer(void* Data, VkDeviceSize size, VkDeviceSize offset) {
		assert(m_pMapped && "cannot copy to unmapped buffer");

		if (size == VK_WHOLE_SIZE) {
			memcpy(m_pMapped, Data, m_BufferSize);
		}
		else {
			char* memOffset = (char*)m_pMapped;
			memOffset += offset;
			memcpy(memOffset, Data, size);
		}
	}

	//flushes memory range of buffer to make it visible to device
	VkResult Buffer::flush(VkDeviceSize size, VkDeviceSize offset) {
		VkMappedMemoryRange mappedRange{};
		mappedRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
		mappedRange.memory = m_memory;
		mappedRange.offset = offset;
		mappedRange.size = size;
		return vkFlushMappedMemoryRanges(m_Instance.getVkLogicalDevice(), 1, &mappedRange);
	}

	//invalidate memory range of buffer to make it visible to host
	VkResult Buffer::invalidate(VkDeviceSize size, VkDeviceSize Offset) {
		VkMappedMemoryRange mappedRange{};
		mappedRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
		mappedRange.memory = m_memory;
		mappedRange.offset = Offset;
		mappedRange.size = size;
		return vkInvalidateMappedMemoryRanges(m_Instance.getVkLogicalDevice(), 1, &mappedRange);
	}

	//create buffer infodescriptor
	VkDescriptorBufferInfo Buffer::descriptorinfo(VkDeviceSize size, VkDeviceSize offset) {
		return VkDescriptorBufferInfo{ m_Buffer, offset, size };
	}

	//copy instancesize amount of data in bytes to mapped buffer at offset index* alignment
	void Buffer::writetoIndex(void* Data, int index) {
		WritetoBuffer(Data, m_InstanceSize, index * m_AlignmentSize);
	}

	//flushes memory at index* alignmentsize of buffer to make it visible on device
	VkResult Buffer::flushIndex(int index) {
		return flush(m_AlignmentSize, index * m_AlignmentSize);
	}

	//get the descriptorinfo at specified index
	VkDescriptorBufferInfo Buffer::descriptorinfoforIndex(int index) {
		return descriptorinfo(m_AlignmentSize, index * m_AlignmentSize);
	}

	//invalidate the data held at the index
	VkResult Buffer::invalidateIndex(int index) {
		return invalidate(m_AlignmentSize, index * m_AlignmentSize);
	}
}