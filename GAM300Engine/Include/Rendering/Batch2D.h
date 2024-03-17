#pragma once
#include "MathCommon.h"
namespace TDS
{
	struct LayerInfo
	{
		bool			isDirty = true;
		std::uint32_t	m_Instance = 0;
		std::uint32_t	m_Offset = 0;
	};

	class Transform;
	//template <typename Derived>
	struct Batch2D
	{
		std::uint32_t m_InstanceCnt = 0;
		std::array<LayerInfo, 12>		m_LayerInfos;
		void Clear()
		{
			m_InstanceCnt = 0;
		}
		bool IsDrawable(Vec3& pos, bool testCPUCulling = false)
		{
			(pos);
			(testCPUCulling);
			return true;
		}

		virtual void AddToBatch(void* componentSprite, Transform* transform, std::uint32_t entity) = 0;
		virtual void PrepareBatch() = 0;

		//template <typename COMPONENT>
		//void AddToBatch(COMPONENT* componentSprite, Transform* transform)
		//{
		//	static_cast<Derived*>(this)->AddToBatch(componentSprite, transform);
		//}
		//void PrepareBatch()
		//{
		//	static_cast<Derived*>(this)->PrepareBatch();
		//}
	};

}