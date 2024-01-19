#pragma once
#include "GraphicsResource/GeomStruct.h" 
namespace TDS
{
	struct Modelpack
	{
		TDSModel			m_ModelHandle;
		std::string			m_ModelName;

		DLL_API Modelpack();

		DLL_API Modelpack(std::string_view Path);

		DLL_API ~Modelpack();

		DLL_API bool			LoadModelPack(std::string_view path);

		DLL_API void			Cleanup();

	};

}