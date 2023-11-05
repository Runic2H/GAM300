#ifndef DEBUG_RENDERER
#define DEBUG_RENDERER
#include "vulkanTools/vulkanInstance.h"
#include "dotnet/ImportExport.h"
#include "components/components.h"
#include "vulkanTools/VulkanPipeline.h"
namespace TDS {
	class DebugRenderer {
	public:
		DLL_API DebugRenderer(VulkanInstance& Instance);
		DLL_API ~DebugRenderer();
		DebugRenderer(const DebugRenderer&) = delete;
		DebugRenderer& operator=(const DebugRenderer&) = delete;
		DLL_API void Render(GraphicsComponent* Gp, Transform* Transform);
		DLL_API VulkanPipeline& GetPipeline();
	private:
		VulkanInstance& m_Instance;
		std::unique_ptr<VulkanPipeline> m_Pipeline;
	};
}
#endif // !DEBUG_RENDERER