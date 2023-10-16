#pragma once
#include "Rendering/RenderLayer.h"
#include "vulkan/vulkan.h"
namespace TDS
{
	//Wrapper which func pointers will send to graphicsManager to handle
	class Renderer;

	class ImguiLayer final : public RenderLayer
	{
		public:
			virtual void Setup(WindowsWin* window);
			virtual void Init();
			virtual void StartFrame();
			virtual void EndFrame();
			virtual void ShutDown();
			virtual void Render();
		private:
			VkDescriptorPool m_ImGuiDescPool = nullptr;

	};
}