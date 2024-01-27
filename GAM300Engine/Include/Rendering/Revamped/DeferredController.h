#pragma once
#include "vulkanTools/FrameInfo.h"
namespace TDS
{
	enum DEFERRED_STAGE
	{
		STAGE_G_BUFFER_BATCH = 0,
		STAGE_G_BUFFER_INSTANCE,
		STAGE_LIGTHING,
		STAGE_SHADOW,
		STAGE_DEPTH_SHADOW,
		STAGE_SHADOW_OMNI,
		STAGE_COMPOSITION,
		STAGE_MAX

	};

	enum RENDER_PASS
	{
		RENDER_G_BUFFER = 0,
		RENDER_SHADOW_MAPPING,
		RENDER_SHADOW_OMNI,
		RENDER_LIGTHING,
		RENDER_POST,
		RENDER_COMPOSITION,
		RENDER_TOTAL
	};



	class VulkanPipeline;
	class MaterialBase;
	class DeferredFrames;

	struct Transform;
	struct GraphicsComponent;
	struct MeshBuffer;

	class FrameBufferObject;

	static constexpr int MAX_INSTANCE_BUFFER = 10000;
	static constexpr int MAX_POSSIBLE_BATCH = 10000;


	struct Transform;

	//1. Put ur update data here



	struct MeshUpdate
	{
		Transform* m_pTransform = nullptr;
		int						m_MeshID;
		int						m_EntityID = -1;
		int						m_TextureID = -1;
		bool					m_IsAnimated = false;
		bool					m_ShowMesh = false;
	};

	struct UpdateData
	{
		std::vector<MeshUpdate>		m_MeshUpdates;
		MeshBuffer* m_MeshBuffer = nullptr;
	};


	struct alignas(16) BatchData
	{
		std::uint32_t	m_MaterialID;
		std::uint32_t	m_TextureID;
		std::uint32_t	m_isAnimated;
		std::uint32_t	m_EntityID;
		Mat4			m_modelMatrix;
	};

	//Batch Rendering Data

	struct Batch3D
	{

		std::array<BatchData, MAX_POSSIBLE_BATCH>												m_BatchBuffers;
		std::map<std::string, UpdateData>														m_BatchUpdateInfo;
		std::uint32_t																			m_BatchCnt;


	};

	//For single mesh, I would prefer to use instancing.
	struct Instance3D
	{

		struct InstanceRenderManager
		{
			struct RenderInstanceInfo
			{
				std::uint32_t			m_Instances = 0;
				std::uint32_t			m_InstanceOffset = 0;
			};


			struct InstanceRequest
			{
				MeshBuffer* m_MeshBuffer = nullptr;
				RenderInstanceInfo				m_RenderInstanceInfo;
			};


			struct InstanceUpdatePack
			{
				std::uint32_t				m_Index = 0;
				std::vector<MeshUpdate>		m_Updates;
			};
			std::map<MeshBuffer*, InstanceUpdatePack>	m_InstanceUpdateInfo;
		};
		std::uint32_t																m_TotalInstances = 0;
		std::uint32_t																m_GroupIdx = 0;
		InstanceRenderManager														m_instanceRenderManager;
		std::array<InstanceRenderManager::InstanceRequest, MAX_INSTANCE_BUFFER>		m_InstanceRequests;
		std::array<BatchData, MAX_INSTANCE_BUFFER>									m_InstanceBuffers;


	};





	class DeferredController
	{
	public:
		typedef std::array<std::shared_ptr<VulkanPipeline>, DEFERRED_STAGE::STAGE_MAX>			PIPELINE_LIST;

		void											Init();
		void											CreatePipelines();
		void											CreateFrameBuffers(std::uint32_t width, std::uint32_t height);
		void											Resize(std::uint32_t width, std::uint32_t height);
		void											G_BufferPass();
		void											G_BufferInstanced();

		void											ClearBatchSubmission();
		void											SubmitMesh(std::uint32_t entityID, GraphicsComponent* graphComp, Transform* transformComp);
		void											SubmitBatch(std::uint32_t entityID, int TextureID, Transform* transformComp, GraphicsComponent* graphComp);
		void											SubmitInstance(std::uint32_t entityID, int TextureID, Transform* transformComp, GraphicsComponent* graphComp);
		std::shared_ptr<VulkanPipeline>					GetDeferredPipeline(DEFERRED_STAGE stage);
		void											ShutDown();

	public:
		GlobalUBO globalUBO{}; //Temp for testing

	private:
		Batch3D											m_Batch3D;
		Instance3D										m_Instance3D;
		PIPELINE_LIST									m_DeferredPipelines;






	};



}