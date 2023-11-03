#pragma once
#include "pch.h"
#include "DirectXTex.h"
#include "CompilerSettings.h"
namespace TDS
{


	namespace DDSConverter
	{

		std::wstring StringToWstring(std::string_view cString);
		void Init();
		void ConvertToDDS(std::string_view path, std::string_view outPath, DXGI_FORMAT ddsFormat = DXGI_FORMAT_UNKNOWN);
		void Destroy();
	}



}