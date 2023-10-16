#pragma once
#include "vulkanTools/VulkanPipeline.h"
namespace TDS
{
	struct MaterialMetaData
	{
		std::string							m_MaterialName = "";
		std::uint32_t						m_MaterialIndex = 0;
		PipelineCreateEntry					m_PipelineCreateEntry;
	};

	class Material
	{
		public:
			Material();
			~Material();

			void							Serialize(std::string_view Path, bool isRead = false);
			std::shared_ptr<VulkanPipeline> GetPipeline();
			const MaterialMetaData&			GetMaterialInfo() const;

			void							SetCommandBuffer(VkCommandBuffer cmd);
			VkCommandBuffer					GetCommandBuffer();
			void							Draw(std::shared_ptr<VMABuffer>& vertexBuffer, std::uint32_t instance = 1);
			void							DrawIndexed(std::shared_ptr<VMABuffer>& vertexBuffer, std::shared_ptr<VMABuffer>& indexBuffer, std::uint32_t instance = 1);
			void							SubmitPushConstant(void* data, size_t size, SHADER_FLAG flag);
			void							UpdateBuffer(size_t size, void* data, std::string_view BindingName, std::uint32_t offset = 0);
			void							UpdateTexture(std::shared_ptr<VulkanTexture>& texture, std::string_view BindingName);
			void							UpdateTextureArray(const std::vector<std::shared_ptr<VulkanTexture>>& textureArray, std::string_view BindingName);
		private:
			MaterialMetaData				m_Material;
			std::shared_ptr<VulkanPipeline> m_Pipeline = nullptr;
	};
}