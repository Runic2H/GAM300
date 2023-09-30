#ifndef TDS_VULKAN_RENDERER
#define TDS_VULKAN_RENDERER

#include "vulkanInstance.h"
#include "vulkanSwapChain.h"
#include "windowswindow.h"

namespace TDS {
	class DLL_API Renderer {
	public:
		Renderer(WindowsWin& window, VulkanInstance& instance);
		~Renderer();

		Renderer(const Renderer&) = delete;
		Renderer& operator=(const Renderer&) = delete;

		VkRenderPass getSwapChainRenderPass() const { return m_SwapChain->getRenderPass(); }
		float getAspectRatio() const { return m_SwapChain->extentAspectRatio(); }
		bool isFrameInProgress() const { return m_isFrameStarted; }
		VkImageView getImageView(uint32_t val)const { return m_SwapChain->getImageView(val); }
		std::vector	<VkImageView> getImageViewContainer()const { return m_SwapChain->getImageViewContainer(); }
		VkCommandBuffer getCurrentCommandBuffer() const {
			assert(m_isFrameStarted && "Cannot get commandbuffer when frame not in progress");
			return m_vCommandBuffers[m_currentFrameIndex];
		}

		int getFrameIndex() const {
			assert(m_isFrameStarted && "Cannot get Frame index when frame not in progress");
			return m_currentFrameIndex;
		}

		VkCommandBuffer BeginFrame();
		void EndFrame();
		void BeginSwapChainRenderPass(VkCommandBuffer commandbuffer);
		void EndSwapChainRenderPass(VkCommandBuffer commandbuffer);

	private:
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