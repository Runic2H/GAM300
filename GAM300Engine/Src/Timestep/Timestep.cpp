/*!*****************************************************************************
 * \file          Timestep.cpp
 * \author        Cheang Wen Ding
 * \par DP email: cheang.w@digipen.edu
 * \par Course:   CSD3400
 * \par Section:  A
 * \date          01/10/2023
 * \brief         Implementation of Timestep class.
 *******************************************************************************/
#include "Timestep/Timestep.h"

namespace TDS
{	
	float TimeStep::mDeltaTime = 0.0f;
	float TimeStep::mFixedTime = 0.0166666f;
	float TimeStep::mFps = 0.0f;
	std::chrono::time_point<std::chrono::high_resolution_clock> TimeStep::InternalClock = std::chrono::high_resolution_clock::now();

	void TimeStep::CalculateDeltaTime()
	{
		auto  Now = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> ElapsedSeconds = Now - InternalClock;
		mDeltaTime = ElapsedSeconds.count();
		mFps = 1.0f / mDeltaTime;
		InternalClock = Now;
	}


	
}
