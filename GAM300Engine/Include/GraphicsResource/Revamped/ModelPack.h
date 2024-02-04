#pragma once
#include "GraphicsResource/GeomStruct.h" 
namespace TDS
{
	struct Modelpack
	{
		std::uint32_t		m_TotalMeshCnt;
		std::string			m_ModelName;
		TDSModel			m_ModelHandle;



		DLL_API Modelpack();

		DLL_API Modelpack(std::string_view Path);

		DLL_API ~Modelpack();

		DLL_API bool			LoadModelPack(std::string_view path);

		DLL_API void			Cleanup();

	};

}