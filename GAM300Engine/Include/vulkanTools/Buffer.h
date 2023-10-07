/*!*************************************************************************
****
\file Buffer.h
\author Ng Zuo Xian Amadeus
\par DP email: ng.z@digipen.edu
\par Course: CSD3400
\par Section: a
\date 22-9-2023
\brief  Contains the Buffer Class and its member functions
****************************************************************************
***/

#ifndef TDS_VULKAN_BUFFER
#define TDS_VULKAN_BUFFER

#include "vulkanInstance.h"
namespace TDS {
	class DLL_API Buffer {
	public:
		//constructor and destructor
		Buffer(VulkanInstance& Instance, VkDeviceSize instanceSize, uint32_t instanceCount, VkBufferUsageFlags usageFlag, VkMemoryPropertyFlags Property, VkDeviceSize minOffsetAlignment = 1);
		~Buffer();

		//no copy constructor
		Buffer(const Buffer&) = delete;
		Buffer& operator=(const Buffer&) = delete;

		/*!*************************************************************************
		This function maps memory to buffer
		****************************************************************************/
		VkResult					map(VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0);
		/*!*************************************************************************
		This function unmaps memory from buffer 
		****************************************************************************/
		void						unmap();

		//functions to act on Device memory
		void						WritetoBuffer(void* data, VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0);
		VkResult					flush(VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0);
		VkDescriptorBufferInfo		descriptorinfo(VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0);
		VkResult					invalidate(VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0);

		//functions on specific index in Device Memory
		void						writetoIndex(void* data, int index);
		VkResult					flushIndex(int index);
		VkDescriptorBufferInfo		descriptorinfoforIndex(int index);
		VkResult					invalidateIndex(int indexx);

		//getters
		VkBuffer				getBuffer()			const { return m_Buffer; }
		void*					getMappedmemory()	const { return m_memory; }
		uint32_t				getInstanceCount()	const { return m_InstanceCount; }
		VkDeviceSize			getInstanceSize()	const { return m_InstanceSize; }
		VkDeviceSize			getAlignmentSize()	const { return m_AlignmentSize; }
		VkBufferUsageFlags		getUsageFlags()		const { return m_UsageFlags; }
		VkMemoryPropertyFlags	getPropertyFlags()	const { return m_MemoryPropertyFlag; }
		VkDeviceSize			getBufferSize()		const { return m_BufferSize; }

	private:
		static VkDeviceSize getAlignment(VkDeviceSize size, VkDeviceSize minOffsetAlignment);

		VulkanInstance& m_Instance;
		void* m_pMapped = nullptr;
		VkBuffer					m_Buffer = VK_NULL_HANDLE;
		VkDeviceMemory				m_memory = VK_NULL_HANDLE;

		VkDeviceSize				m_BufferSize;
		VkDeviceSize				m_InstanceSize;
		VkDeviceSize				m_AlignmentSize;
		uint32_t					m_InstanceCount;
		VkBufferUsageFlags			m_UsageFlags;
		VkMemoryPropertyFlags		m_MemoryPropertyFlag;
	};
}

#endif //#ifndef TDS_VULKAN_BUFFER
