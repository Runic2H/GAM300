#include "vulkanTools/Synchronization.h"

namespace TDS
{
	Synchronization::Synchronization(SYNCTYPE synctype_, VkPipelineStageFlags graphicStage) : m_SyncType(synctype_)
	{
		switch (synctype_)
		{
		case(SYNCTYPE::GRAPHIC2COMPUTE):
			m_DstStageMask = VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT;
			m_SrcStageMask = graphicStage;
			break;

		case(SYNCTYPE::COMPUTE2COMPUTE):
			m_SrcStageMask = m_DstStageMask = VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT;
			break;

		case(SYNCTYPE::COMPUTE2GRAPHIC):
			m_DstStageMask = graphicStage;
			m_SrcStageMask = VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT;
			break;

		case(SYNCTYPE::TRANSFER):
			m_DstStageMask = VK_PIPELINE_STAGE_TRANSFER_BIT;
			m_SrcStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
			break;
		case(SYNCTYPE::TRANSFER2):
			m_DstStageMask = VK_PIPELINE_STAGE_TRANSFER_BIT;
			m_SrcStageMask = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
			break;

		case(SYNCTYPE::REVERT1):
			m_DstStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
			m_SrcStageMask = VK_PIPELINE_STAGE_TRANSFER_BIT;
			break;
		}

	}

	void Synchronization::addImageBarrier(SYNCATTACHMENT syncAttachment_, VkImage toSyncImage_, VkImageSubresourceRange subresourceRange_, VkImageLayout oldLayout, VkImageLayout newLayout,
		VkAccessFlags src, VkAccessFlags dst)
	{
		VkImageMemoryBarrier imageMemorybarrier{};
		imageMemorybarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		imageMemorybarrier.newLayout = newLayout;

		//image and subresourcerange should identifyimage subresource accessed
		imageMemorybarrier.image = toSyncImage_;
		imageMemorybarrier.subresourceRange = subresourceRange_;
		imageMemorybarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		imageMemorybarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		imageMemorybarrier.dstAccessMask = dst;
		imageMemorybarrier.oldLayout = oldLayout; //VK_UNDEFINED
		imageMemorybarrier.srcAccessMask = src;

		switch (syncAttachment_)
		{
		case(SYNCATTACHMENT::COLOR):
			imageMemorybarrier.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
			break;

		case(SYNCATTACHMENT::DEPTH):
			imageMemorybarrier.srcAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
			break;
		}


		m_ImageMemoryBarriers.push_back(imageMemorybarrier);

	}

	void Synchronization::addMemoryBarrier(VkAccessFlags syncMemoryAcces)
	{
		VkMemoryBarrier memoryBarrier{};
		memoryBarrier.sType = VK_STRUCTURE_TYPE_MEMORY_BARRIER;
		memoryBarrier.dstAccessMask = syncMemoryAcces;
		memoryBarrier.srcAccessMask = VK_ACCESS_SHADER_WRITE_BIT;

		m_MemoryBarriers.push_back(memoryBarrier);
	}

	void Synchronization::addBufferTransferMemoryBarrier(VkAccessFlags syncMemoryAccessSrc, VkAccessFlags syncMemoryAccessDst, VMABuffer* buffer)
	{
		VkBufferMemoryBarrier buffermemoryBarrier{};
		buffermemoryBarrier.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;

		buffermemoryBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		buffermemoryBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;

		buffermemoryBarrier.srcAccessMask = syncMemoryAccessSrc;
		buffermemoryBarrier.dstAccessMask = syncMemoryAccessDst;


		buffermemoryBarrier.buffer = buffer->GetBuffer();
		buffermemoryBarrier.size = buffer->GetBufferSize();
		buffermemoryBarrier.offset = 0;

		m_BufferMemoryBarriers.push_back(buffermemoryBarrier);
	}

	void Synchronization::syncBarrier(VkCommandBuffer commandbuffer)
	{
		vkCmdPipelineBarrier(
			commandbuffer,
			m_SrcStageMask,					// srcStageMask
			m_DstStageMask,					// dstStageMask
			0,								// dependencyFlags
			m_MemoryBarriers.size(),			// memoryBarrierCount         
			m_MemoryBarriers.data(),			// pMemoryBarriers
			m_BufferMemoryBarriers.size(),	// bufferMemoryBarrierCount
			m_BufferMemoryBarriers.data(),	// pBufferMemoryBarriers
			m_ImageMemoryBarriers.size(),		// imageMemoryBarrierCount
			m_ImageMemoryBarriers.data()		// pImageMemoryBarriers
		);
	}


}