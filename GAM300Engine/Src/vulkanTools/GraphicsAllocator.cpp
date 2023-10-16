#define VMA_IMPLEMENTATION
#include "vulkanTools/GraphicsAllocator.h"
#include "vulkanTools/vulkanInstance.h"


namespace TDS
{
	GraphicsAllocator GraphicsAllocator::m_instance;
	GraphicsAllocator::GraphicsAllocator() :m_TotalAllocatedBytes(0), m_VulkanAllocator(0)
	{
	}
	GraphicsAllocator::~GraphicsAllocator()
	{
		if (m_VulkanAllocator)
			vmaDestroyAllocator(m_VulkanAllocator);
	}
	void GraphicsAllocator::Init(VulkanInstance& instance)
	{
		VmaAllocatorCreateInfo vmaCreateinfo{};
		vmaCreateinfo.vulkanApiVersion = VK_API_VERSION_1_3;
		vmaCreateinfo.physicalDevice = instance.getVkPhysicalDevice();
		vmaCreateinfo.device = instance.getVkLogicalDevice();
		vmaCreateinfo.instance = instance.getInstance();
		vmaCreateinfo.instance = instance.getInstance();
		vmaCreateAllocator(&vmaCreateinfo, &m_VulkanAllocator);
	}

	void GraphicsAllocator::UnMapMemory(VmaAllocation allocation)
	{
		vmaUnmapMemory(GraphicsAllocator::GetInstance().GetAllocator(), allocation);
	}

	void GraphicsAllocator::FreeMemory(VmaAllocation allocation)
	{
		vmaFreeMemory(GraphicsAllocator::GetInstance().GetAllocator(), allocation);
	}



}