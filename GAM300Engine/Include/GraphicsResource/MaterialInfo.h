#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H
#include "MathCommon.h"
namespace TDS
{
	

#define ADD_MATERIAL_TYPE(x, y) MATERIAL_##x = y,


#define DEFINE_MATERIAL_TYPE_LIST \
	ADD_MATERIAL_TYPE(DIFFUSE, 1)\
	ADD_MATERIAL_TYPE(SPECULAR, 2)\
	ADD_MATERIAL_TYPE(AMBIENT, 3)\
	ADD_MATERIAL_TYPE(EMISSIVE, 4)\
	ADD_MATERIAL_TYPE(HEIGHT, 5)\
	ADD_MATERIAL_TYPE(NORMALS, 6)\
	ADD_MATERIAL_TYPE(SHININESS, 8)\
	ADD_MATERIAL_TYPE(OPACITY,8)\
	ADD_MATERIAL_TYPE(DISPLACEMENT, 9)\
	ADD_MATERIAL_TYPE(LIGHTMAP, 10)\
	ADD_MATERIAL_TYPE(REFLECTION, 11)\
	ADD_MATERIAL_TYPE(PBR_ALBEDO, 12)\
	ADD_MATERIAL_TYPE(PBR_NORMAL, 13)\
	ADD_MATERIAL_TYPE(PBR_EMISSION, 14)\
	ADD_MATERIAL_TYPE(PBR_METALNESS, 15)\
	ADD_MATERIAL_TYPE(PBR_ROUGHNESS, 16)\
	ADD_MATERIAL_TYPE(PBR_OCCLUSION, 17)\
	ADD_MATERIAL_TYPE(SHEEN, 19)\
	ADD_MATERIAL_TYPE(CLEARCOAT,20)\
	ADD_MATERIAL_TYPE(TRANSMISSION,21)




	typedef enum : std::uint16_t
	{
		DEFINE_MATERIAL_TYPE_LIST
	} 
	MATERIAL_TYPE;


	#undef ADD_MATERIAL_TYPE

	#define ADD_MATERIAL_TYPE(x, y)\
		materialMapList[y] = #x;

	struct MaterialMapList
	{
		static auto& Get()
		{
			static std::map<int, std::string> materialMapList;

			if (materialMapList.empty())
				DEFINE_MATERIAL_TYPE_LIST

				return materialMapList;
		}
	};
	

	struct MaterialInfo
	{
		std::string		m_MaterialName;
		size_t			m_MaterialGUID;
	};



	struct MaterialList
	{
		std::vector<MaterialInfo> m_MaterialInfos;
	};


}
#endif