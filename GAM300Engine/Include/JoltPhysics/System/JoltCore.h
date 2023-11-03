#ifndef JOLTCORE_H
#define JOLTCORE_H

#include "dotnet/ImportExport.h"
#include "Logger/Logger.h"

#include <Jolt/RegisterTypes.h>
#include <Jolt/Core/Factory.h>
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Physics/PhysicsSettings.h>
namespace TDS
{
	class JoltCore
	{
	public:
		static void Init();
		static void Shutdown();

		static std::unique_ptr<JPH::JobSystemThreadPool> s_pJobSystem;
	private:

	};
}

#endif // !JOLTCORE_H
