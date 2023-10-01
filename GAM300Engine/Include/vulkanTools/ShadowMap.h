/*!*************************************************************************
****
\file ShadowMap.h
\author Ng Zuo Xian Amadeus
\par DP email: ng.z@digipen.edu
\par Course: CSD3400
\par Section: a
\date 22-9-2023
\brief  Contains the ShadowMap Class and its member functions
****************************************************************************
***/
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
		//Constructor and destructor
		ShadowMap(VulkanInstance& Instance, VkRenderPass renderpass, VkDescriptorSetLayout globalsetlayout);
		~ShadowMap();

		//no copy constructor
		ShadowMap(const ShadowMap&) = delete;
		ShadowMap& operator=(const ShadowMap&) = delete;

		//update ShadowMap
		void update(FrameInfo& frameinfo, GlobalUBO& UBO);
		//render ShadowMap
		void render(FrameInfo& frameinfo);


	private:
		//Helper Function
		void createPipeline(VkRenderPass renderpass);

		void createImageView();
		void createImage();
		void createRenderPass();
		void createFrameBuffer();
		void createCommandBuffer();

		VulkanInstance&				m_Instance;
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