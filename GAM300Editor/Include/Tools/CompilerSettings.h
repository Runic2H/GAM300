#pragma once
/*!*****************************************************************************
 * \file          CompilerSettings.h
 * \author        Eugene Ho Shu Sheng
 * \par DP email: shushengeugene.ho@digipen.edu
 * \par Course:   CSD3400
 * \par Section:  A
 * \date          01/10/2023
 * \brief         Descripter struct for the command parser
 *******************************************************************************/
#include <pch.h>
namespace TDS
{
	struct GeomDescriptor
	{
		/*!*************************************************************************
		 * Transform struct
		 ***************************************************************************/
		struct Transform
		{
			float m_Scale[3] = { 1.f, 1.f, 1.f };
			float m_Rotate[3] = { 0.f, 0.f, 0.f };
			float m_Translate[3] = { 0.f, 0.f, 0.f };
		};
		/*!*************************************************************************
		 * Desc struct contain all the information for the command parser
		 ***************************************************************************/
		struct GenerateLOD
		{
			bool m_CreateLOD = false;
			std::int32_t m_Max_num_lods = 3;
			float ReductionFactor = 0.7f;
		};

		struct Desc
		{
			std::string m_FilePath;
			Transform m_L2W;
			bool MergeMesh = false;
		};

		bool		m_Compress = true;
		bool		m_LoadMesh = true;
		bool		m_LoadAnimation = false; //Sometimes u might want to load mesh only OR animation data only
		bool		m_LoadMaterials = false;
		Desc		m_Descriptor;
		GenerateLOD m_LodOptions;
		bool Serialize(std::string_view FilePath, bool Read);
	};

	struct TextureDescriptor
	{
		struct Desc
		{
			std::string m_BitMapPath;
			std::string m_Format = "R32G32B32A32_FLOAT";
		};
		Desc m_Descriptor;
		bool Serialize(std::string_view FilePath, bool Read);
	};
}