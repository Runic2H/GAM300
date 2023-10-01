/*!*****************************************************************************
 * \file          AssetModel.h
 * \author        Eugene Ho Shu Sheng
 * \par DP email: shushengeugene.ho@digipen.edu
 * \par Course:   CSD3400
 * \par Section:  A
 * \date          01/10/2023
 * \brief         This file contains the declaration of the AssetModel class.
 *******************************************************************************/
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
		/*!*************************************************************************
		 * Constructor & Destructor for AssetModel class
		 ***************************************************************************/
		AssetModel();
		~AssetModel();
		/*!*************************************************************************
		 * Load the geometry data from GeomCompiled
		 ***************************************************************************/
		void LoadGeomData(GeomCompiled& geom);
		/*!*************************************************************************
		 * Helper Functions
		 ***************************************************************************/
		std::vector<VertexData>& GetVertexData();
		std::vector<std::uint32_t>& GetIndexData();


	};


}