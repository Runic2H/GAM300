#pragma once
#include "vulkanTools/VMATypes/VMABuffer.h"
#include "TDSMath.h"
namespace TDS
{
	enum class GRID_STATE
	{
		CLEAR = 0,
		WALL = 1
	};


	struct GridData
	{
		int m_Row, m_Col;
		GRID_STATE m_State;
	};

	struct Map
	{
		Vec2 CellDimension;
	};
	struct GridMap
	{
		std::uint32_t m_MapWidth{0}, m_MapHeight{ 0 };
		int m_NumRows = 1;
		int m_NumCols = 1;
		Vec2 CellDimension = { 10.f, 10.f };

		inline int TotalNumberOfGrids() const
		{
			return m_NumRows * m_NumCols;
		}

	};

	class GridManagerBase
	{
	private:
		GridMap m_GridMap;
		std::vector<std::vector<GridData>> m_Grids;

	public:
		GridManagerBase();
		~GridManagerBase();

		inline GridMap& GetMapInfo()
		{
			return m_GridMap;
		}

		void CreateTileMap(std::uint32_t Width, std::uint32_t Height);

		void ResizeMap(std::uint32_t Width, std::uint32_t Height);

		void SetNumberOfGrids(int NumRows, int numCols);

		void SetTileState(GRID_STATE tileColor, Vec2 TilePos);

		void UpdateGridSize();

		void DeserializeGridData(std::string_view path);

		void SerializeGridData(std::string_view path);

		Vec3 GetWorldPos(int Row, int Col);

		std::pair<int, int> GetGridPos(Vec3 worldPos);


	};
}