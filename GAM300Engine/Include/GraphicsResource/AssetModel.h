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
	class AssetModel
	{
	private:
		std::vector<VertexData> m_VertexData;
		std::vector<std::uint32_t> m_IndexData;
		AABB BoundingBox;
	public:
		/*!*************************************************************************
		 * Constructor & Destructor for AssetModel class
		 ***************************************************************************/
		DLL_API AssetModel();
		DLL_API ~AssetModel();
		/*!*************************************************************************
		 * Load the geometry data from GeomCompiled
		 ***************************************************************************/
		DLL_API void LoadGeomData(GeomCompiled& geom);
		/*!*************************************************************************
		 * Helper Functions
		 ***************************************************************************/
		DLL_API std::vector<VertexData>& GetVertexData();
		DLL_API std::vector<std::uint32_t>& GetIndexData();


	};


}