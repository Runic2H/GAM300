/*!*****************************************************************************
 * \file          AssetModel.cpp
 * \author        Eugene Ho Shu Sheng
 * \par DP email: shushengeugene.ho@digipen.edu
 * \par Course:   CSD3400
 * \par Section:  A
 * \date          01/10/2023
 * \brief         This file contains the implementation of the AssetModel class.
 *******************************************************************************/
#include "GraphicsResource/AssetModel.h"
#include <fstream>
#include <iostream>
#include "Rendering/GraphicsManager.h"
#include "vulkanTools/vulkanSwapChain.h"
#include "vulkanTools/vulkanInstance.h"
#include "vulkanTools/Renderer.h"
namespace TDS
{

	void AssetModel::LoadGeomData(Geom& geom)
	{
		iColor color{};
		m_CurrMeshData->m_VertexData.resize(geom.m_Pos.size());
		m_CurrMeshData->m_IndexData.resize(geom.m_Indices.size());
		std::copy(geom.m_Indices.begin(), geom.m_Indices.end(), m_CurrMeshData->m_IndexData.data());
		for (size_t i = 0; i < geom.m_Pos.size(); ++i) {
			m_CurrMeshData->m_VertexData[i].m_Pos = geom.m_Pos[i];


			if (i < geom.m_Extra.size())
			{
				m_CurrMeshData->m_VertexData[i].m_UV = geom.m_Extra[i].m_UV;

				m_CurrMeshData->m_VertexData[i].m_fNormal = Vec4(geom.m_Extra[i].m_Normal.x, geom.m_Extra[i].m_Normal.y, geom.m_Extra[i].m_Normal.z, 1.0f);
				//m_VertexData[i].m_fTanget = geom.m_Extra[i].m_Tanget;
				//m_VertexData[i].m_fBitangent = geom.m_Extra[i].m_Bitangent;



				m_CurrMeshData->m_VertexData[i].m_Color = { 255.f, 0.f, 0.f };
				/*m_VertexData[i].m_Tangent = iColor(Vec4(geom.m_Extra[i].m_Tanget.x, geom.m_Extra[i].m_Tanget.y, geom.m_Extra[i].m_Tanget.z, 1.0f));
				m_VertexData[i].m_Bitangent = iColor(Vec4(geom.m_Extra[i].m_Bitangent.x, geom.m_Extra[i].m_Bitangent.y, geom.m_Extra[i].m_Bitangent.z, 1.0f));
				m_VertexData[i].m_Normal = iColor(Vec4(geom.m_Extra[i].m_Normal.x, geom.m_Extra[i].m_Normal.y, geom.m_Extra[i].m_Normal.z, 1.0f));*/
			}
		}


	}
	void DLL_API AssetModel::Load(Geom& geom)
	{
		if (geom.m_Mesh.empty() || geom.m_SubMesh.empty())
		{
			return;
		}

		const auto& baseSubMesh = geom.m_SubMesh[0];


		m_CurrMeshData->m_VertexData.resize(baseSubMesh.m_nVertices);
		m_CurrMeshData->m_IndexData.resize(baseSubMesh.m_nFaces * 3);
		std::copy_n(geom.m_Indices.begin() + baseSubMesh.m_iIndices, m_CurrMeshData->m_IndexData.size(), m_CurrMeshData->m_IndexData.begin());

		for (size_t i = 0; i < baseSubMesh.m_nVertices; ++i) {
			auto vertexIndex = baseSubMesh.m_iVertices + i;
			m_CurrMeshData->m_VertexData[i].m_Pos = geom.m_Pos[vertexIndex];

			if (vertexIndex < geom.m_Extra.size())
			{
				m_CurrMeshData->m_VertexData[i].m_UV = geom.m_Extra[vertexIndex].m_UV;
				m_CurrMeshData->m_VertexData[i].m_fNormal = Vec4(geom.m_Extra[vertexIndex].m_Normal.x, geom.m_Extra[vertexIndex].m_Normal.y, geom.m_Extra[vertexIndex].m_Normal.z, 1.0f);

				m_CurrMeshData->m_VertexData[i].m_Color = { 255.f, 0.f, 0.f };
			}
		}

		Vec3 centroid(0.0f, 0.0f, 0.0f);
		for (const auto& vertex : m_CurrMeshData->m_VertexData) {
			centroid += vertex.m_Pos;
		}
		centroid /= static_cast<float>(m_CurrMeshData->m_VertexData.size());

		BoundingBox.setNull();
		for (const auto& vertex : m_CurrMeshData->m_VertexData) {
			BoundingBox.extend(vertex.m_Pos - centroid);
		}
	}
	void DLL_API AssetModel::CreateBuffers()
	{
		if (m_CurrMeshData->m_VertexData.empty() && m_CurrMeshData->m_IndexData.empty())
		{
			return;
		}
		if (m_CurrMeshData->m_VertexBuffer == nullptr)
			m_CurrMeshData->m_VertexBuffer = new VMABuffer();
		if (m_CurrMeshData->m_IndexBuffer == nullptr)
			m_CurrMeshData->m_IndexBuffer = new VMABuffer();

		m_CurrMeshData->m_VertexBuffer->MappedStaging(m_CurrMeshData->m_VertexData.size() * sizeof(VertexData), VkBufferUsageFlagBits::VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, GraphicsManager::getInstance().getVkInstance(), m_CurrMeshData->m_VertexData.data());
		//m_VertexBuffer->CreateVertexBuffer(m_VertexData.size() * sizeof(VertexData), false, m_VertexData.data());
		m_CurrMeshData->m_VertexBuffer->SetDataCnt(m_CurrMeshData->m_VertexData.size());
		/*	m_IndexBuffer->CreateIndexBuffer(m_IndexData.size() * sizeof(std::uint32_t), false, m_IndexData.data());*/
		m_CurrMeshData->m_IndexBuffer->MappedStaging(m_CurrMeshData->m_IndexData.size() * sizeof(std::uint32_t), VkBufferUsageFlagBits::VK_BUFFER_USAGE_INDEX_BUFFER_BIT, GraphicsManager::getInstance().getVkInstance(), m_CurrMeshData->m_IndexData.data());
		m_CurrMeshData->m_IndexBuffer->SetDataCnt(m_CurrMeshData->m_IndexData.size());
	}
	void DLL_API AssetModel::DestroyBuffers()
	{
		//This is not efficient but since we not really multithreading. Just do this for now

		//if (m_CurrMeshData->m_VertexBuffer)
		//{
		//	m_CurrMeshData->m_VertexBuffer->DestroyBuffer();
		//	delete m_CurrMeshData->m_VertexBuffer;
		//	m_CurrMeshData->m_VertexBuffer = nullptr;
		//}

		//if (m_CurrMeshData->m_IndexBuffer)
		//{

		//	m_CurrIndexBuffer->DestroyBuffer();
		//	delete m_CurrIndexBuffer;
		//	m_CurrIndexBuffer = nullptr;
		//}


	}
	AssetModel::AssetModel()
	{
	}
	AssetModel::~AssetModel()
	{

	}

	std::vector<VertexData>& AssetModel::GetVertexData()
	{
		return m_CurrMeshData->m_VertexData;
	}
	std::vector<std::uint32_t>& AssetModel::GetIndexData()
	{
		return m_CurrMeshData->m_IndexData;
	}

	DLL_API VMABuffer* AssetModel::GetIndexBuffer()
	{
		return m_CurrMeshData->m_IndexBuffer;
	}

	DLL_API VMABuffer* AssetModel::GetVertexBuffer()
	{
		return m_CurrMeshData->m_VertexBuffer;
	}

	DLL_API bool AssetModel::BufferIsNull()
	{
		return (m_CurrMeshData->m_VertexBuffer == nullptr && m_CurrMeshData->m_IndexBuffer == nullptr);
	}

	DLL_API void AssetModel::Destroy()
	{
		for (auto& mesh : m_Meshes)
		{
			mesh.second.Destroy();
		}
	}

	DLL_API void AssetModel::CreateBoundingShapes()
	{
		
			Vec3 centroid(0.0f, 0.0f, 0.0f);

			std::uint32_t cnt = 0;
			for (auto& mesh : m_Meshes)
			{

				for (const auto& vertex : mesh.second.m_VertexData)
				{
					centroid += vertex.m_Pos;
					++cnt;
				}

			}
			centroid /= static_cast<float>(cnt);

			BoundingBox.setNull();

			for (auto& mesh : m_Meshes)
			{

				for (const auto& vertex : mesh.second.m_VertexData)
				{
					BoundingBox.extend(vertex.m_Pos - centroid);
				}

			}
	}

	void MeshData::CreateBuffers()
	{
		if (m_VertexData.empty() && m_IndexData.empty())
		{
			return;
		}
		if (m_VertexBuffer == nullptr)
			m_VertexBuffer = new VMABuffer();
		if (m_IndexBuffer == nullptr)
			m_IndexBuffer = new VMABuffer();

		m_VertexBuffer->MappedStaging(m_VertexData.size() * sizeof(VertexData), VkBufferUsageFlagBits::VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, GraphicsManager::getInstance().getVkInstance(), m_VertexData.data());
		m_VertexBuffer->SetDataCnt(m_VertexData.size());
		m_IndexBuffer->MappedStaging(m_IndexData.size() * sizeof(std::uint32_t), VkBufferUsageFlagBits::VK_BUFFER_USAGE_INDEX_BUFFER_BIT, GraphicsManager::getInstance().getVkInstance(), m_IndexData.data());
		m_IndexBuffer->SetDataCnt(m_IndexData.size());
	}

	bool MeshData::BufferIsNull()
	{
		return (m_IndexBuffer == nullptr || m_VertexBuffer == nullptr);
	}

	void MeshData::Destroy()
	{
		vkQueueWaitIdle(GraphicsManager::getInstance().getVkInstance().getGraphicsQueue());
		if (BufferIsNull() == false)
		{
			m_VertexBuffer->DestroyBuffer();
			m_IndexBuffer->DestroyBuffer();
			delete m_VertexBuffer;
			delete m_IndexBuffer;
			m_VertexBuffer = nullptr;
			m_IndexBuffer = nullptr;

		}
	}

	void MeshData::CreateBoundingShapes()
	{
		Vec3 centroid(0.0f, 0.0f, 0.0f);
		for (const auto& vertex : m_VertexData)
		{
			centroid += vertex.m_Pos;
		}
		centroid /= static_cast<float>(m_VertexData.size());

		BoundingBox.setNull();

		for (const auto& vertex : m_VertexData)
		{
			BoundingBox.extend(vertex.m_Pos - centroid);
		}
	}

}