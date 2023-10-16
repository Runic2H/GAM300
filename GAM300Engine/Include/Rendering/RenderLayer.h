#pragma once
#include "dotnet/ImportExport.h"
namespace TDS
{
	class Renderer;
	class WindowsWin;
	class DLL_API RenderLayer
	{
	public:
		virtual void Setup(WindowsWin* window) = 0;
		virtual void Init() = 0;
		virtual void StartFrame() = 0;
		virtual void EndFrame() = 0;
		virtual void ShutDown() = 0;
		virtual void Render() = 0;

	};
}