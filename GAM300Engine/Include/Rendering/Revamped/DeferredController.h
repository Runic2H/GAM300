#pragma once
namespace TDS
{
	enum DEFERRED_STAGE
	{
		STAGE_G_BUFFER = 0,
		STAGE_LIGTHING,
		STAGE_SHADOW,
		STAGE_COMPOSITION,
		STAGE_MAX

	};


	struct alignas(16) InstanceBuffer
	{
		Vec4 InstData;
		Mat4 model;
	};


	class VulkanPipeline;
	class MaterialBase;
	class DeferredFrames;

	struct Transform;
	struct GraphicsComponent;
	struct MeshData;
	
	class FBO;

	static constexpr int MAX_INSTANCE_BUFFER = 14000;


	struct Transform;

	//1. Put ur update data here
	struct UpdateData
	{
		Transform*				m_pTransform = nullptr;
		int						m_EntityID = -1;
		int						m_TextureID = -1;
	};



	class DeferredController
	{
		public:
			struct MeshInstanceTrack
			{
				std::string			m_MeshName;
				std::uint32_t		m_Instances = 0;
				std::uint32_t		m_Offset = 0;
			};

			struct InstanceData
			{
				std::uint32_t				m_Index = 0;
				std::vector<UpdateData>		m_Updates;
			};
			
			void								Init();
			void								CreatePipelines();
			void								CreateFrameBuffers();
			void								Resize(std::uint32_t width, std::uint32_t height);
			void								UpdateInstanceData();


			std::shared_ptr<VulkanPipeline>		GetDeferredPipeline(DEFERRED_STAGE stage);

		public:
			typedef std::array<InstanceBuffer, MAX_INSTANCE_BUFFER>									INSTANCE_BUFFER_LIST;
			typedef std::array<std::shared_ptr<VulkanPipeline>, DEFERRED_STAGE::STAGE_MAX>			PIPELINE_LIST;
			typedef std::array<FBO*, DEFERRED_STAGE::STAGE_MAX>										FBO_LIST;

			std::uint32_t																			m_InstIndex{0};
			std::uint32_t																			m_UpdateIndex{0};
			std::uint32_t																			m_PointLightIndex {0};

			INSTANCE_BUFFER_LIST																	m_InstanceBuffers;
			PIPELINE_LIST																			m_DeferredPipelines;
			FBO_LIST																				m_FrameBuffers;

			std::vector<MeshInstanceTrack>															m_MeshInstTrackContainer;
			std::map<std::string, InstanceData>														m_MeshInstances;


	};



}