/*!*************************************************************************
****
\file vulkanDebugger.h
\author Ng Zuo Xian Amadeus
\par DP email: ng.z@digipen.edu
\par Course: CSD3400
\par Section: a
\date 22-9-2023
\brief  Contains the Debug Class and its member functions
****************************************************************************
***/
#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <assert.h>

#include <vulkan/vulkan.h>

using namespace std::string_view_literals;
namespace TDS
{
	namespace Debug
	{
		//setup debugger for specified instance
		void setupDebugger(const VkInstance& instance);
		//free debugger in specified instance
		void freeDebugger(const VkInstance& instance);
	}

}//namespace TDS


