#include "Rendering/UiSystem.h"
#include "components/components.h"
#include "Rendering/Renderer2D.h"
#include "Rendering/GraphicsManager.h"
#include "vulkanTools/Renderer.h"
#define _BATCH
namespace TDS
{
	void UiSystem::Init()
	{
	}
	void UiSystem::Update(const float dt, const std::vector<EntityID>& entities, Transform* transform, UISprite* _Sprite)
	{

		if (GraphicsManager::getInstance().IsViewingFrom2D() == false)
			return;

		if (_Sprite == nullptr)
			return;
		
#ifdef _BATCH
		Batch2DList& batch = Renderer2D::GetInstance()->GetBatchList();
		
		
		for (size_t i = 0; i < entities.size(); ++i)
		{
			batch.AddToBatch(&_Sprite[i], &transform[i]);
		}
		batch.PrepareBatch();

		auto cmdBuffer = GraphicsManager::getInstance().getCommandBuffer();
		auto frame = GraphicsManager::getInstance().GetSwapchainRenderer().getFrameIndex();
		Renderer2D::GetInstance()->Update(cmdBuffer, frame);
		Renderer2D::GetInstance()->Draw(cmdBuffer, frame);
		batch.Clear();
#else
		auto cmdBuffer = GraphicsManager::getInstance().getCommandBuffer();
		auto frame = GraphicsManager::getInstance().GetSwapchainRenderer().getFrameIndex();
		Renderer2D::GetInstance()->UpdateNonBatch(_Sprite, transform, cmdBuffer, entities.size(), frame);

#endif


	}
}