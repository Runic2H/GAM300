#ifndef PATHFINDER
#define PATHFINDER
/*
@author		Thea Sea
@email		thea.sea@digipen.edu
@brief		pathfinding grid system
			- handles pathfinding, grid system, tile system and calculation of final cost in A* pathfinding
*/
#include "Tile.h"
#include <list>
#include <memory>

namespace TDS
{
	class Pathfinder
	{
	public:
		Pathfinder();

		void DisplayPathAnimated(const double _dt, const float _animSpeed = 0.5f);
		const std::vector<std::vector<std::shared_ptr<Tile>>>& GetGrid() const { return m_Grid; }

		// For ECS System
		static void Initialize();
		static void Update(const float dt, const std::vector<EntityID>& entities, Transform* _transform);
		DLL_API static std::unique_ptr<Pathfinder>& GetInstance();

		DLL_API void ReadLayout(std::string path);
		DLL_API void SetTopLeft(Vec2 topLeft);
		DLL_API void SetGridSize(Vec2 _gridSize);

		DLL_API void SetStart(int row, int col);
		DLL_API void SetGoal(int row, int col);
		DLL_API Vec2 GetNextStep();

		// TEST
		//DLL_API 

	private:
		void FindPath();
		void CreateGrid();
		void AssignNeighbors();
		void MarkAsProcessed(Tile* _tile);
		void CreatePath(Tile* _tile);
		void DisplayPath();
		uint32_t CalculateDistance(Tile* _currentTile, Tile* _nextTile);

	private:
		static std::unique_ptr<Pathfinder> pathfinder;

		uint32_t m_TotalRows;
		uint32_t m_TotalCols;
		bool m_AllowDiagonals;
		std::vector<std::vector<std::shared_ptr<Tile>>> m_Grid;
		std::shared_ptr<Tile> m_Start;
		std::shared_ptr<Tile> m_Goal;
		std::list<Tile*> m_OpenList;
		std::list<Tile*> m_ClosedList;

		Vec2 topLeftWorldPosition;
		Vec2 gridSize;
		Vec2 currentTile;

		// Debug
		std::vector<Tile*> PathTiles;
		double currentTime{ 0.0 };
	};

	class Waypoint;
	class Room
	{
	public:
		int roomID;
		Vec2 topLeftBoundary;
		Vec2 bottomRightBoundary;
		std::vector<Waypoint*> waypoints;
	};

	class Waypoint
	{
	public:
		int waypointID;
		Vec2 position;
		std::vector<Room*> rooms;							// rooms the waypoint is associated with
		std::vector<Waypoint*> neighbourWaypoints;

		// For pathfinding
		std::vector<float> neighbourWaypointsDistance;
		float gCost;										// distance between the current node and the start node
		float hCost;										// heuristic — estimated distance from the current node to the end node
		float fCost;										// total cost of node
		Waypoint* parent;
	};

	class WaypointPathfinder
	{
	public:
		DLL_API static std::unique_ptr<WaypointPathfinder>& GetInstance();

		DLL_API void ClearRoomWaypoints();

		DLL_API int AddRoom(Vec2 topLeft, Vec2 bottomRight); // Returns room ID
		DLL_API int AddWaypoint(Vec2 waypointPosition); // Returns waypoint ID
		DLL_API void AddWaypointRoomConnection(int waypointID, int roomID);
		DLL_API void AddNeighbour(int waypointID, int neighbourWaypointID);

		DLL_API int GetRoomID(Vec2 position);

		DLL_API void FindPath(Vec2 start, Vec2 goal);
		DLL_API Vec2 NextStep();

	private:
		static std::unique_ptr<WaypointPathfinder> waypointPathfinder;

		std::vector<Room> rooms;
		std::vector<Waypoint> waypoints;

		std::vector<Waypoint*> openList;
		std::vector<Waypoint*> closedList;
		std::vector<Vec2> foundPath;

		Vec2 goalPosition;
	};
}

#endif #PATHFINDER