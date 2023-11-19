#include "Rendering/FontSystem.h"
#include "Rendering/FontRenderer.h"
#include "Rendering/GraphicsManager.h"
#include "vulkanTools/Renderer.h"
namespace TDS
{
	void FontSystem::Init()
	{
	}
	void FontSystem::Update(const float dt, const std::vector<EntityID>& entities, Transform* transform, FontComponent* _font)
	{
		//if (_font == nullptr)
		//	return;

		//FontBatch& batch = FontRenderer::GetInstance()->GetBatchList();

		//for (size_t i = 0; i < entities.size(); ++i)
		//	batch.AddToBatch(&_font[i], &transform[i]);

		//batch.PrepareBatch();

		//auto cmdBuffer = GraphicsManager::getInstance().getCommandBuffer();
		//auto frame = GraphicsManager::getInstance().GetSwapchainRenderer().getFrameIndex();
		//FontRenderer::GetInstance()->Update(cmdBuffer, frame);
		//FontRenderer::GetInstance()->Draw(cmdBuffer, frame);
		//batch.Clear();
	}
}