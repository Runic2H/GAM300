#pragma once
#include "vulkanTools/VMATypes/VMABuffer.h"
namespace TDS
{

	struct UBO
	{
		std::shared_ptr<VMABuffer> m_Buffer{};
		VkDescriptorBufferInfo m_BufferInfo;
	};

	struct BufferInfo
	{
		size_t m_Size;
		void* m_Data = nullptr;
		bool m_Shared = false;
	};



}