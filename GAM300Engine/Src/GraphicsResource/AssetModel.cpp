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
namespace TDS
{

	void AssetModel::LoadGeomData(GeomCompiled& geom)
	{
		m_VertexData.resize(geom.m_Pos.size());
		m_IndexData.resize(geom.m_Indices.size());
		std::copy(geom.m_Indices.begin(), geom.m_Indices.end(), m_IndexData.data());
		for (size_t i = 0; i < geom.m_Pos.size(); ++i) {
			m_VertexData[i].m_Pos = geom.m_Pos[i];


			if (i < geom.m_Extra.size())
			{
				m_VertexData[i].m_UV = geom.m_Extra[i].m_UV;

				m_VertexData[i].m_fNormal = Vec4(geom.m_Extra[i].m_Normal.x, geom.m_Extra[i].m_Normal.y, geom.m_Extra[i].m_Normal.z, 1.0f);
				m_VertexData[i].m_fTanget = geom.m_Extra[i].m_Tanget;
				m_VertexData[i].m_fBitangent = geom.m_Extra[i].m_Bitangent;

				m_VertexData[i].m_Color = iColor(geom.m_Extra[i].m_Colour);

				m_VertexData[i].m_Tangent = iColor(Vec4(geom.m_Extra[i].m_Tanget.x, geom.m_Extra[i].m_Tanget.y, geom.m_Extra[i].m_Tanget.z, 1.0f));
				m_VertexData[i].m_Bitangent = iColor(Vec4(geom.m_Extra[i].m_Bitangent.x, geom.m_Extra[i].m_Bitangent.y, geom.m_Extra[i].m_Bitangent.z, 1.0f));
				m_VertexData[i].m_Normal = iColor(Vec4(geom.m_Extra[i].m_Normal.x, geom.m_Extra[i].m_Normal.y, geom.m_Extra[i].m_Normal.z, 1.0f));
			}
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
}