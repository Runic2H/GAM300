#pragma once


/*!*****************************************************************************
* \file          GeometryStructures.h
* \author        Eugene Ho Shu Sheng
* \par DP email: shushengeugene.ho@digipen.edu
* \par Course:   CSD3400
* \par Section:  A
* \date          01/10/2023
* \brief         Structure for Geometry
*******************************************************************************/
#pragma once
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "TDSMath.h"
#include "../GAM300Engine/Include/GraphicsResource/GraphicsResourceDefines.h"
#include "pch.h"

namespace TDS
{
	struct lod
	{
		std::vector<std::uint32_t> m_Indices;
	};
	/*!*************************************************************************
	 * RawVertex struct that create a vertex
	 ***************************************************************************/
	struct RawVertex
	{
		Vec3 m_Pos;
		Vec2 m_UV;
		Vec4 m_fNormal;
		Vec3 m_fTanget;
		Vec3 m_fBitangent;
		iColor m_Tangent;
		iColor m_Bitangent;
		iColor m_Normal;
		iColor m_Color;

	};

	/*!*************************************************************************
	 * For geom compiler, compile all the geometry into a single file
	 ***************************************************************************/
	struct GeomCompiled
	{
		struct Mesh
		{
			std::array<char, 64> m_Name;
		};

		struct SubMesh
		{
			std::uint32_t m_nFaces;
			std::uint32_t m_iIndices;
			std::uint32_t m_iVertices;
			std::uint32_t m_nVertices;
			std::uint16_t m_iMaterial;
		};

		struct ExtraVertices
		{
			Vec2 m_UV;
			Vec3 m_Normal;
			Vec3 m_Tanget;
			Vec3 m_Bitangent;
			std::uint32_t m_Colour;
		};
		std::vector<Mesh> m_Mesh;
		std::vector<SubMesh> m_SubMesh;
		std::vector<Vec3> m_Pos;
		std::vector<ExtraVertices> m_Extra;
		std::vector<std::uint32_t> m_Indices;
	};


	/*!*************************************************************************
	 * Output the geometry into a file from the compiled geometry
	 ***************************************************************************/
	struct FinalGeom
	{
		struct SubMesh
		{
			std::vector<Vec3> m_Pos;
			std::vector<GeomCompiled::ExtraVertices> m_Extra;
			std::vector<std::uint32_t> m_Indices;
			std::int32_t m_iMaterial;
		};

		struct Mesh
		{
			std::string m_Name;
			std::vector<SubMesh> m_SubMeshes;
		};

		std::string m_Filename;
		std::vector<Mesh> m_Meshes;

	};

}
