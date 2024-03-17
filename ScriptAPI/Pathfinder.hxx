#pragma once
#include "IncludeFromEngine.hxx"
#include "AI/Pathfinder.h"
#include "Vector2.hxx"

namespace ScriptAPI
{
	public ref class Pathfinder
	{
	public:
		static void ReadLayoutFile(System::String^ file);
		static void SetTopLeft(Vector2 topLeft);
		static void SetGridSize(Vector2 gridSize);

		static void SetStart(int X, int Y);
		static void SetGoal(int X, int Y);
		static Vector2 GetNextStep();
	};

	public ref class WaypointPathfinder
	{
	public:
		static void ClearRoomWaypoints();
		static int AddRoom(Vector2 topLeft, Vector2 bottomRight); // Returns room ID
		static int AddWaypoint(Vector2 waypointPosition); // Returns waypoint ID
		static void AddWaypointRoomConnection(int waypointID, int roomID);
		static void AddNeighbour(int waypoint, int neighbourWaypoint);

		static void FindPath(Vector2 start, Vector2 goal);
		static Vector2 NextStep(Vector2 currentPosition, float speed);

		static bool SameRoom(Vector2 start, Vector2 goal);

		static Vector2 nextStep;
	};
}