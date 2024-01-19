#pragma once
#include "FBOInternal.h"

namespace TDS
{
	//This implementation here uses omni shadow mapping which will map shadows for lighting in all direction.
	//I might just use my own FB creation here for more control.

	struct AttachmentImage
	{
		VkImage							m_Image = nullptr;
		VkImageView						m_DepthView = nullptr;
		VmaAllocation					m_Allocation = nullptr;
	};

	class VulkanTexture;

	class OmniShadowPass : public FrameBufferObjectInternal<OmniShadowPass>
	{
	private:
		VkFormat							m_ValidDepth{};
		VkRenderPass						m_Renderpass = nullptr;
		std::shared_ptr<VulkanTexture>		m_CubeMapImage = nullptr;
		AttachmentImage						m_DepthImage{};
		std::array<VkFramebuffer, 6>		m_CubeMapFrameBuffers{};


		void	PrepareRenderPass(VkRenderPass& renderpass);
		void	PrepareCubeMapTexture();
	public:
		OmniShadowPass(Vec2 DimensionInput);

		bool	Create();
		bool	Resize(std::uint32_t width, std::uint32_t height);
		void	Destroy();
		void	InitResizeFunctionPointer();

		CREATE_GETTOR(DepthImage, AttachmentImage);

		void	GetBlendAttachments(BlendContainer& blendCont, PipelineCreateEntry& createEntry);

	};




}