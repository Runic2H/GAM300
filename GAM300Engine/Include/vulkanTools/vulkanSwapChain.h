/*!*************************************************************************
****
\file vulkanSwapChain.h
\author Ng Zuo Xian Amadeus
\par DP email: ng.z@digipen.edu
\par Course: CSD3400
\par Section: a
\date 22-9-2023
\brief  Contains the vulkanSwapChain Class and its member functions
****************************************************************************
***/
#ifndef VULKAN_SWAP_CHAIN
#define VULKAN_SWAP_CHAIN

//#include <iostream>
//#include <stdlib.h>
#include <string>
//#include <assert.h>
//#include <stdio.h>
#include <vector>

//#define	VK_USE_PLATFORM_WIN32_KHR
#include "vulkanInstance.h"
#include "dotnet/ImportExport.h"

namespace TDS
{

	class VulkanSwapChain
	{

	public:
		//frames processed concurrently
		DLL_API static constexpr int MAX_FRAMES_IN_FLIGHT{ 2 };	//maybe set as a macro, will see

		//constructor and destructor
		DLL_API VulkanSwapChain(VulkanInstance& Instance, VkExtent2D WindowExtent);
		DLL_API VulkanSwapChain(VulkanInstance& Instance, VkExtent2D WindowExtent, std::shared_ptr<VulkanSwapChain> prev);
		DLL_API ~VulkanSwapChain();

		//no copy constructor
		DLL_API VulkanSwapChain(const VulkanSwapChain&) = delete;
		DLL_API VulkanSwapChain& operator=(const VulkanSwapChain&) = delete;

		//getters
		DLL_API VkFramebuffer				getFrameBuffer(int Index)		{ return m_vSwapChainFramebuffers[Index]; }
		DLL_API VkRenderPass				getRenderPass()					{ return m_RenderPass; }
		DLL_API VkImageView					getImageView(int Index)			{ return m_vSwapChainImageViews[Index]; }
		DLL_API size_t						getImageCount()					{ return m_vSwapChainImages.size(); }
		DLL_API VkFormat					getSwapChainImageFormat()		{ return m_SwapChainImageFormat; }
		DLL_API VkExtent2D					getSwapChainExtent()			{ return m_SwapChainExtent; }
		DLL_API uint32_t					width()							{ return m_SwapChainExtent.width; }
		DLL_API uint32_t					height()						{ return m_SwapChainExtent.height; }
		DLL_API std::vector	<VkImageView>	getImageViewContainer()const	{ return m_vSwapChainImageViews; }
		DLL_API float						extentAspectRatio() {
			return static_cast<float>(m_SwapChainExtent.width) / static_cast<float>(m_SwapChainExtent.height);
		}

		DLL_API VkFormat findDepthFormat();

		DLL_API VkResult acquireNextImage(uint32_t* imageIndex);
		DLL_API VkResult SubmitCommandBuffers(const VkCommandBuffer* Buffers, uint32_t* ImageIndex);

		DLL_API bool compareSwapFormat(const VulkanSwapChain& SwapChain) const {
			return SwapChain.m_SwapChainDepthFormat == m_SwapChainDepthFormat && SwapChain.m_SwapChainImageFormat == m_SwapChainImageFormat;
		}


	private:
		//helper functions
		void init();
		void CreateSwapChain();
		void CreateImageViews();
		void CreateDepthResource();
		void CreateRenderPass();
		void CreateFrameBuffers();
		void CreateSyncObjects();

		VkSurfaceFormatKHR	ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR	ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentMode);
		VkExtent2D			ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

		VkFormat							m_SwapChainImageFormat;
		VkFormat							m_SwapChainDepthFormat;
		VkExtent2D							m_SwapChainExtent;

		std::vector<VkFramebuffer>			m_vSwapChainFramebuffers;
		VkRenderPass						m_RenderPass;

		std::vector<VkImage>				m_vDepthImages;
		std::vector<VkDeviceMemory>			m_vDepthImageMemory;
		std::vector<VkImageView>			m_vDepthImageViews;
		std::vector<VkImage>				m_vSwapChainImages;
		std::vector<VkImageView>			m_vSwapChainImageViews;

		VulkanInstance& m_Instance;
		VkExtent2D							m_WindowExtent;

		VkSwapchainKHR						m_SwapChain;
		std::shared_ptr<VulkanSwapChain>	m_OldSwapChain;

		std::vector<VkSemaphore>			m_vImageAvailableSemaphore;
		std::vector<VkSemaphore>			m_vRenderFinishedSemaphore;
		std::vector<VkFence>				m_vInFlightFences;
		std::vector<VkFence>				m_vImagesinFlight;
		size_t								m_currentFrame{ 0 };

		VkInstance instance;
		VkDevice device;
		VkPhysicalDevice physicalDevice;
		VkSurfaceKHR surface;
	};

}



#endif//!VULKAN_SWAP_CHAIN