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
		m_VertexData.resize(geom.m_Pos.size());
		m_IndexData.resize(geom.m_Indices.size());
		std::copy(geom.m_Indices.begin(), geom.m_Indices.end(), m_IndexData.data());
		for (size_t i = 0; i < geom.m_Pos.size(); ++i) {
			m_VertexData[i].m_Pos = geom.m_Pos[i];


			if (i < geom.m_Extra.size())
			{
				m_VertexData[i].m_UV = geom.m_Extra[i].m_UV;

				m_VertexData[i].m_fNormal = Vec4(geom.m_Extra[i].m_Normal.x, geom.m_Extra[i].m_Normal.y, geom.m_Extra[i].m_Normal.z, 1.0f);
				//m_VertexData[i].m_fTanget = geom.m_Extra[i].m_Tanget;
				//m_VertexData[i].m_fBitangent = geom.m_Extra[i].m_Bitangent;



				m_VertexData[i].m_Color = { 255.f, 0.f, 0.f };
				/*m_VertexData[i].m_Tangent = iColor(Vec4(geom.m_Extra[i].m_Tanget.x, geom.m_Extra[i].m_Tanget.y, geom.m_Extra[i].m_Tanget.z, 1.0f));
				m_VertexData[i].m_Bitangent = iColor(Vec4(geom.m_Extra[i].m_Bitangent.x, geom.m_Extra[i].m_Bitangent.y, geom.m_Extra[i].m_Bitangent.z, 1.0f));
				m_VertexData[i].m_Normal = iColor(Vec4(geom.m_Extra[i].m_Normal.x, geom.m_Extra[i].m_Normal.y, geom.m_Extra[i].m_Normal.z, 1.0f));*/
			}
		}


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
	void DLL_API AssetModel::CreateBuffers()
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
		//m_VertexBuffer->CreateVertexBuffer(m_VertexData.size() * sizeof(VertexData), false, m_VertexData.data());
		m_VertexBuffer->SetDataCnt(m_VertexData.size());
		/*	m_IndexBuffer->CreateIndexBuffer(m_IndexData.size() * sizeof(std::uint32_t), false, m_IndexData.data());*/
		m_IndexBuffer->MappedStaging(m_IndexData.size() * sizeof(std::uint32_t), VkBufferUsageFlagBits::VK_BUFFER_USAGE_INDEX_BUFFER_BIT, GraphicsManager::getInstance().getVkInstance(), m_IndexData.data());
		m_IndexBuffer->SetDataCnt(m_IndexData.size());
	}
	void DLL_API AssetModel::DestroyBuffers()
	{
		//This is not efficient but since we not really multithreading. Just do this for now
		vkQueueWaitIdle(GraphicsManager::getInstance().getVkInstance().getGraphicsQueue());
		if (m_VertexBuffer)
		{
			m_VertexBuffer->DestroyBuffer();
			delete m_VertexBuffer;
			m_VertexBuffer = nullptr;
		}

		if (m_IndexBuffer)
		{

			m_IndexBuffer->DestroyBuffer();
			delete m_IndexBuffer;
			m_IndexBuffer = nullptr;
		}


	}
	AssetModel::AssetModel()
	{
	}
	AssetModel::~AssetModel()
	{

	}

	std::vector<VertexData>& AssetModel::GetVertexData()
	{
		return m_VertexData;
	}
	std::vector<std::uint32_t>& AssetModel::GetIndexData()
	{
		return m_IndexData;
	}

	DLL_API VMABuffer* AssetModel::GetIndexBuffer()
	{
		return m_IndexBuffer;
	}

	DLL_API VMABuffer* AssetModel::GetVertexBuffer()
	{
		return m_VertexBuffer;
	}

	DLL_API bool AssetModel::BufferIsNull()
	{
		return (m_IndexBuffer == nullptr && m_VertexBuffer == nullptr);
	}

	DLL_API void AssetModel::Destroy()
	{
		if (BufferIsNull() == false)
		{
			DestroyBuffers();
		}
	}

}