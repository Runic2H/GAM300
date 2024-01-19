#include "Rendering/Revamped/DeferredController.h"
#include "components/transform.h"
namespace TDS
{
	void DeferredController::Init()
	{
	}
	void DeferredController::CreatePipelines()
	{
		
	}
	void DeferredController::UpdateInstanceData()
	{
		for (auto& meshinst : m_MeshInstances)
		{
			MeshInstanceTrack& instTrack = m_MeshInstTrackContainer[meshinst.second.m_Index];
			instTrack.m_MeshName = meshinst.first;

			for (std::uint32_t i = 0; i < meshinst.second.m_Index; ++i)
			{
				UpdateData& update = meshinst.second.m_Updates[i];

				InstanceBuffer& instanceBuffer = m_InstanceBuffers[m_UpdateIndex];

				instTrack.m_Offset = m_InstIndex;
				instTrack.m_Instances = meshinst.second.m_Index;

				instanceBuffer.InstData.z = update.m_EntityID;
				instanceBuffer.InstData.w = update.m_TextureID;

				if (Vec3 Scale = update.m_pTransform->GetScale(); Scale.x <= 0.f || Scale.y <= 0.f || Scale.z <= 0.f)
				{ }
				else 
				{
					update.m_pTransform->GenerateTransform();
				}
				instanceBuffer.model = update.m_pTransform->GetTransformMatrix();


				update.m_TextureID = -1;
				update.m_EntityID = -1;
				update.m_pTransform = nullptr;

				++m_UpdateIndex;
			}
			meshinst.second.m_Index = 0;
			++m_InstIndex;
		}


	}
	void DeferredController::CreateFrameBuffers()
	{
	}
	void DeferredController::Resize(std::uint32_t width, std::uint32_t height)
	{
	}

}