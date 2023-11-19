#include "Rendering/UiSystem.h"
#include "components/components.h"
#include "Rendering/Renderer2D.h"
#include "Rendering/FontSystem.h"
#include "Rendering/FontRenderer.h"
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

		//if (GraphicsManager::getInstance().IsViewingFrom2D() == false)
		//	return;

		if (_Sprite == nullptr)
			return;
		
		auto frame = GraphicsManager::getInstance().GetSwapchainRenderer().getFrameIndex();
		auto cmdBuffer = GraphicsManager::getInstance().getCommandBuffer();
		FontBatch& Fontbatch = FontRenderer::GetInstance()->GetBatchList();
		SpriteBatch& Spritebatch = Renderer2D::GetInstance()->GetBatchList();
		for (size_t i = 0; i < entities.size(); ++i)
		{
			if (_Sprite[i].m_IsFont)
				Fontbatch.AddToBatch(&_Sprite[i], &transform[i]);
			
			else
				Spritebatch.AddToBatch(&_Sprite[i], &transform[i]);
			
		}
		Spritebatch.PrepareBatch();
		Fontbatch.PrepareBatch();


		Renderer2D::GetInstance()->Update(cmdBuffer, frame);
		Renderer2D::GetInstance()->Draw(cmdBuffer, frame);

		FontRenderer::GetInstance()->Update(cmdBuffer, frame);
		FontRenderer::GetInstance()->Draw(cmdBuffer, frame);

		Spritebatch.Clear();
		Fontbatch.Clear();


		/*if (_Sprite->m_IsFont)
		{
			FontBatch& batch = FontRenderer::GetInstance()->GetBatchList();

			for (size_t i = 0; i < entities.size(); ++i)
				batch.AddToBatch(&_Sprite[i], &transform[i]);

			batch.PrepareBatch();
			FontRenderer::GetInstance()->Update(cmdBuffer, frame);
			FontRenderer::GetInstance()->Draw(cmdBuffer, frame);
			batch.Clear();
		}
		else
		{
			SpriteBatch& batch = Renderer2D::GetInstance()->GetBatchList();

			for (size_t i = 0; i < entities.size(); ++i)
				batch.AddToBatch(&_Sprite[i], &transform[i]);

			batch.PrepareBatch();
			Renderer2D::GetInstance()->Update(cmdBuffer, frame);
			Renderer2D::GetInstance()->Draw(cmdBuffer, frame);
			batch.Clear();
		}*/

	}
}