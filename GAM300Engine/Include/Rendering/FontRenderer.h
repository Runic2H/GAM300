#pragma once
#include "MathCommon.h"
#include "GraphicsResource/FontInfo.h"
#include "vulkanTools/VMATypes/VMABuffer.h"
#include "components/components.h"
#include <ecs/ecs.h>
#include <dotnet/ImportExport.h>
namespace TDS
{

	class VulkanPipeline;
	class FrameBuffer;

	struct Instance
	{
		Vec2 m_StartUV;
		Vec2 m_EndUV;
		Mat4 m_model;
	};



	struct CharacterState
	{
		char character;
		Vec2 position;
		Vec2 scale;
		float rotation;
	};

	struct FontUBO
	{
		Mat4 m_projection;
		Mat4 m_view;
	};

	struct FontColors
	{
		Vec4 bgColor;
		Vec4 fgColor;
		float pxRange;
	};


	constexpr std::uint32_t MAX_CHARACTERS = 1000;
	class FontRenderer
	{
	private:
		std::shared_ptr<VulkanPipeline> m_Pipeline = nullptr;
		std::shared_ptr<FrameBuffer>	m_pFrameBuffer = nullptr;
		std::array<Instance, MAX_CHARACTERS> m_CharacterInstance;
		std::shared_ptr<VMABuffer> m_VertexBuffer = nullptr;
		std::shared_ptr<VMABuffer> m_IndexBuffer = nullptr;
		FontUBO m_UpdateForAllEntity;
	public:
		DLL_API void Init();
		DLL_API void Update(const std::vector<EntityID>& entity, FontComponent* component);
		DLL_API void ShutDown();
		DLL_API static void OnInit();
		DLL_API static void OnUpdate(const float dt, const std::vector<EntityID>& entities, FontComponent* component);
		DLL_API static void AddFontTexture(VkDescriptorImageInfo& imageInfo);


	};
}