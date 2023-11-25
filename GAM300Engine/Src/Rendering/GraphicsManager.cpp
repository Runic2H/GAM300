#include "Rendering/GraphicsManager.h"
#include "vulkanTools/Renderer.h"
#include "vulkanTools/vulkanInstance.h"
#include "vulkanTools/CommandManager.h"
#include "vulkanTools/DirectFrameBuffer.h"
#include "Shader/ShaderLoader.h"
#include "Rendering/Renderer3D.h"
#include "vulkanTools/GlobalBufferPool.h"
#include "vulkanTools/VulkanTexture.h"
#include "vulkanTools/GlobalBufferPool.h"
#include "Rendering/RenderLayer.h"
#include "Rendering/Renderer3D.h"
#include "Rendering/RenderDataManager.h"
#include "Rendering/RenderTarget.h"
#include "Rendering/renderPass.h"
#include "vulkanTools/FrameBuffer.h"
#include "Rendering/Renderer2D.h"
#include "Rendering/FontRenderer.h"
namespace TDS
{
	GraphicsManager::GraphicsManager()
	{
	}
	GraphicsManager::~GraphicsManager()
	{
	}
	void GraphicsManager::Init(WindowsWin* window)
	{
		m_pWindow = window;
		m_MainVkContext = std::make_shared<VulkanInstance>(*m_pWindow);
		m_CommandManager = std::make_shared<CommandManager>();
		ShaderLoader::GetInstance()->DeserializeShaderReflection(REFLECTED_BIN);
		GraphicsAllocator::GetInstance().Init(*m_MainVkContext);
		m_CommandManager->Init();
		m_SwapchainRenderer = std::make_shared<Renderer>(*m_pWindow, *m_MainVkContext);
		DefaultTextures::GetInstance().Init();
		


		Vec3 size = { static_cast<float>(window->getWidth()), static_cast<float>(window->getHeight()), 1.f };
		std::vector<AttachmentInfo> attachmentInfos{};
		std::vector<RenderTarget*> attachments{};
		RenderTargetCI rendertargetCI{
			VK_FORMAT_R8G8B8A8_UNORM,
			VK_IMAGE_ASPECT_COLOR_BIT,
			VK_IMAGE_VIEW_TYPE_2D,
			size,
			VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT,
			VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
			RenderTargetType::COLOR,
			false,
			VK_SAMPLE_COUNT_1_BIT
		};
		RenderTargetCI rendertargetCI2{
			VK_FORMAT_D32_SFLOAT,
			VK_IMAGE_ASPECT_DEPTH_BIT,
			VK_IMAGE_VIEW_TYPE_2D,
			size,
			VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
			VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
			RenderTargetType::DEPTH,
			false,
			VK_SAMPLE_COUNT_1_BIT
		};

		RenderTargetCI rendertargetCI3{
				VK_FORMAT_R32_UINT,
				VK_IMAGE_ASPECT_COLOR_BIT,
				VK_IMAGE_VIEW_TYPE_2D,
				size,
				VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
				VK_IMAGE_LAYOUT_GENERAL,
				RenderTargetType::COLOR,
				false
		};

		m_RenderingAttachment = new RenderTarget(m_MainVkContext, rendertargetCI);
		m_RenderingDepthAttachment = new RenderTarget(m_MainVkContext, rendertargetCI2);
		m_PickAttachment = new RenderTarget(m_MainVkContext, rendertargetCI3);
		attachmentInfos.push_back({ m_RenderingAttachment, VK_ATTACHMENT_LOAD_OP_LOAD , VK_ATTACHMENT_STORE_OP_STORE });
		attachmentInfos.push_back({ m_RenderingDepthAttachment, VK_ATTACHMENT_LOAD_OP_CLEAR, VK_ATTACHMENT_STORE_OP_STORE });
		attachmentInfos.push_back({ m_PickAttachment, VK_ATTACHMENT_LOAD_OP_CLEAR, VK_ATTACHMENT_STORE_OP_STORE });
		attachments.push_back(m_RenderingAttachment);
		attachments.push_back(m_RenderingDepthAttachment);
		attachments.push_back(m_PickAttachment);
		
		m_Renderpass = new RenderPass(m_MainVkContext->getVkLogicalDevice(), attachmentInfos);
		m_Framebuffer = new FrameBuffer(m_MainVkContext->getVkLogicalDevice(), m_Renderpass->getRenderPass(), attachments);
		
		Renderer3D::Init();
		Renderer2D::GetInstance()->Init();
		FontRenderer::GetInstance()->Init();
		m_PointLightRenderer = std::make_unique<PointLightSystem>(*m_MainVkContext);
		m_DebugRenderer = std::make_unique<DebugRenderer>(*m_MainVkContext);
		m_ObjectPicking = std::make_shared<ObjectPick>(m_MainVkContext, size);
		for (auto& renderLayer : m_RenderLayer)
		{
			renderLayer->Setup(m_pWindow);
			renderLayer->Init();
		}
	}
	void GraphicsManager::SetClearColor(Vec4 clearColor)
	{
		m_CurrClearColor = clearColor;
	}
	void GraphicsManager::ToggleViewFrom2D(bool condition)
	{
		m_ViewingFrom2D = condition;
	}
	void GraphicsManager::StartFrame()
	{
		m_FrameHasBegin = true;
		for (auto& renderLayer : m_RenderLayer)
		{
			renderLayer->StartFrame();
		}
		currentCommand = m_SwapchainRenderer->BeginFrame();

	}

	bool GraphicsManager::IsViewingFrom2D()
	{
		return m_ViewingFrom2D;
	}

	void GraphicsManager::AddRenderLayer(RenderLayer* layer)
	{
		m_RenderLayer.push_back(layer);
	}

	void GraphicsManager::EndFrame()
	{
		for (auto& renderLayer : m_RenderLayer)
		{
			renderLayer->StartFrame();
			renderLayer->Render();
		}
		m_SwapchainRenderer->EndFrame();
		m_FrameHasBegin = false;

	}
	void GraphicsManager::ShutDown()
	{

		vkDeviceWaitIdle(m_MainVkContext->getVkLogicalDevice());

		for (auto& renderlayer : m_RenderLayer)
		{
			renderlayer->ShutDown();
		}
		Renderer3D::getInstance()->ShutDown();
		Renderer2D::GetInstance()->ShutDown();
		m_DebugRenderer->GetPipeline().ShutDown();
		FontRenderer::GetInstance()->ShutDown();
		m_ObjectPicking->Shutdown();
		GlobalBufferPool::GetInstance()->Destroy();
		m_RenderingAttachment->~RenderTarget();
		m_RenderingDepthAttachment->~RenderTarget();
		m_Renderpass->~RenderPass();
		m_Framebuffer->~FrameBuffer();
		DefaultTextures::GetInstance().DestroyDefaultTextures();
		m_SwapchainRenderer->ShutDown();
		m_CommandManager->Shutdown();
		RendererDataManager::Destroy();
		GraphicsAllocator::GetInstance().ShutDown();

		m_MainVkContext->ShutDown();
	}
	void GraphicsManager::ResizeFrameBuffer(std::uint32_t width, std::uint32_t height)
	{
	}

	void GraphicsManager::UpdateClearColor()
	{
		std::vector<VkClearAttachment> clearAttachments(2);

		clearAttachments[0].clearValue = {{m_CurrClearColor.x,  m_CurrClearColor.y,  m_CurrClearColor.z,  m_CurrClearColor.w}};
		clearAttachments[0].aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		clearAttachments[0].colorAttachment = 0;
		
		clearAttachments[1].clearValue = { {m_CurrClearColor.x,  m_CurrClearColor.y,  m_CurrClearColor.z,  m_CurrClearColor.w} };
		clearAttachments[1].aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		clearAttachments[1].colorAttachment = 3;

		VkClearRect clearRect{};
		clearRect.layerCount = 1;
		clearRect.baseArrayLayer = 0;
		clearRect.rect.offset = { 0, 0 };
		clearRect.rect.extent = { static_cast<std::uint32_t>(m_Framebuffer->getDimensions().x), static_cast<std::uint32_t>(m_Framebuffer->getDimensions().y)};
		vkCmdClearAttachments(this->currentCommand, static_cast<uint32_t>(clearAttachments.size()), clearAttachments.data(), 1, &clearRect);

	}
	void GraphicsManager::setCamera(TDSCamera& camera)
	{
		m_Camera = &camera;
	}
	WindowsWin* GraphicsManager::GetWindow()
	{
		return m_pWindow;
	}
	std::uint32_t GraphicsManager::PickedObject()
	{
		return m_ObjectPicking->getActiveObject();
	}
	void GraphicsManager::SetLayerToRender(int ID)
	{
		m_LayerID = ID;
	}
	bool GraphicsManager::RenderAllLayer()
	{
		return m_RenderAllLayer;
	}
	void GraphicsManager::ToggleRenderAllLayer(bool condition)
	{
		m_RenderAllLayer = condition;
	}
	int GraphicsManager::LayerToRender()
	{
		return m_LayerID;
	}
	TDSCamera& GraphicsManager::GetCamera()
	{
		return *m_Camera;
	}
	//std::shared_ptr<DirectFrameBuffer> GraphicsManager::GetMainFrameBuffer()
	//{
	//	return m_MainFrameBuffer;
	//}
	VkCommandBuffer& GraphicsManager::getCommandBuffer()
	{
		return currentCommand;
	}
	Renderer& GraphicsManager::GetSwapchainRenderer()
	{
		return *m_SwapchainRenderer;
	}
	CommandManager& GraphicsManager::getCommandManager()
	{
		return *m_CommandManager;
	}
	VulkanInstance& GraphicsManager::getVkInstance()
	{
		return *m_MainVkContext;
	}
	std::shared_ptr<VulkanInstance> GraphicsManager::getVkInstancePtr()
	{
		return m_MainVkContext;
	}
	GraphicsManager& GraphicsManager::getInstance()
	{
		if (m_Instance == nullptr)
		{
			m_Instance = std::make_shared<GraphicsManager>();
		}
		return *m_Instance;
	}
	ObjectPick& GraphicsManager::getObjectPicker()
	{
		return *this->m_ObjectPicking;
	}
}