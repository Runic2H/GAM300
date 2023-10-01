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

	class DLL_API VulkanSwapChain
	{

	public:
		//frames processed concurrently
		static constexpr int MAX_FRAMES_IN_FLIGHT{ 2 };	//maybe set as a macro, will see

		//constructor and destructor
		VulkanSwapChain(VulkanInstance& Instance, VkExtent2D WindowExtent);
		VulkanSwapChain(VulkanInstance& Instance, VkExtent2D WindowExtent, std::shared_ptr<VulkanSwapChain> prev);
		~VulkanSwapChain();

		//no copy constructor
		VulkanSwapChain(const VulkanSwapChain&) = delete;
		VulkanSwapChain& operator=(const VulkanSwapChain&) = delete;

		//getters
		VkFramebuffer				getFrameBuffer(int Index)		{ return m_vSwapChainFramebuffers[Index]; }
		VkRenderPass				getRenderPass()					{ return m_RenderPass; }
		VkImageView					getImageView(int Index)			{ return m_vSwapChainImageViews[Index]; }
		size_t						getImageCount()					{ return m_vSwapChainImages.size(); }
		VkFormat					getSwapChainImageFormat()		{ return m_SwapChainImageFormat; }
		VkExtent2D					getSwapChainExtent()			{ return m_SwapChainExtent; }
		uint32_t					width()							{ return m_SwapChainExtent.width; }
		uint32_t					height()						{ return m_SwapChainExtent.height; }
		std::vector	<VkImageView>	getImageViewContainer()const	{ return m_vSwapChainImageViews; }
		float						extentAspectRatio() {
			return static_cast<float>(m_SwapChainExtent.width) / static_cast<float>(m_SwapChainExtent.height);
		}

		VkFormat findDepthFormat();

		VkResult acquireNextImage(uint32_t* imageIndex);
		VkResult SubmitCommandBuffers(const VkCommandBuffer* Buffers, uint32_t* ImageIndex);

		bool compareSwapFormat(const VulkanSwapChain& SwapChain) const {
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