#pragma once
#include <string_view>
#include "VertexInfo.h"
#include <vector>
#include "Geometry/Geometry.h"
#include "vulkanTools/Geom.h"
namespace TDS
{
	class DLL_API AssetModel
	{
	private:
		std::vector<VertexData> m_VertexData;
		std::vector<std::uint32_t> m_IndexData;
		AABB BoundingBox;
	public:
		AssetModel();
		~AssetModel();
		void LoadGeomData(GeomCompiled& geom);
		std::vector<VertexData>& GetVertexData();
		std::vector<std::uint32_t>& GetIndexData();


	};


}