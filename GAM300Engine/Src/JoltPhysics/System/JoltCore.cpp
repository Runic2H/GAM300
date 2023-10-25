#include "JoltPhysics/System/JoltCore.h"

namespace TDS
{
	std::unique_ptr<JPH::JobSystemThreadPool> JoltCore::s_pJobSystem;
	// Callback for traces, connect this to your own trace function if you have one
	static void TraceImpl(const char* inFMT, ...)
	{
		// Format the message
		va_list list;
		va_start(list, inFMT);
		char buffer[1024];
		vsnprintf(buffer, sizeof(buffer), inFMT, list);
		va_end(list);

		// Print to the TTY
		TDS_TRACE(buffer);
	}

#ifdef JPH_ENABLE_ASSERTS

	// Callback for asserts, connect this to your own assert handler if you have one
	static bool AssertFailedImpl(const char* inExpression, const char* inMessage, const char* inFile, JPH::uint inLine)
	{
		// Print to the TTY
		std::cout << inFile << ":" << inLine << ": (" << inExpression << ") " << (inMessage != nullptr ? inMessage : "") << std::endl;
		// Breakpoint
		return true;
	};

#endif // JPH_ENABLE_ASSERTS

	void JoltCore::Init()
	{
		using namespace JPH;
		// Register allocation hook
		RegisterDefaultAllocator();

		// Install callbacks
		Trace = TraceImpl;
		JPH_IF_ENABLE_ASSERTS(AssertFailed = AssertFailedImpl;)

			// Create a factory
			Factory::sInstance = new Factory();

		// Register all Jolt physics types
		RegisterTypes();

		s_pJobSystem = std::make_unique<JobSystemThreadPool>(cMaxPhysicsJobs, cMaxPhysicsBarriers, thread::hardware_concurrency() - 1);


	}

	void JoltCore::Shutdown()
	{
		using namespace JPH;
		
		s_pJobSystem = nullptr;

		delete Factory::sInstance;
		Factory::sInstance = nullptr;

		Trace = nullptr;
	}

}
