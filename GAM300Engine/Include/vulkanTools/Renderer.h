/*!*************************************************************************
****
\file Renderer.h
\author Ng Zuo Xian Amadeus
\par DP email: ng.z@digipen.edu
\par Course: CSD3400
\par Section: a
\date 22-9-2023
\brief  Contains the Renderer Class and its member functions
****************************************************************************
***/
#ifndef TDS_VULKAN_RENDERER
#define TDS_VULKAN_RENDERER

#include "vulkanInstance.h"
#include "vulkanSwapChain.h"
#include "windowswindow.h"

namespace TDS {
	class Renderer {
	public:
		//Constructor and Destructor
		DLL_API Renderer(WindowsWin& window, VulkanInstance& instance);
		DLL_API ~Renderer();

		//no copy constructor
		Renderer(const Renderer&) = delete;
		Renderer& operator=(const Renderer&) = delete;

		//Getters
		DLL_API VkRenderPass				getSwapChainRenderPass() const { return m_SwapChain->getRenderPass(); }
		DLL_API float						getAspectRatio() const { return m_SwapChain->extentAspectRatio(); }
		DLL_API bool						isFrameInProgress() const { return m_isFrameStarted; }
		DLL_API VkImageView					getImageView(uint32_t val)const { return m_SwapChain->getImageView(val); }
		DLL_API std::vector	<VkImageView>	getImageViewContainer()const { return m_SwapChain->getImageViewContainer(); }
		DLL_API VkCommandBuffer				getCurrentCommandBuffer() const {
			assert(m_isFrameStarted && "Cannot get commandbuffer when frame not in progress");
			return m_vCommandBuffers[m_currentFrameIndex];
		}

		DLL_API int							getFrameIndex() const {
			assert(m_isFrameStarted && "Cannot get Frame index when frame not in progress");
			return m_currentFrameIndex;
		}

		//these functions tell tell when to begin and end the frame and renderpass
		DLL_API VkCommandBuffer BeginFrame();
		DLL_API void EndFrame();
		DLL_API void BeginSwapChainRenderPass(VkCommandBuffer commandbuffer);
		DLL_API void EndSwapChainRenderPass(VkCommandBuffer commandbuffer);

	private:
		//helper functions
		void createCommandBuffers();
		void freeCommandBuffers();
		void recreateSwapChain();

		WindowsWin& m_Window;
		VulkanInstance& m_Instance;
		std::unique_ptr<VulkanSwapChain>	m_SwapChain;
		std::vector<VkCommandBuffer>		m_vCommandBuffers;

		uint32_t							m_currentImageIndex;
		int									m_currentFrameIndex{ 0 };
		bool								m_isFrameStarted{ false };
	};
}

#endif //!TDS_VULKAN_RENDERER