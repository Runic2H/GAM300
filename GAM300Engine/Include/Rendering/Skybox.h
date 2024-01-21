#pragma once
#include "vulkanTools/VulkanPipeline.h"
#include "MathCommon.h"
#include "GraphicsResource/TextureInfo.h"
#include "vulkanTools/VulkanTexture.h"
#include "AssetManagement/AssetManager.h"
#include "dotnet/ImportExport.h"
namespace TDS
{

	class SkyBoxRenderer
	{
		private:
			struct SkyBoxUBO
			{
				Mat4			m_Projection{};
				Mat4			m_View{};
			}skyboxubo;
			struct SkyBoxVertexData
			{
				Vec3 m_Pos{1.f,0.f,0.f};
			};

			Texture							m_SkyBoxTexture;
			std::shared_ptr<VulkanPipeline> m_SkyBoxPipeline = nullptr;
			Vec3				m_SkylinePositions{};
			Vec3				m_SkylineScale{2000.f,2000.f,2000.f};
			Vec3				m_SkylineRot{};
			TypeReference<MeshController>		m_CubeMapModel;
			std::shared_ptr<VMABuffer>		m_CubeMapVertexBuffer = nullptr;
			std::shared_ptr<VMABuffer>		m_CubeMapIndexBuffer = nullptr;
		public:
			DLL_API void Init();
			DLL_API void RenderSkyBox(VkCommandBuffer commandBuffer, uint32_t frameIndex);
			DLL_API void ShutDown();


	};

}