#pragma once
#include "vulkanTools/GraphicsAllocator.h"
#include "GraphicsResource/GraphicsResourceDefines.h"
#include "dotnet/ImportExport.h"
namespace TDS
{
	//Dear Xing Xiang, please ignore this and use ur frame buffer class with my pipeline. THis is just for to test my pipeline

	//THIS IS FOR DIRECT RENDERING



	struct AttachmentSetting
	{
		VkFormat			m_Format;
		iColor				m_ClearColor = Vec4(0.0f, 0.0f, 0.0f, 1.0f);
		bool				m_ClearOp = true;;

	};

	struct FrameBufferEntryInfo
	{
		VkFilter						m_Filter = VkFilter::VK_FILTER_NEAREST;
		VkExtent2D						m_AreaDimension;
		std::vector<AttachmentSetting>	m_AttachmentRequirememnts;

	};


	struct FBAttachment
	{
		VkImage					m_Image;
		VmaAllocation			m_Allocation;
		VkImageView				m_View;
		VkDescriptorImageInfo	m_ImageInfo;
	};



	class DirectFrameBuffer;
	class DLL_API FrameBuffer
	{
	public:
		virtual bool									Init(FrameBufferEntryInfo& entryInfo) = 0;
		virtual void									Destroy() = 0;
		virtual bool									CreateFrameBuffer(std::uint32_t width, std::uint32_t height) = 0;

	public:
		void											Resize(VkExtent2D newExtent);
		void											SetClearColor(const iColor& color);
		void											CreateSampler(VkFilter filter);
		void											DestroyAttachment(FBAttachment& fbAttachmnet);

		void											CreateAttachment(VkFormat format, FBAttachment& attachment, VkExtent2D extent, VkSampleCountFlagBits sampleCnt,
														VkImageUsageFlags usage, VkImageAspectFlags imageAspect);
		
		void											CreateRenderPass(VkRenderPass& output, VkFormat clrFormat, VkFormat depthFormat, VkSampleCountFlagBits sampleCnt,
														std::uint32_t numOfAttachments, std::uint32_t numOfResolveAttachments = 0, std::uint32_t numOfDepthAttachments = 1);
		//Getters
		FBAttachment&									GetDepthAttachment();

		const std::uint32_t								GetNumberOfAttachments() const;
		VkRenderPass									GetRenderPass()			 const;
		VkFramebuffer									GetCurrentFrameBuffer()  const;
		VkFramebuffer									GetFrameBuffer(std::uint32_t index)  const;
		std::vector<VkClearValue>&						GetClearValues();
		std::vector<VkClearAttachment>&					GetClearAttachments();
		FrameBufferEntryInfo&							getFBEntryInfo();

	protected:
		FrameBufferEntryInfo							m_Entry{};
		VkSampler										m_Sampler = nullptr;
		VkRenderPass									m_RenderPass = nullptr;
		VkFormat										m_ColorFormat,
			m_DepthFormat;
		std::uint32_t									m_FrameIndex = 0;
		FBAttachment									m_DepthAttachment;
		std::vector<VkFramebuffer>						m_FrameBuffers;
		std::vector<VkClearAttachment>					m_ClearAttachments;
		std::vector<VkClearValue>						m_ClearValues;
		std::vector<FBAttachment>						m_Attachments;
		//Ignore this unless you dont multisampling + offscreen
		std::vector<FBAttachment>						m_ResolveAttachment;
		std::unordered_map<std::string, std::uint32_t>	m_AttachmentNameMap;

	};

}