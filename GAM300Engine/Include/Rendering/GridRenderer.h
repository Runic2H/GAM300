#pragma once
#include "AssetManagement/AssetManager.h"
namespace TDS
{
	class VMABuffer;
	class VulkanPipeline;
	class AssetModel;

	struct alignas(16) GridUniform
	{
		Mat4 model = Mat4::identity();
		Mat4 view = Mat4::identity();
		Mat4 proj = Mat4::identity();
		Vec4 gridColor = { 0.f, 0.f, 0.f, 0.f };
	};

	struct alignas(16) GridLineUniform
	{
		Mat4 model;
		Mat4 view;
		Mat4 proj;
	};

	class GridManagerBase;
	class GridRenderer
	{
	public:
		void Init();
		void Render();
		void ShutDown();
		void SetColour(int row, int col, Color color);

	private:
		std::array<GridUniform, 5000> m_GridUniform;
		std::array<GridLineUniform, 5000> m_GridLineUniform;
		std::shared_ptr<GridManagerBase> m_pGridManager = nullptr;
		std::shared_ptr<VMABuffer> m_VertexBuffer = nullptr;
		std::shared_ptr<VMABuffer> m_IndexBuffer = nullptr;
		std::shared_ptr<VulkanPipeline> m_GridPipeline = nullptr;
		std::shared_ptr<VulkanPipeline> m_DebugPipeline = nullptr;
		std::shared_ptr<AssetManager> m_pAssetManager = nullptr;
		TypeReference<AssetModel> m_GridModel;



	};
}