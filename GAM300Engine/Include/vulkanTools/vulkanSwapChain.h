#ifndef VULKAN_SWAP_CHAIN
#define VULKAN_SWAP_CHAIN


#define	VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.h>

namespace TDS
{
	typedef struct _SwapChainBuffers
	{
		VkImage image;
		VkImageView view;
	}SwapChainBuffer;

	class VulkanSwapChain
	{
	
	public:
		void initSurface(void* platformHandle, void* platformWindow);
		void connect(VkInstance instance, VkPhysicalDevice physicalDevice, VkDevice device);
		void create(uint32_t* width, uint32_t* height, bool vsync = false, bool fullscreen = false);
		VkResult acquireNextImage(VkSemaphore presentCompleteSemaphore, uint32_t* imageIndex);
		VkResult queuePresent(VkQueue queue, uint32_t imageIndex, VkSemaphore waitSemaphore = VK_NULL_HANDLE);
		void cleanup();


	public:
		VkFormat colorFormat;
		VkColorSpaceKHR colorSpace;
		VkSwapchainKHR swapChain = VK_NULL_HANDLE;
		uint32_t imageCount;
		std::vector<VkImage> images;
		std::vector<SwapChainBuffer> buffers;
		uint32_t queueNodeIndex = UINT32_MAX;
	
	private:
		VkInstance instance;
		VkDevice device;
		VkPhysicalDevice physicalDevice;
		VkSurfaceKHR surface;
	};

}



#endif//!VULKAN_SWAP_CHAIN