#pragma once

#include "dotnet/ImportExport.h"
#include "vulkanTools/vulkanInstance.h"
#include "vulkanTools/Pipeline.h"
#include "FrameInfo.h"


namespace TDS {
	class DLL_API ShadowMap {
	public:
#define SHADOW_MAP_WIDTH 1200
#define SHADOW_MAP_HEIGHT 800
		ShadowMap(VulkanInstance& Instance, VkRenderPass renderpass, VkDescriptorSetLayout globalsetlayout);
		~ShadowMap();

		ShadowMap(const ShadowMap&) = delete;
		ShadowMap& operator=(const ShadowMap&) = delete;

		void update(FrameInfo& frameinfo, GlobalUBO& UBO);
		void render(FrameInfo& frameinfo);


	private:
		void createPipeline(VkRenderPass renderpass);

		void createImageView();
		void createImage();
		void createRenderPass();
		void createFrameBuffer();
		void createCommandBuffer();

		VulkanInstance& m_Instance;
		VkRenderPass				m_Renderpass;
		VkFramebuffer				m_FrameBuffer;
		VkCommandBuffer				m_CmdBuffer;

		std::unique_ptr<Pipeline>	m_Pipeline;
		VkPipelineLayout			m_pipelineLayout;
		VkImageView					m_ImageView;
		VkImage						m_Image;
		VkShaderModule				m_VertShader;
	};
}