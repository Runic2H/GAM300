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
		void setupDebugger(const VkInstance& instance);

		void freeDebugger(const VkInstance& instance);
	}

}//namespace TDS


