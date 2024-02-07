#define NOGDI

#include "GridManager/GridManager.h"
#include "Logger/Logger.h"
#include "rapidjson/document.h"
#include "rapidJSON/writer.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/ostreamwrapper.h"
#include <fstream>
namespace TDS
{
	GridManagerBase::GridManagerBase() :m_GridMap{}, m_Grids{}
	{

	}
	GridManagerBase::~GridManagerBase()
	{

	}

	void GridManagerBase::CreateTileMap(std::uint32_t Width, std::uint32_t Height)
	{
		m_GridMap.m_MapWidth = Width;
		m_GridMap.m_MapHeight = Height;
		m_Grids.resize(m_GridMap.m_NumRows, std::vector<GridData>(m_GridMap.m_NumCols));
		UpdateGridSize();
	}

	void GridManagerBase::UpdateGridSize()
	{
		m_GridMap.CellDimension.x = static_cast<float>(m_GridMap.m_MapWidth) / m_GridMap.m_NumCols;
		m_GridMap.CellDimension.y = static_cast<float>(m_GridMap.m_MapHeight) / m_GridMap.m_NumRows;
	}

	void GridManagerBase::DeserializeGridData(std::string_view path)
	{
		std::ifstream ifs(path.data(), std::ios::in);
		if (!ifs.is_open()) {
			throw std::runtime_error("Failed to open file for reading");
		}

		rapidjson::IStreamWrapper isw(ifs);
		rapidjson::Document doc;
		doc.ParseStream(isw);

		if (doc.HasParseError()) {
			throw std::runtime_error("Failed to parse JSON");
		}

		// Deserialize m_GridMap
		const auto& gridMap = doc["GridMap"].GetObject();
		m_GridMap.m_MapWidth = gridMap["MapWidth"].GetUint();
		m_GridMap.m_MapHeight = gridMap["MapHeight"].GetUint();
		m_GridMap.m_NumRows = gridMap["NumRows"].GetInt();
		m_GridMap.m_NumCols = gridMap["NumCols"].GetInt();
		const auto& cellDimension = gridMap["CellDimension"].GetObject();
		m_GridMap.CellDimension.x = cellDimension["x"].GetDouble();
		m_GridMap.CellDimension.y = cellDimension["y"].GetDouble();

		// Deserialize m_Grids
		m_Grids.clear();
		const auto& gridsArray = doc["Grids"].GetArray();
		for (const auto& rowArray : gridsArray) {
			std::vector<GridData> row;
			for (const auto& gridObj : rowArray.GetArray()) {
				GridData grid;
				grid.m_Row = gridObj["Row"].GetInt();
				grid.m_Col = gridObj["Col"].GetInt();
				grid.m_State = static_cast<GRID_STATE>(gridObj["State"].GetInt());
				row.push_back(grid);
			}
			m_Grids.push_back(row);
		}

		ifs.close();
	}

	void GridManagerBase::SerializeGridData(std::string_view path)
	{
		std::ofstream ofs(path.data(), std::ios::out | std::ios::trunc);
		if (!ofs.is_open()) {
			throw std::runtime_error("Failed to open file for writing");
		}

		rapidjson::OStreamWrapper osw(ofs);
		rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);

		writer.StartObject();

		writer.Key("GridMap");
		writer.StartObject();
		writer.Key("MapWidth"); writer.Uint(m_GridMap.m_MapWidth);
		writer.Key("MapHeight"); writer.Uint(m_GridMap.m_MapHeight);
		writer.Key("NumRows"); writer.Int(m_GridMap.m_NumRows);
		writer.Key("NumCols"); writer.Int(m_GridMap.m_NumCols);
		writer.Key("CellDimension");
		writer.StartObject();
		writer.Key("x"); writer.Double(m_GridMap.CellDimension.x);
		writer.Key("y"); writer.Double(m_GridMap.CellDimension.y);
		writer.EndObject();
		writer.EndObject();


		writer.Key("Grids");
		writer.StartArray();
		for (const auto& row : m_Grids) {
			writer.StartArray();
			for (const auto& grid : row) {
				writer.StartObject();
				writer.Key("Row"); writer.Int(grid.m_Row);
				writer.Key("Col"); writer.Int(grid.m_Col);
				writer.Key("State"); writer.Int(static_cast<int>(grid.m_State));
				writer.EndObject();
			}
			writer.EndArray();
		}
		writer.EndArray();

		writer.EndObject();

		ofs.close();
	}

	Vec3 GridManagerBase::GetWorldPos(int Row, int Col) {
		if (Row < 0 || Row >= m_GridMap.m_NumRows || Col < 0 || Col >= m_GridMap.m_NumCols)
		{
			TDS_ERROR("Error: Grid position out of bounds.");
			return Vec3();
		}

		float x = (Col + 0.5f) * m_GridMap.CellDimension.x;
		float y = (m_GridMap.m_NumRows - Row - 0.5f) * m_GridMap.CellDimension.y;
		float z = 0.0f;

		return Vec3(x, y, z);
	}


	std::pair<int, int> GridManagerBase::GetGridPos(Vec3 worldPos) {
		if (worldPos.x < 0.f || worldPos.x > m_GridMap.m_MapWidth || worldPos.y < 0.f || worldPos.y > m_GridMap.m_MapHeight)
		{
			TDS_ERROR("Error: World position out of bounds.");
			return std::make_pair(-1, -1);
		}

		int col = static_cast<int>(worldPos.x / m_GridMap.CellDimension.x);
		int row = m_GridMap.m_NumRows - 1 - static_cast<int>(worldPos.y / m_GridMap.CellDimension.y);

		return std::make_pair(row, col);
	}


	void GridManagerBase::ResizeMap(std::uint32_t Width, std::uint32_t Height)
	{
		m_GridMap.m_MapWidth = Width;
		m_GridMap.m_MapHeight = Height;
		UpdateGridSize();
	}

	void GridManagerBase::SetNumberOfGrids(int NumRows, int numCols)
	{
		m_GridMap.m_NumRows = NumRows;
		m_GridMap.m_NumCols = numCols;
		m_Grids.resize(NumRows, std::vector<GridData>(numCols));
		UpdateGridSize();
	}

	void GridManagerBase::SetTileState(GRID_STATE tileState, Vec2 TilePos)
	{
		if (TilePos.x >= 0 && TilePos.x < m_GridMap.m_NumCols && TilePos.y >= 0 && TilePos.y < m_GridMap.m_NumRows)
			m_Grids[TilePos.y][TilePos.x].m_State = tileState;
		else
			TDS_ERROR("Error: Tile position out of bounds.");

	}
}