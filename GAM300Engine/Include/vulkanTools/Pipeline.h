/*!*************************************************************************
****
\file Pipeline.h
\author Ng Zuo Xian Amadeus
\par DP email: ng.z@digipen.edu
\par Course: CSD3400
\par Section: a
\date 22-9-2023
\brief  Contains the Pipeline Class and its member functions
****************************************************************************
***/
#ifndef TDS_VULKAN_PIPELINE
#define TDS_VULKAN_PIPELINE


#include "vulkanTools/vulkanInstance.h"
#include "dotnet/ImportExport.h"
namespace TDS {

	class DLL_API Pipeline {
	public:
		struct PipelineConfiginfo {
			//default constructor with no copy constructor
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
		//constructor and destructor of Pipeline Class
		Pipeline(VulkanInstance& Instance, const std::string& VertFilePath, const std::string& FragFilePath, const PipelineConfiginfo& configInfo);
		~Pipeline();

		//no copy constructor
		Pipeline(const Pipeline&) = delete;
		Pipeline& operator=(const Pipeline&) = delete;

		//binds the pipeline to the commandbuffer
		void bind(VkCommandBuffer CommandBuffer);

		//default settings for the pipelineconfig
		static void defaultPipelineConfiginfo(PipelineConfiginfo& configInfo);
		//settings for alphablending
		static void enableAlphaBlending(PipelineConfiginfo& configInfo);

		//reads a text file and converts it into a vector of string
		static std::vector<char>	ReadFile(const std::string& Filepath);
		//creates a shadermodule from the code stored as a vector of string
		void						createShaderModule(const std::vector<char>& code, VkShaderModule* shadermodule);
	private:
		//creates a graphic pipeline

		void						createGraphicPipeline(const std::string& VertFilepath, const std::string& FragFilePath, const PipelineConfiginfo& configInfo);


		VulkanInstance& m_Instance;
		VkPipeline					m_GraphicPipeline;
		VkShaderModule				m_VertShaderModule;
		VkShaderModule				m_FragShaderModule;
	};
}

#endif // !TDS_VULKAN_PIPELINE