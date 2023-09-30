#ifndef TDS_VULKAN_PIPELINE
#define TDS_VULKAN_PIPELINE


#include "vulkanTools/vulkanInstance.h"
#include "dotnet/ImportExport.h"
namespace TDS {

	class DLL_API Pipeline {
	public:
		struct PipelineConfiginfo {
			PipelineConfiginfo() = default;
			PipelineConfiginfo(const PipelineConfiginfo&) = delete;
			PipelineConfiginfo& operator= (const PipelineConfiginfo&) = delete;

			std::vector<VkVertexInputBindingDescription>		m_BindingDescriptions{};
			std::vector<VkVertexInputAttributeDescription>		m_AttributeDescriptions{};
			VkPipelineViewportStateCreateInfo					m_ViewportInfo;
			VkPipelineInputAssemblyStateCreateInfo				m_InputAssemblyInfo;
			VkPipelineRasterizationStateCreateInfo				m_RasterizerInfo;
			VkPipelineMultisampleStateCreateInfo				m_MultisampleInfo;
			VkPipelineColorBlendAttachmentState					m_ColorBlendAttachment;
			VkPipelineColorBlendStateCreateInfo					m_ColorBlendInfo;
			VkPipelineDepthStencilStateCreateInfo				m_DepthStencilInfo;
			std::vector<VkDynamicState>							m_DynamicstateEnables;
			VkPipelineDynamicStateCreateInfo					m_DynamicstateInfo;
			VkPipelineLayout									m_PipelineLayout{ nullptr };
			VkRenderPass										m_renderpass{ nullptr };
			uint32_t											m_subpass{ 0 };
		};
		Pipeline(VulkanInstance& Instance, const std::string& VertFilePath, const std::string& FragFilePath, const PipelineConfiginfo& configInfo);
		~Pipeline();

		Pipeline(const Pipeline&) = delete;
		Pipeline& operator=(const Pipeline&) = delete;

		void bind(VkCommandBuffer CommandBuffer);

		static void defaultPipelineConfiginfo(PipelineConfiginfo& configInfo);
		static void enableAlphaBlending(PipelineConfiginfo& configInfo);

	private:
		static std::vector<char>	ReadFile(const std::string& Filepath);

		void						createGraphicPipeline(const std::string& VertFilepath, const std::string& FragFilePath, const PipelineConfiginfo& configInfo);

		void						createShaderModule(const std::vector<char>& code, VkShaderModule* shadermodule);

		VulkanInstance& m_Instance;
		VkPipeline					m_GraphicPipeline;
		VkShaderModule				m_VertShaderModule;
		VkShaderModule				m_FragShaderModule;
	};
}

#endif // !TDS_VULKAN_PIPELINE