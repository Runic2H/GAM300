/*!*************************************************************************
****
\file Pipeline.cpp
\author Ng Zuo Xian Amadeus
\par DP email: ng.z@digipen.edu
\par Course: CSD3400
\par Section: a
\date 22-9-2023
\brief  Function definitions of the Pipeline Class
****************************************************************************
***/
#include "vulkanTools/Pipeline.h"
#include "vulkanTools/Model.h"
#ifndef SHADER_DIR
#define SHADER_DIR "../assets/shaders/"
#endif // !SHADER_DIR

namespace TDS {
	//Pipeline constructor
	Pipeline::Pipeline(VulkanInstance& Instance, const std::string& VertFilePath, const std::string& FragFilePath, const PipelineConfiginfo& configInfo) :m_Instance(Instance) {
		createGraphicPipeline(VertFilePath, FragFilePath, configInfo);
	}

	//Pipeline Destructor
	Pipeline::~Pipeline() {
		vkDestroyShaderModule(m_Instance.getVkLogicalDevice(), m_VertShaderModule, nullptr);
		vkDestroyShaderModule(m_Instance.getVkLogicalDevice(), m_FragShaderModule, nullptr);
		vkDestroyPipeline(m_Instance.getVkLogicalDevice(), m_GraphicPipeline, nullptr);
	}

	//converts textfile into vector of chars
	std::vector<char> Pipeline::ReadFile(const std::string& Filepath) {
		std::string Path = SHADER_DIR + Filepath;
		std::ifstream file(Path, std::ios::ate | std::ios::binary);

		if (!file.is_open()) throw std::runtime_error("failed to open file at " + Path);

		size_t Filesize = static_cast<size_t>(file.tellg());
		std::vector<char> buffer(Filesize);

		file.seekg(0);
		file.read(buffer.data(), Filesize);

		file.close();
		return buffer;
	}

	//create graphiccs pipeline
	void Pipeline::createGraphicPipeline(const std::string& VertFilePath, const std::string& FragFilePath, const PipelineConfiginfo& configInfo) {
		assert(configInfo.m_PipelineLayout != VK_NULL_HANDLE && "Cannot create graphic pipeline: no pipelinelayout provided in configInfo");
		assert(configInfo.m_renderpass != VK_NULL_HANDLE && "Cannot create graphics pipeline: no RenderPass provided in configInfo");

		auto vertcode = ReadFile(VertFilePath);
		auto fragcode = ReadFile(FragFilePath);

		createShaderModule(vertcode, &m_VertShaderModule);
		createShaderModule(fragcode, &m_FragShaderModule);

		VkPipelineShaderStageCreateInfo Shaderstages[2]; //0 for vert, 1 for frag, more to come??
		Shaderstages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		Shaderstages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
		Shaderstages[0].module = m_VertShaderModule;
		Shaderstages[0].pName = "main";
		Shaderstages[0].flags = 0;
		Shaderstages[0].pNext = nullptr;
		Shaderstages[0].pSpecializationInfo = nullptr;

		Shaderstages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		Shaderstages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
		Shaderstages[1].module = m_FragShaderModule;
		Shaderstages[1].pName = "main";
		Shaderstages[1].flags = 0;
		Shaderstages[1].pNext = nullptr;
		Shaderstages[1].pSpecializationInfo = nullptr;

		auto& BindingDescription = configInfo.m_BindingDescriptions;
		auto& AttributeDescription = configInfo.m_AttributeDescriptions;

		VkPipelineVertexInputStateCreateInfo VertexInputInfo{};
		VertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		VertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(AttributeDescription.size());
		VertexInputInfo.vertexBindingDescriptionCount = static_cast<uint32_t>(BindingDescription.size());
		VertexInputInfo.pVertexAttributeDescriptions = AttributeDescription.data();
		VertexInputInfo.pVertexBindingDescriptions = BindingDescription.data();

		VkGraphicsPipelineCreateInfo PipelineInfo{};
		PipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		PipelineInfo.stageCount = 2;
		PipelineInfo.pStages = Shaderstages;
		PipelineInfo.pVertexInputState = &VertexInputInfo;
		PipelineInfo.pInputAssemblyState = &configInfo.m_InputAssemblyInfo;
		PipelineInfo.pViewportState = &configInfo.m_ViewportInfo;
		PipelineInfo.pRasterizationState = &configInfo.m_RasterizerInfo;
		PipelineInfo.pMultisampleState = &configInfo.m_MultisampleInfo;
		PipelineInfo.pColorBlendState = &configInfo.m_ColorBlendInfo;
		PipelineInfo.pDepthStencilState = &configInfo.m_DepthStencilInfo;
		PipelineInfo.pDynamicState = &configInfo.m_DynamicstateInfo;

		PipelineInfo.layout = configInfo.m_PipelineLayout;
		PipelineInfo.renderPass = configInfo.m_renderpass;
		PipelineInfo.subpass = configInfo.m_subpass;

		PipelineInfo.basePipelineIndex = -1;
		PipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

		if (vkCreateGraphicsPipelines(m_Instance.getVkLogicalDevice(), VK_NULL_HANDLE, 1, &PipelineInfo, nullptr, &m_GraphicPipeline) != VK_SUCCESS)
			throw std::runtime_error("failed to create graphic pipeline");
	}

	//create shader module using a vector of chars
	void Pipeline::createShaderModule(const std::vector<char>& code, VkShaderModule* ShaderModule) {
		VkShaderModuleCreateInfo CreateInfo{};
		CreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		CreateInfo.codeSize = code.size();
		CreateInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

		if (vkCreateShaderModule(m_Instance.getVkLogicalDevice(), &CreateInfo, nullptr, ShaderModule) != VK_SUCCESS)
			throw std::runtime_error("Failed to create shader module");
	}

	//binds the pipeline to a commandbuffer
	void Pipeline::bind(VkCommandBuffer commandbuffer) {
		vkCmdBindPipeline(commandbuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_GraphicPipeline);
	}

	//defualt set up for pipeline
	void Pipeline::defaultPipelineConfiginfo(PipelineConfiginfo& configInfo) {
		//input assembly
		configInfo.m_InputAssemblyInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		configInfo.m_InputAssemblyInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		configInfo.m_InputAssemblyInfo.primitiveRestartEnable = VK_FALSE;

		//viewport
		configInfo.m_ViewportInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		configInfo.m_ViewportInfo.viewportCount = 1;
		configInfo.m_ViewportInfo.pViewports = nullptr;
		configInfo.m_ViewportInfo.scissorCount = 1;
		configInfo.m_ViewportInfo.pScissors = nullptr;

		//rasterizer
		configInfo.m_RasterizerInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		configInfo.m_RasterizerInfo.depthClampEnable = VK_FALSE;
		configInfo.m_RasterizerInfo.rasterizerDiscardEnable = VK_FALSE;
		configInfo.m_RasterizerInfo.polygonMode = VK_POLYGON_MODE_FILL;
		configInfo.m_RasterizerInfo.lineWidth = 1.f;
		configInfo.m_RasterizerInfo.cullMode = VK_CULL_MODE_BACK_BIT;
		configInfo.m_RasterizerInfo.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
		configInfo.m_RasterizerInfo.depthBiasEnable = VK_FALSE;
		//if depthbias enabled, edit these
		configInfo.m_RasterizerInfo.depthBiasConstantFactor = 0.f;			//optional
		configInfo.m_RasterizerInfo.depthClampEnable = 0.f;					//optional
		configInfo.m_RasterizerInfo.depthBiasSlopeFactor = 0.f;				//optional

		//Multisampling
		configInfo.m_MultisampleInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		configInfo.m_MultisampleInfo.sampleShadingEnable = VK_FALSE;
		configInfo.m_MultisampleInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
		//if sampleshading enabled, edit these
		configInfo.m_MultisampleInfo.minSampleShading = 1.f;				//optional
		configInfo.m_MultisampleInfo.pSampleMask = nullptr;					//optional
		configInfo.m_MultisampleInfo.alphaToCoverageEnable = VK_FALSE;		//optional
		configInfo.m_MultisampleInfo.alphaToOneEnable = VK_FALSE;			//optional

		//colorblending attachment state
		configInfo.m_ColorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		configInfo.m_ColorBlendAttachment.blendEnable = VK_FALSE;
		//if blend is enabled, edit these
		configInfo.m_ColorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;		//optional
		configInfo.m_ColorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;		//optional
		configInfo.m_ColorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;					//optional
		configInfo.m_ColorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;		//optional
		configInfo.m_ColorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;		//optional
		configInfo.m_ColorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;					//optional

		//color blending state
		configInfo.m_ColorBlendInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		configInfo.m_ColorBlendInfo.logicOpEnable = VK_FALSE;
		configInfo.m_ColorBlendInfo.logicOp = VK_LOGIC_OP_COPY;
		configInfo.m_ColorBlendInfo.attachmentCount = 1;
		configInfo.m_ColorBlendInfo.pAttachments = &configInfo.m_ColorBlendAttachment;
		//change for RGBA depending on blendfactor
		configInfo.m_ColorBlendInfo.blendConstants[0] = 0.f;				//optional
		configInfo.m_ColorBlendInfo.blendConstants[1] = 0.f;				//optional
		configInfo.m_ColorBlendInfo.blendConstants[2] = 0.f;				//optional
		configInfo.m_ColorBlendInfo.blendConstants[2] = 0.f;				//optional

		//depthstencil
		configInfo.m_DepthStencilInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
		configInfo.m_DepthStencilInfo.depthTestEnable = VK_TRUE;			//depthtest for fragments
		configInfo.m_DepthStencilInfo.depthWriteEnable = VK_TRUE;			//if depthtest pass, write to depthbuffer?
		configInfo.m_DepthStencilInfo.depthCompareOp = VK_COMPARE_OP_LESS;	//comparison that is performed to keep or discard fragments(lower depth = closer, so the depth of new fragments should be less.)
		configInfo.m_DepthStencilInfo.depthBoundsTestEnable = VK_FALSE;		//keep fragment that fall within specified depth range
		configInfo.m_DepthStencilInfo.minDepthBounds = 0.f;					//optional
		configInfo.m_DepthStencilInfo.maxDepthBounds = 1.f;					//optional
		configInfo.m_DepthStencilInfo.stencilTestEnable = VK_FALSE;
		configInfo.m_DepthStencilInfo.front = {};							//optional
		configInfo.m_DepthStencilInfo.back = {};							//optional

		//dynamicstates
		configInfo.m_DynamicstateEnables = { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };
		configInfo.m_DynamicstateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		configInfo.m_DynamicstateInfo.pDynamicStates = configInfo.m_DynamicstateEnables.data();
		configInfo.m_DynamicstateInfo.dynamicStateCount = static_cast<uint32_t>(configInfo.m_DynamicstateEnables.size());
		configInfo.m_DynamicstateInfo.flags = 0;

		//TO CHANGE ONCE MODEL>CPP complete
		configInfo.m_BindingDescriptions = Model::Vertex::getBindingDescriptions();
		configInfo.m_AttributeDescriptions = Model::Vertex::getAttributeDescriptions();
	}

	//enable settigns for alpha blending
	void Pipeline::enableAlphaBlending(PipelineConfiginfo& configInfo) {
		configInfo.m_ColorBlendAttachment.blendEnable = VK_TRUE;
		configInfo.m_ColorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		configInfo.m_ColorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
		configInfo.m_ColorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
		configInfo.m_ColorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
		configInfo.m_ColorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
		configInfo.m_ColorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
		configInfo.m_ColorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;
	}
}