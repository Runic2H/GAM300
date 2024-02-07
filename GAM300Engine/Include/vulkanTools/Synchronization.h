#ifndef SYNCHRONIZATION
#define SYNCHRONIZATION
#include "VMATypes/VMABuffer.h"
#include "dotnet/ImportExport.h"

namespace TDS
{
	enum class SYNCATTACHMENT
	{
		NONE = 0,
		DEPTH,
		COLOR
	};

	enum class SYNCTYPE
	{
		COMPUTE2COMPUTE,
		COMPUTE2GRAPHIC,
		GRAPHIC2COMPUTE,
		TRANSFER,
		TRANSFER2,
		REVERT1
		//DEBUGBARRIER -- not sure if needed
	};

	//sync y
	class DLL_API Synchronization
	{
	public:

		Synchronization(const Synchronization&) = delete;
		Synchronization& operator=(const Synchronization&) = delete;

		Synchronization(SYNCTYPE synctype_, VkPipelineStageFlags graphicStage = 0);
		void addImageBarrier(SYNCATTACHMENT syncAttachment_, VkImage toSyncImage_, VkImageSubresourceRange subresourceRange_, VkImageLayout oldLayout, VkImageLayout newLayout, VkAccessFlags src, VkAccessFlags dst);
		void addMemoryBarrier(VkAccessFlags syncMemoryAcces);
		void addBufferTransferMemoryBarrier(VkAccessFlags syncMemoryAccessSrc, VkAccessFlags syncMemoryAccessDst, VMABuffer* buffer);
		void syncBarrier(VkCommandBuffer commandbuffer);
		void clearBarrier() { m_MemoryBarriers.clear(); m_ImageMemoryBarriers.clear(); }

	private:

		VkPipelineStageFlags m_SrcStageMask{};
		VkPipelineStageFlags m_DstStageMask{};
		std::vector<VkMemoryBarrier> m_MemoryBarriers;
		std::vector<VkBufferMemoryBarrier> m_BufferMemoryBarriers;
		std::vector<VkImageMemoryBarrier> m_ImageMemoryBarriers;
		SYNCTYPE m_SyncType;


	};


}//END of TDS


#endif // !SYNCHRONIZATION
