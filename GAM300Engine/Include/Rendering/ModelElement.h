#pragma once
#include "vulkanTools/VMATypes/VMABuffer.h"
namespace TDS
{
	struct ModelElement
	{
		std::shared_ptr<VMABuffer> m_VertexBuffer{nullptr};
		std::shared_ptr<VMABuffer> m_IndexBuffer{nullptr};
		std::uint32_t m_MaterialIndex = 0;
	};
}