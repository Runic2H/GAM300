#pragma once
#include <vulkan/vulkan.h>
#include "dotnet/ImportExport.h"
#include "vma/vk_mem_alloc.h"

namespace TDS
{
	class VulkanInstance;

	class DLL_API VMABuffer
	{
	public:
		VMABuffer();
		~VMABuffer();

		void* Map();
		void UnMap();
		void  CreateBuffer(std::uint64_t size, VkBufferUsageFlags bufferUsage, std::int32_t VmaUsage, void* data = nullptr);
		static VMABuffer CreateStagingBuffer(size_t size, VulkanInstance& instance, void* data = nullptr);

		void  MappedStaging(size_t size, VkBufferUsageFlags usage, VulkanInstance& instance, void* data);
		void  MapData(const void* data, size_t size, std::uint32_t offset = 0);
		void  ReadData(void* data, size_t size, std::uint32_t offset = 0);
		void  DestroyBuffer();

		size_t GetBufferSize() const;
		const VkBuffer& GetBuffer();

		const std::uint32_t& getDataCount();
		void CreateVertexBuffer(size_t size, bool is_static, void* data = nullptr);
		void UpdateVertexData(void* data, size_t size, std::uint32_t offset = 0);

		void CreateIndexBuffer(size_t indexCnt, bool is_static, std::uint32_t* indices = 0);
		void UpdateIndexData(std::uint32_t* indices, size_t indexCnt, std::uint32_t offset = 0);

		void SetDataCnt(std::uint32_t cnt);
	private:
		void* m_MappedMemory = nullptr;
		VkBuffer m_Buffer = nullptr;
		VmaAllocation m_Allocation = nullptr;
		size_t m_BufferSize = 0;
		std::uint32_t m_DataCnt = 0;
	};


}