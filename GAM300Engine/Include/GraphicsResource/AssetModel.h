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
#include "vulkanTools/VMATypes/VMABuffer.h"
namespace TDS
{
	class Material;

	struct DLL_API MeshData
	{
		VMABuffer* m_VertexBuffer = nullptr;
		VMABuffer* m_IndexBuffer = nullptr;
		std::vector<VertexData> m_VertexData;
		std::vector<std::uint32_t> m_IndexData;

		void CreateBuffers();
		bool BufferIsNull();
		void Destroy();

		void CreateBoundingShapes();

		AABB BoundingBox;
		Sphere m_BoundingSphere;
	};
	class AssetModel
	{
	public:
		/*!*************************************************************************
		 * Constructor & Destructor for AssetModel class
		 ***************************************************************************/
		DLL_API AssetModel();
		DLL_API ~AssetModel();
		/*!*************************************************************************
		 * Load the geometry data from GeomCompiled
		 ***************************************************************************/
		void DLL_API LoadGeomData(Geom& geom);
		void DLL_API Load(Geom& geom);
		void DLL_API CreateBuffers();

		void DLL_API DestroyBuffers();
		/*!*************************************************************************
		 * Helper Functions
		 ***************************************************************************/
		DLL_API std::vector<VertexData>& GetVertexData();
		DLL_API std::vector<std::uint32_t>& GetIndexData();
		DLL_API VMABuffer* GetIndexBuffer();
		DLL_API VMABuffer* GetVertexBuffer();
		DLL_API bool BufferIsNull();
		DLL_API void Destroy();
		DLL_API void CreateBoundingShapes();
	private:
		AABB BoundingBox;
		Sphere m_BoundingSphere;
	public:
		MeshData* m_CurrMeshData = nullptr;
		std::unordered_map<std::string, MeshData> m_Meshes;

	};


}