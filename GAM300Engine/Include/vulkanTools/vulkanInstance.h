/*!*************************************************************************
****
\file vulkanInstance.h
\author Ng Zuo Xian Amadeus
\par DP email: ng.z@digipen.edu
\par Course: CSD3400
\par Section: a
\date 22-9-2023
\brief  Contains the vulkanInstance Class and its member functions
****************************************************************************
***/
#ifndef VULKAN_CREATE_INSTANCE
#define VULKAN_CREATE_INSTANCE

#ifndef NOMINMAX
#define NOMINMAX
#endif//NOMINMAX
#define	VK_USE_PLATFORM_WIN32_KHR

#include <vulkan/vulkan.h>
#include <vector>
//#include <string>
//#include <iostream>
//#include <set>
//#include <limits>
//#include <algorithm>
//#include <fstream>
#include <optional>
//#include <array>

//assimp to be moved
//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>
//assimp
#include "windowswindow.h"
#include "vulkanTools/vulkanDebugger.h"
#include "dotnet/ImportExport.h"
//#include "vulkanTools/vulkanDevice.h"
//#include "TDSMath.h"
////#include "vulkanSwapChain.h"
//#include "Vector2.h"
//#include "dotnet/ImportExport.h"
//#include "camera/camera.h"
namespace TDS
{

	class VulkanInstance
	{
	public:
		struct QueueFamilyIndices
		{

			std::optional<uint32_t> graphicsFamily;
			std::optional<uint32_t>	presentFamily;
			bool isComplete()
			{
				return graphicsFamily.has_value() &&
					presentFamily.has_value();
			}
		};

		struct SwapChainSupportDetails
		{
			VkSurfaceCapabilitiesKHR capabilities{};
			std::vector<VkSurfaceFormatKHR> formats{};
			std::vector<VkPresentModeKHR> presentModes{};
		};

	public:
		//constructor and destructor
		DLL_API VulkanInstance(const WindowsWin& enableWindows);
		DLL_API ~VulkanInstance();

		//no copyable or movable
		DLL_API VulkanInstance(const VulkanInstance&) = delete;
		DLL_API VulkanInstance(VulkanInstance&&) = delete;
		DLL_API VulkanInstance& operator=(const VulkanInstance&) = delete;
		DLL_API VulkanInstance& operator=(VulkanInstance&&) = delete;


		//getters
		DLL_API VkInstance       getInstance() const { return m_VKhandler; }
		DLL_API VkPhysicalDevice getVkPhysicalDevice()const { return m_PhysDeviceHandle; }
		DLL_API VkDevice		 getVkLogicalDevice()const { return m_logicalDevice; }
		DLL_API VkCommandPool	 getCommandPool() const { return m_CommandPool; }
		DLL_API VkQueue          getGraphicsQueue() { return  m_graphicQueue; }
		DLL_API VkQueue          getPresentQueue() { return m_presentQueue; }
		DLL_API VkSurfaceKHR     getSurface() { return m_Surface; }
		DLL_API bool			 getVsync()const { return vsync; }

		//helpers
		DLL_API SwapChainSupportDetails getSwapChainSupport() { return querySwapChainSupport(m_PhysDeviceHandle); }
		DLL_API QueueFamilyIndices findPhysicalQueueFamilies() { return findQueueFamilies(m_PhysDeviceHandle); }
		DLL_API uint32_t findMemoryType(const uint32_t& typeFiler, VkMemoryPropertyFlags properties);
		DLL_API VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
		DLL_API void createBuffers(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer,
			VkDeviceMemory& buffermemory);
		DLL_API VkCommandBuffer	beginSingleTimeCommands();
		DLL_API void endSingleTimeCommands(VkCommandBuffer commandBuffer);
		DLL_API void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
		DLL_API void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, uint32_t layerCount);
		DLL_API void createImageWithInfo(const VkImageCreateInfo& imageInfo, VkMemoryPropertyFlags properties,
			VkImage& image, VkDeviceMemory& imageMemory);

	private:

		VkInstance		 m_VKhandler{};
		VkSurfaceKHR	 m_Surface{};

		VkPhysicalDevice m_PhysDeviceHandle{ VK_NULL_HANDLE }; //where selected graphic card is stored

		VkDevice		 m_logicalDevice{};
		VkQueue			 m_graphicQueue{};
		VkQueue			 m_presentQueue{};

		VkCommandPool	 m_CommandPool{};

		VkPhysicalDeviceProperties m_Properties;

		std::vector<std::string> supportedInstanceExtensions{};
		std::vector<const char*> enabledInstanceExtensions{};

		const std::vector<const char*> validationLayers{ "VK_LAYER_KHRONOS_validation" };
		const std::vector<const char*> deviceExtensions{ VK_KHR_SWAPCHAIN_EXTENSION_NAME };

		static constexpr decltype(VkApplicationInfo::apiVersion) apiVersion{ VK_API_VERSION_1_3 };

		bool		  vsync{ false };
		bool		  enableValidate{ false };



	private:

		VkResult createInstance(bool enableValidation);
		void CreateSurface(const WindowsWin& _Windows);
		void ChoosePhysicalDevice();
		void CreateLogicalDevice(const WindowsWin& _Windows);
		void CreateCommandPool();


		//helper functions
		bool checkValidationLayerSupport();
		bool isDeviceSuitable(VkPhysicalDevice device);
		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
		bool checkDeviceExtensionSupport(VkPhysicalDevice device);
		SwapChainSupportDetails  querySwapChainSupport(const VkPhysicalDevice& device);

	};








}//namespace TDS



#endif//!VULKAN_CREATE_INSTANCE