#pragma once
#include <pch.h>
#include "dotnet/ImportExport.h"
#include "vulkan/vulkan.h"
#include "camera/camera.h"
#include "vulkanTools/PointLightSystem.h"
#include "camera/Camerasystem/CameraSystem.h"
#include "DebugRenderer.h"

namespace TDS
{

	class WindowsWin;
	class VulkanInstance;
	class Renderer;
	class CommandManager;
	class RenderLayer;
	class RenderTarget;
	class RenderPass;
	class FrameBuffer;
	class PointLightSystem;
	class DLL_API GraphicsManager
	{
	private:
		std::shared_ptr<VulkanInstance>			m_MainVkContext;
		std::shared_ptr<Renderer>				m_SwapchainRenderer;
		std::shared_ptr<CommandManager>			m_CommandManager;
		std::vector<RenderLayer*>				m_RenderLayer;
		TDSCamera*								m_Camera = nullptr;
		VkCommandBuffer							currentCommand = nullptr;
		WindowsWin*								m_pWindow = nullptr;
		RenderTarget*							m_RenderingAttachment{ nullptr };
		RenderTarget*							m_RenderingDepthAttachment{ nullptr };
		RenderPass*								m_Renderpass{ nullptr };
		FrameBuffer*							m_Framebuffer{ nullptr };
		bool									m_ViewingFrom2D = false;

	public:
		inline static std::shared_ptr<GraphicsManager> m_Instance;
		GraphicsManager();
		~GraphicsManager();

		void								ToggleViewFrom2D(bool condition);
		bool								IsViewingFrom2D();
				
		void								AddRenderLayer(RenderLayer* layer);
		void								Init(WindowsWin* window);
		void								StartFrame();
		void								EndFrame();
		void								ShutDown();
		void								ResizeFrameBuffer(std::uint32_t width, std::uint32_t height);
		void								setCamera(TDSCamera& camera);
		std::shared_ptr<VulkanInstance>		getVkInstancePtr();

		WindowsWin*							GetWindow();
		
		

		TDSCamera& GetCamera();

		VkCommandBuffer& getCommandBuffer();
		Renderer& GetSwapchainRenderer();
		VulkanInstance& getVkInstance();
		CommandManager& getCommandManager();
		static GraphicsManager& getInstance();
		RenderTarget& getFinalImage() { return *m_RenderingAttachment; }
		FrameBuffer& getFrameBuffer() { return *m_Framebuffer; }
		RenderPass& getRenderPass() { return *m_Renderpass; }
		std::unique_ptr<PointLightSystem> m_PointLightRenderer;
		std::unique_ptr<DebugRenderer> m_DebugRenderer;
	};


}