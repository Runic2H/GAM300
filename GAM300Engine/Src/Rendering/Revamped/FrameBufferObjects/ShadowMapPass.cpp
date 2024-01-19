#include "Rendering/Revamped/FrameBufferObjects/ShadowMapPass.h"
#include "Rendering/GraphicsManager.h"
namespace TDS
{

    ShadowMapPass::ShadowMapPass(Vec2 DimensionInput) :m_ShadowDepth()
    {
        m_Resizeable = true;
        m_AutoSync = true;
        m_TargetSwapchain = false;
        m_SampleCnt = VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT;
        m_FrameBufferDimension = DimensionInput;
        m_FBOType = FBO_TYPE::SHADOW;


        m_ShadowDepth = RenderTargetCI(VK_FORMAT_D32_SFLOAT,
            VK_IMAGE_ASPECT_DEPTH_BIT,
            VK_IMAGE_VIEW_TYPE_2D,
            m_FrameBufferDimension,
            VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
            VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
            RenderTargetType::DEPTH,
            false,
            VK_SAMPLE_COUNT_1_BIT);




    }
    bool ShadowMapPass::Create()
    {
        GraphicsManager& mgr = GraphicsManager::getInstance();
        std::shared_ptr<VulkanInstance> instance = mgr.getVkInstancePtr();

        m_DepthTarget = new RenderTarget(instance, m_ShadowDepth);

        std::vector<AttachmentInfo> attachInfo;
        auto& depthAttach = attachInfo.emplace_back();
        depthAttach.loadOP = VK_ATTACHMENT_LOAD_OP_CLEAR;
        depthAttach.framebufferAttachment = m_DepthTarget;
        depthAttach.storeOP = VK_ATTACHMENT_STORE_OP_STORE;
        depthAttach.stencilLoadOP = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        depthAttach.stencilStoreOP = VK_ATTACHMENT_STORE_OP_DONT_CARE;

        m_RenderTargets.emplace_back(m_DepthTarget);

        m_VKRenderPass = new RenderPass(instance->getVkLogicalDevice(), attachInfo);
        m_FrameBufferHdl = new FrameBuffer(instance->getVkLogicalDevice(), m_VKRenderPass->getRenderPass(), m_RenderTargets);

        return true;
    }

    bool ShadowMapPass::Resize(std::uint32_t width, std::uint32_t height)
    {
        Destroy();
        m_FrameBufferDimension = Vec2(float(width), float(height));
        return Create();
    }
    void ShadowMapPass::InitResizeFunctionPointer()
    {
        if (m_Resizeable)
        {
            RecreateFunc = [this](std::uint32_t Width, std::uint32_t Height) -> bool
            {
                return Resize(Width, Height);
            };
        }

        DestroyFunc = [&]() -> void
        {
            Destroy();
        };

        BlendAttachmentGettor = [&](BlendContainer& blendCont, PipelineCreateEntry& createEntry) -> void
        {
            return GetBlendAttachments(blendCont, createEntry);
        };
    }
    void ShadowMapPass::Destroy()
    {
        if (m_VKRenderPass)
            delete m_VKRenderPass;
        if (m_FrameBufferHdl)
            delete m_FrameBufferHdl;
        if (m_DepthTarget)
            delete m_DepthTarget;
        for (auto& target : m_RenderTargets)
        {
            if (target)
                delete target;
        }
    }
    void ShadowMapPass::GetBlendAttachments(BlendContainer& blendCont, PipelineCreateEntry& createEntry)
    {
    }

}