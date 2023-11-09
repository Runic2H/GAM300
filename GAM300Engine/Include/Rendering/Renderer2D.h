#pragma once
#include "MathCommon.h"
#include "camera/SphereFrustum.h"
#include "ResourceManagement/ResourceManager.h"
#include "GraphicsResource/AssetModel.h"

namespace TDS
{
	struct InstanceInfo2D
	{
		Vec3			m_Scale;
		Vec3			m_Rotate;
		Vec3			m_Translate;
		Mat4			m_Transform{ 1.f };
		Color*			m_Color = nullptr;
		std::uint32_t	m_LayerID;
		std::uint32_t	m_TextureIndex = 499;
	};

	struct LayerInfo
	{
		bool isDirty = true;
		std::uint32_t	m_Instance = 0;
		std::uint32_t	m_Offset = 0;

	};


	struct alignas(16) Instance2D
	{
		Mat4 m_Model;
		Vec4 m_Color;
		Vec4 m_texID = { 499.f, 0.f, 0.f, 0.f };
	};

	struct alignas(16) SceneUBO
	{
		Mat4 Projection;
		Mat4 View;
		unsigned int ViewingFrom2D = 0;
		float padding[3];
	};
	class Transform;
	class UISprite;

	struct Batch2DList
	{
		std::uint32_t m_InstanceCnt = 0;

		std::array<Instance2D, 12000>		m_Instances;
		std::array<InstanceInfo2D, 12000> m_InstanceInfo;
		std::array<LayerInfo, 12>		m_LayerInfos;

		void			DLL_API Clear();
		bool			DLL_API IsDrawable(Vec3& pos, bool testCPUCulling = false);
		void			DLL_API AddToBatch(UISprite* componentSprite, Transform* transform);
		void			DLL_API PrepareBatch();
	};

	class RenderTarget;
	class RenderPass;
	class FrameBuffer;
	class VulkanPipeline;

	struct OffScreenFrameBuffer
	{
		RenderTarget* m_RenderingAttachment{ nullptr };
		RenderTarget* m_RenderingDepthAttachment{ nullptr };
		RenderPass* m_Renderpass{ nullptr };
		FrameBuffer* m_Framebuffer{ nullptr };
		Vec4 ClearColor = Vec4(0.0f, 0.0f, 0.0f, 1.0f);
	};

	struct RenderedSprite
	{
		bool					m_Update = false;
		VkDescriptorImageInfo	m_ImageInfo{};
		
	};

	class Renderer2D
	{
		public:
			DLL_API Renderer2D();
			DLL_API ~Renderer2D();
			void DLL_API Init();
			void DLL_API Draw(VkCommandBuffer commandBuffer, int Frame, Vec4 ClearColor = {0.f, 0.f, 0.f, 1.f});
			void DLL_API DrawNonBatch(VkCommandBuffer commandBuffer, int Frame);
			void DLL_API Update(VkCommandBuffer commandBuffer, int Frame);
			void DLL_API UpdateNonBatch(UISprite* componentSprite, Transform* transform, VkCommandBuffer commandBuffer, size_t EntitySize, int Frame);
			inline Batch2DList& GetBatchList()
			{
				return m_BatchList;
			}
			inline RenderedSprite& GetRenderedSprite()
			{
				return m_SpriteTexture;
			}
			void DLL_API ShutDown();
			static std::shared_ptr<Renderer2D> DLL_API GetInstance();
		private:
			inline static std::shared_ptr<Renderer2D> m_Instance = nullptr;
			std::shared_ptr<VulkanPipeline> m_Pipeline = nullptr;
			//std::shared_ptr<VulkanPipeline> m_CanvasRenderer = nullptr;
			Batch2DList m_BatchList{};
			RenderedSprite m_SpriteTexture{};
			OffScreenFrameBuffer m_FrameBuffer; //Not using for now
			//TypeReference<AssetModel> m_AssetModel;
			VMABuffer* m_VertexBuffer = nullptr;
			VMABuffer* m_IndexBuffer = nullptr;
			SceneUBO m_SceneUBO{}; //Probably not in used.
			

	};

}