#include "Pathfinder.hxx"
#include "TypeConversion.hxx"

namespace ScriptAPI
{
	void Pathfinder::ReadLayoutFile(System::String^ file)
	{
		System::Console::WriteLine(file);
		TDS::Pathfinder::GetInstance()->ReadLayout(toStdString(file));
	}

	void Pathfinder::SetTopLeft(Vector2 topLeft)
	{
		TDS::Pathfinder::GetInstance()->SetTopLeft(TDS::floatsToVec2(topLeft.X, topLeft.Y));
	}

	void Pathfinder::SetGridSize(Vector2 gridSize)
	{
		TDS::Pathfinder::GetInstance()->SetGridSize(TDS::floatsToVec2(gridSize.X, gridSize.Y));
	}

	void Pathfinder::SetStart(int X, int Y)
	{
		TDS::Pathfinder::GetInstance()->SetStart(X, Y);
	}

	void Pathfinder::SetGoal(int X, int Y)
	{
		TDS::Pathfinder::GetInstance()->SetGoal(X, Y);
	}

	Vector2 Pathfinder::GetNextStep()
	{
		TDS::Vec2 toReturn = TDS::Pathfinder::GetInstance()->GetNextStep();
		return Vector2(toReturn.x, toReturn.y);
	}

	// Waypoint Pathfinder ========================================================================
	void WaypointPathfinder::ClearRoomWaypoints()
	{
		TDS::WaypointPathfinder::GetInstance()->ClearRoomWaypoints();
	}
	int WaypointPathfinder::AddRoom(Vector2 topLeft, Vector2 bottomRight)
	{
		return TDS::WaypointPathfinder::GetInstance()->AddRoom(TDS::floatsToVec2(topLeft.X, topLeft.Y), TDS::floatsToVec2(bottomRight.X, bottomRight.Y));
	}
	int WaypointPathfinder::AddWaypoint(Vector2 waypointPosition)
	{
		return TDS::WaypointPathfinder::GetInstance()->AddWaypoint(TDS::floatsToVec2(waypointPosition.X, waypointPosition.Y));
	}
	void WaypointPathfinder::AddWaypointRoomConnection(int waypointID, int roomID)
	{
		return TDS::WaypointPathfinder::GetInstance()->AddWaypointRoomConnection(waypointID, roomID);
	}
	void WaypointPathfinder::AddNeighbour(int waypoint, int neighbourWaypoint)
	{
		return TDS::WaypointPathfinder::GetInstance()->AddNeighbour(waypoint, neighbourWaypoint);
	}
	
	void WaypointPathfinder::FindPath(Vector2 _start, Vector2 goal)
	{
		TDS::WaypointPathfinder::GetInstance()->FindPath(TDS::floatsToVec2(_start.X, _start.Y), TDS::floatsToVec2(goal.X, goal.Y));
		TDS::Vec2 nextStepVec2 = TDS::WaypointPathfinder::GetInstance()->NextStep();
		nextStep = Vector2(nextStepVec2.x, nextStepVec2.y);
	}
	Vector2 WaypointPathfinder::NextStep(Vector2 currentPosition, float speed)
	{
		TDS::Vec2 toReturnVec2 = TDS::Vec2::MoveTowards(TDS::floatsToVec2(currentPosition.X, currentPosition.Y), TDS::floatsToVec2(nextStep.X, nextStep.Y), speed * 5);
		Vector2 toReturn = Vector2(toReturnVec2.x, toReturnVec2.y);

		if (nextStep == toReturn)
		{
			TDS::Vec2 nextStepVec2 = TDS::WaypointPathfinder::GetInstance()->NextStep();
			nextStep = Vector2(nextStepVec2.x, nextStepVec2.y);
		}

		return toReturn;
	}
}