/*
@author		Thea Sea
@email		thea.sea@digipen.edu
@brief		pathfinding grid system
			- handles pathfinding, grid system, tile system and calculation of final cost in A* pathfinding
*/
#include "AI/Pathfinder.h"
#include <cmath>
#include <chrono>
#include "components/components.h"
#include "sceneManager/sceneManager.h"

namespace TDS
{
	std::unique_ptr<Pathfinder> Pathfinder::pathfinder;
	std::unique_ptr<WaypointPathfinder> WaypointPathfinder::waypointPathfinder;

	Pathfinder::Pathfinder() :
		m_TotalRows(12),
		m_TotalCols(18),
		m_AllowDiagonals(true)
	{
		CreateGrid();

		// 6350, 2477
		// -3573, -1392
		// 2777, 1085

		//auto entities = ecs.getEntities();
		//for (int i = 0; i < entities.size(); ++i)
		//{
		//	if (ecs.getComponent<NameTag>(entities[i])->GetName() != "Main_F" &&
		//		ecs.getComponent<Transform>(entities[i])->GetPosition().y == 0)
		//	{
		//		std::cout << entities[i] << std::endl;
		//	}
		//}

		//m_Start = m_Grid[2][2];
		//m_Goal = m_Grid[2][10];

		//m_Grid[1][5]->SetTraversable(false);
		//m_Grid[2][5]->SetTraversable(false);
		//m_Grid[3][5]->SetTraversable(false);
		//m_Grid[4][5]->SetTraversable(false);
		//m_Grid[1][6]->SetTraversable(false);

		//m_Start->SetSolidColor(Vec3(0.0f, 1.0f, 0.0f));
		//m_Goal->SetSolidColor(Vec3(0.0f, 0.0f, 1.0f));

		//m_OpenList.push_back(m_Start.get());

		//FindPath();
	}

	void Pathfinder::CreateGrid()
	{
		const float startX = 30.0f;
		const float startY = 30.0f;
		const float tileSpacing = 1.0f;

		m_Grid.resize(m_TotalRows);
		for (uint32_t i = 0; i < m_TotalRows; ++i)
		{
			m_Grid[i].resize(m_TotalCols);
		}

		for (uint32_t i = 0; i < m_TotalRows; ++i)
		{
			for (uint32_t j = 0; j < m_TotalCols; ++j)
			{
				m_Grid[i][j] = std::make_shared<Tile>(i, j);

				const Vec3 tileSize = m_Grid[i][j]->m_Transform.GetScale();
				const float xPos = startX + (j * (tileSize.x + tileSpacing));
				const float yPos = startY + (i * (tileSize.y + tileSpacing));

				m_Grid[i][j]->m_Transform.SetPosition(Vec3(xPos, yPos, -1.0f));
			}
		}

		AssignNeighbors();
	}

	void Pathfinder::AssignNeighbors()
	{
		for (uint32_t i = 0; i < m_TotalRows; ++i)
		{
			for (uint32_t j = 0; j < m_TotalCols; ++j)
			{
				Tile* currentTile = m_Grid[i][j].get();

				if (i > 0) currentTile->SetNeightbor(m_Grid[i - 1][j].get());												// Top tile
				if (j < m_TotalCols - 1) currentTile->SetNeightbor(m_Grid[i][j + 1].get());									// Right tile
				if (i < m_TotalRows - 1) currentTile->SetNeightbor(m_Grid[i + 1][j].get());									// Bottom tile
				if (j > 0) currentTile->SetNeightbor(m_Grid[i][j - 1].get());												// Left tile

				if (!m_AllowDiagonals)
				{
					continue;
				}

				if (i > 0 && j > 0) currentTile->SetNeightbor(m_Grid[i - 1][j - 1].get());									// Top-left tile
				if (i > 0 && j < m_TotalCols - 1) currentTile->SetNeightbor(m_Grid[i - 1][j + 1].get());					// Top-right tile
				if (i < m_TotalRows - 1 && j > 0) currentTile->SetNeightbor(m_Grid[i + 1][j - 1].get());					// Bottom-left tile
				if (i < m_TotalRows - 1 && j < m_TotalCols - 1) currentTile->SetNeightbor(m_Grid[i + 1][j + 1].get());		// Bottom-right tile
			}
		}
	}

	void Pathfinder::MarkAsProcessed(Tile* _tile)
	{
		// Move _tile from m_OpenList to m_ClosedList
		const auto iter = std::find(m_OpenList.begin(), m_OpenList.end(), _tile);

		if (iter != m_OpenList.end())
		{
			m_OpenList.erase(iter);
			m_ClosedList.push_back(_tile);
		}
	}

	void Pathfinder::CreatePath(Tile* _tile)
	{
		Tile* pathTile = _tile;
		while (pathTile->GetParent() != nullptr)
		{
			if (pathTile->GetParent() == m_Start.get())
			{
				return;
			}

			pathTile = pathTile->GetParent();
			PathTiles.emplace_back(pathTile);
		}
	}

	void Pathfinder::DisplayPath()
	{
		for (Tile* pathTile : PathTiles)
		{
			pathTile->SetSolidColor(Vec3(0.0f, 1.0f, 0.0f));
		}
	}

	void Pathfinder::DisplayPathAnimated(const double _dt, const float _animSpeed)
	{
		static size_t index = 0;

		currentTime += 1.0 * _dt;
		if (currentTime < _animSpeed)
		{
			return;
		}

		if (index < PathTiles.size())
		{
			++index;
			PathTiles[PathTiles.size() - index]->SetSolidColor(Vec3(0.0f, 1.0f, 0.0f));
			currentTime = 0.0;
		}
	}

	uint32_t Pathfinder::CalculateDistance(Tile* _currentTile, Tile* _nextTile)
	{
		const uint32_t adjacentMoveCost = 10;
		const uint32_t diagonalMoveCost = 14;

		int32_t dx = std::abs(static_cast<int32_t>(_currentTile->GetGridX() - _nextTile->GetGridX()));
		int32_t dy = std::abs(static_cast<int32_t>(_currentTile->GetGridY() - _nextTile->GetGridY()));

		if (!m_AllowDiagonals)
		{
			// Use the standard Manhattan distance heuristic if diagonals are not allowed
			return adjacentMoveCost * (dx + dy);
		}

		// Otherwise, use a modified heuristic to take diagonals into consideration
		if (dx > dy)
		{
			return diagonalMoveCost * dy + adjacentMoveCost * (dx - dy);
		}

		return diagonalMoveCost * dx + adjacentMoveCost * (dy - dx);
	}


	/*
		A* Pathfinding referenced, algorithm referenced from rabin's assignment
	*/
	void Pathfinder::FindPath()
	{
		auto startTime = std::chrono::high_resolution_clock::now();

		// Reset
		PathTiles.clear();
		m_ClosedList.clear();
		m_OpenList.clear();
		m_OpenList.emplace_back(m_Start.get());

		for (int row = 0; row < m_TotalRows; ++row)
		{
			for (int col = 0; col < m_TotalCols; ++col)
			{
				m_Grid[row][col]->SetGCost(UINT32_MAX);
			}
		}

		while (!m_OpenList.empty())
		{
			Tile* currentTile = *m_OpenList.begin();

			for (Tile* tile : m_OpenList)
			{
				if (tile->GetFCost() < currentTile->GetFCost() ||
					(tile->GetFCost() == currentTile->GetFCost() && tile->GetHCost() < currentTile->GetHCost()))
				{
					currentTile = tile;
				}
			}

			MarkAsProcessed(currentTile);

			if (currentTile == m_Goal.get())
			{
				const auto endTime = std::chrono::high_resolution_clock::now();
				const auto timeTaken = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
				printf("Found path at location <%d, %d> in %lld ms\n", currentTile->GetGridX(), currentTile->GetGridY(), timeTaken);
				CreatePath(currentTile);
				//DisplayPath();
				return;
			}

			for (Tile* neighborTile : currentTile->GetNeighbors())
			{
				if (!neighborTile->GetTraversable() ||
					std::find(m_ClosedList.begin(), m_ClosedList.end(), neighborTile) != m_ClosedList.end())
				{
					continue;
				}

				if (currentTile->GetGCost() == UINT32_MAX)
					currentTile->SetGCost(0);

				float gCost = currentTile->GetGCost() + CalculateDistance(currentTile, neighborTile);

				if (gCost < neighborTile->GetGCost())
				{
					neighborTile->SetGCost(gCost);
					neighborTile->SetHCost(CalculateDistance(neighborTile, m_Goal.get()));
					neighborTile->SetParent(currentTile);

					const auto iter = std::find(m_OpenList.begin(), m_OpenList.end(), neighborTile);
					if (iter == m_OpenList.end())
					{
						m_OpenList.push_back(neighborTile);
					}
				}
			}
		}

		printf("Pathfinder failed to find a solution\n");
		return;
	}

	// For ECS System
	void Pathfinder::Initialize()
	{
		pathfinder->GetInstance();
		
		// Register the grid
		
		for (size_t i = 0; i < pathfinder->GetGrid().size(); ++i)
		{
		    for (size_t j = 0; j < pathfinder->GetGrid()[i].size(); ++j)
		    {
		        // do some RegisterEntity using pathfinder.GetGrid()[i][j].get();
		    }
		}
	}
	void Pathfinder::Update(const float dt, const std::vector<EntityID>& entities, Transform* _transform)
	{
		// Render grid
		
		//gridrender.Render(commandBuffer, frame);
		//gridrender.SetColour(0, 0, Color(1.0f, 0.0f, 0.0f, 1.0f));
		//pathfinder->DisplayPathAnimated(GetDeltaTime()); //display path
	}

	std::unique_ptr<Pathfinder>& Pathfinder::GetInstance()
	{
		if (pathfinder == nullptr)
		{
			pathfinder = std::make_unique<Pathfinder>();
		}

		return pathfinder;
	}

	void Pathfinder::ReadLayout(std::string path)
	{
		std::string filePath = SceneManager::GetInstance()->getAssetPath();
		filePath += path;

		std::ifstream is;
		is.open(filePath);
		std::string currentRow;

		if (!is.good())
		{
			return;
		}

		m_TotalRows = 0;
		m_TotalCols = 0;
		while (is >> currentRow)
		{
			if (m_TotalCols == 0)
				m_TotalCols = currentRow.size();

			++m_TotalRows;
		}

		is.close();
		is.open(filePath);

		CreateGrid();

		int currentRowCount = 0;
		while (is >> currentRow)
		{
			for (int i = 0; i < m_TotalCols; ++i)
			{
				if (currentRow[i] == '0')
				{
					m_Grid[currentRowCount][i]->SetTraversable(false);
				}
				else
				{
					m_Grid[currentRowCount][i]->SetTraversable(true);
				}
			}
			
			++currentRowCount;
		}

		is.close();
	}

	void Pathfinder::SetTopLeft(Vec2 topLeft)
	{
		topLeftWorldPosition = topLeft;
	}

	void Pathfinder::SetGridSize(Vec2 _gridSize)
	{
		gridSize = _gridSize;
	}

	void Pathfinder::SetStart(int row, int col)
	{
		m_Start = m_Grid[row][col];
	}

	void Pathfinder::SetGoal(int row, int col)
	{
		m_Goal = m_Grid[row][col];
	}

	Vec2 Pathfinder::GetNextStep()
	{
		if (!PathTiles.size())
		{
			FindPath();
		}

		if (!PathTiles.size()) // Still no path
		{
			return Vec2(0.0f, 0.0f);
		}

		Vec2 nextStep = topLeftWorldPosition + Vec2(gridSize.x * PathTiles[0]->GetGridX(), gridSize.y * PathTiles[0]->GetGridY());
		PathTiles.erase(PathTiles.begin());

		return nextStep;
	}

	// Waypoint Pathfinder ==================================================================
	std::unique_ptr<WaypointPathfinder>& WaypointPathfinder::GetInstance()
	{
		if (waypointPathfinder == nullptr)
		{
			waypointPathfinder = std::make_unique<WaypointPathfinder>();
		}

		return waypointPathfinder;
	}
	void WaypointPathfinder::ClearRoomWaypoints()
	{
		rooms.clear();
		waypoints.clear();
	}
	int WaypointPathfinder::AddRoom(Vec2 topLeft, Vec2 bottomRight)
	{
		Room newRoom{ rooms.size(), topLeft, bottomRight };
		rooms.emplace_back(newRoom);
		return newRoom.roomID;
	}
	int WaypointPathfinder::AddWaypoint(Vec2 waypointPosition)
	{
		Waypoint newWaypoint{ waypoints.size(), waypointPosition };
		waypoints.emplace_back(newWaypoint);
		return newWaypoint.waypointID;
	}
	void WaypointPathfinder::AddWaypointRoomConnection(int waypointID, int roomID)
	{
		waypoints[waypointID].rooms.emplace_back(&rooms[roomID]);
		rooms[roomID].waypoints.emplace_back(&waypoints[waypointID]);
	}
	void WaypointPathfinder::AddNeighbour(int waypointID, int neighbourWaypointID)
	{
		waypoints[waypointID].neighbourWaypoints.emplace_back(&waypoints[neighbourWaypointID]);
		waypoints[waypointID].neighbourWaypointsDistance.emplace_back(Vec2::Distance(waypoints[waypointID].position, waypoints[neighbourWaypointID].position));
	}

	int WaypointPathfinder::GetRoomID(Vec2 position)
	{
		for (int i = 0; i < rooms.size(); ++i)
		{
			if (rooms[i].topLeftBoundary.x <= position.x && rooms[i].bottomRightBoundary.x >= position.x &&
				rooms[i].topLeftBoundary.y <= position.y && rooms[i].bottomRightBoundary.y >= position.y)
			{
				return i;
			}
		}

		return rooms.size();
	}

	void WaypointPathfinder::FindPath(Vec2 start, Vec2 goal)
	{
		// 1. Find start & goal room IDs
		// 2. If rooms are different, find path from waypoints
		// 3. If rooms are the same, walk straight to the goal

		// 1
		goalPosition = goal;
		int startRoom = GetRoomID(start);
		int goalRoom = GetRoomID(goal);
		foundPath.clear();

		// 2
		if (startRoom == goalRoom)
		{
			return;
		}

		// 3
		// Reset
		closedList.clear();
		openList.clear();

		for (int i = 0; i < waypoints.size(); ++i)
		{
			waypoints[i].gCost = FLT_MAX;
			waypoints[i].parent = nullptr;
		}

		// add in all waypoints that are in same room as start
		Waypoint* firstWaypoint = nullptr;
		float distance = FLT_MAX;
		for (auto waypoint : rooms[startRoom].waypoints)
		{
			float currentDistance = Vec2::Distance(waypoint->position, start);
			if (firstWaypoint == nullptr || currentDistance < distance)
			{
				firstWaypoint = waypoint;
				distance = currentDistance;
			}
		}
		openList.emplace_back(firstWaypoint);
		firstWaypoint->gCost = Vec2::Distance(start, firstWaypoint->position);

		while (!openList.empty())
		{
			Waypoint* currentWaypoint = openList[0];
			int currentWaypointOpenListID = 0;

			for (int i = 0; i < openList.size(); ++i)
			{
				if (openList[i]->fCost < currentWaypoint->fCost ||
					(openList[i]->fCost == currentWaypoint->fCost && openList[i]->hCost < currentWaypoint->hCost))
				{
					currentWaypoint = openList[i];
					currentWaypointOpenListID = i;
				}
			}

			openList.erase(openList.begin() + currentWaypointOpenListID);
			closedList.emplace_back(currentWaypoint);

			for (auto room : currentWaypoint->rooms) // checking for goal
			{
				if (room->roomID == goalRoom) // same room as goal
				{
					// Create path
					foundPath.emplace_back(goal);

					Waypoint* createPathWaypoint = currentWaypoint;
					while (createPathWaypoint != nullptr)
					{
						foundPath.emplace(foundPath.begin(), createPathWaypoint->position);
						createPathWaypoint = createPathWaypoint->parent;
					}

					return;
				}
			}

			for (int i = 0; i < currentWaypoint->neighbourWaypoints.size(); ++i)
			{
				Waypoint* neighbourWaypoint = currentWaypoint->neighbourWaypoints[i];
				float neighbourGCost = currentWaypoint->gCost + currentWaypoint->neighbourWaypointsDistance[i];

				if (neighbourGCost < neighbourWaypoint->gCost)
				{
					neighbourWaypoint->gCost = neighbourGCost;
					neighbourWaypoint->hCost = Vec2::Distance(neighbourWaypoint->position, goal);
					neighbourWaypoint->fCost = neighbourWaypoint->gCost + neighbourWaypoint->hCost;
					neighbourWaypoint->parent = currentWaypoint;

					const auto iter = std::find(openList.begin(), openList.end(), neighbourWaypoint);
					if (iter == openList.end())
					{
						openList.push_back(neighbourWaypoint);
					}
				}
			}
		}

		printf("Pathfinder failed to find a solution\n");
		return;
	}

	Vec2 WaypointPathfinder::NextStep()
	{
		if (!foundPath.size()) // Walk straight to goal
		{
			return goalPosition;
		}

		Vec2 toReturn = foundPath[0];
		foundPath.erase(foundPath.begin());

		std::cout << toReturn.x << "\t" << toReturn.y << std::endl;
		return toReturn;
	}
}

