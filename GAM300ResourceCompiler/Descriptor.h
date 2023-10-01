/*!*****************************************************************************
 * \file          Descriptor.h
 * \author        Eugene Ho Shu Sheng
 * \par DP email: shushengeugene.ho@digipen.edu
 * \par Course:   CSD3400
 * \par Section:  A
 * \date          01/10/2023
 * \brief         Descripter struct for the command parser
 *******************************************************************************/
#pragma once
#include "pch.h"
namespace TDS
{

	struct Descriptor
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
		struct Desc
		{
			std::string m_FilePath;
			Transform m_L2W;
			bool MergeMesh = false;
			std::string m_MeshFileName;
			std::string m_RenamedMesh;
		};
		Desc m_Descriptor;
		bool Serialize(std::string_view FilePath, bool Read);
	};

}