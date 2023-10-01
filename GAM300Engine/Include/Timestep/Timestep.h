/*!*****************************************************************************
 * \file          Timestep.h
 * \author        Cheang Wen Ding
 * \par DP email: cheang.w@digipen.edu
 * \par Course:   CSD3400
 * \par Section:  A
 * \date          01/10/2023
 * \brief         Timestep class that handles the delta time & fps.
 *******************************************************************************/
#ifndef TIMESTEP_H
#define TIMESTEP_H

#include "dotnet/ImportExport.h"

namespace TDS
{
class DLL_API TimeStep
{
public:
	/*!*************************************************************************
	 * Getters for delta time and fps
	 ***************************************************************************/
	static float GetDeltaTime() { return mDeltaTime; }
	static float GetFixedDeltaTime() { return mFixedTime; }
	static float GetFps() { return mFps; }
	/*!*************************************************************************
	 * Static function that updates the delta time and fps called in the 
	 * main loop
	 ***************************************************************************/
	static void CalculateDeltaTime();

private:
	// functions

private:
	// variables
	static float mDeltaTime;
	static float mFixedTime;
	static float mFps;
	static std::chrono::time_point<std::chrono::high_resolution_clock>InternalClock;

};


	
}




#endif // !TIMESTEP_H
