#include "Rendering/FontRenderer.h"
#include "vulkanTools/VulkanPipeline.h"
#include "Rendering/GraphicsManager.h"
#include "vulkanTools/Renderer.h"
#include "vulkanTools/VulkanTexture.h"

namespace TDS
{
	void FontRenderer::Init()
	{
		std::vector<Vec3> quad =
		{
			{-0.5f,  0.5f, 0.f},
			{-0.5f, -0.5f, 0.f},
			{ 0.5f,  0.5f, 0.f},
			{ 0.5f, -0.5f, 0.f}
		};
		m_VertexBuffer = std::make_shared<VMABuffer>();
		m_VertexBuffer->CreateVertexBuffer(quad.size() * sizeof(Vec3), true, quad.data());
		m_VertexBuffer->SetDataCnt((std::uint32_t)quad.size());
		std::vector<uint32_t> indices =
		{
			0, 1, 2,
			2, 1, 3
		};
		m_IndexBuffer = std::make_shared<VMABuffer>();
		m_IndexBuffer->CreateIndexBuffer(indices.size() * sizeof(uint32_t), true, indices.data());
		m_IndexBuffer->SetDataCnt((std::uint32_t)indices.size());
		PipelineCreateEntry entry{};
		entry.m_NumDescriptorSets = 1;

		entry.m_ShaderInputs.m_Shaders.insert(std::make_pair(SHADER_FLAG::VERTEX, "../../assets/shaders/FontVertex.spv"));
		entry.m_ShaderInputs.m_Shaders.insert(std::make_pair(SHADER_FLAG::FRAGMENT, "../../assets/shaders/FontFragment.spv"));
		VertexLayout layout =
			VertexLayout(
				{
				  VertexBufferElement(VAR_TYPE::VEC3, "vPosition")
				});
		entry.m_ShaderInputs.m_InputVertex.push_back(VertexBufferInfo(false, layout, sizeof(Vec3)));
		BufferInfo info{};
		info.m_Data = nullptr;
		info.m_Size = sizeof(Instance) * MAX_CHARACTERS;
		info.m_Static = false;
		entry.m_ShaderInputs.m_InputBuffers.insert(std::make_pair(1, info));
		m_Pipeline = std::make_shared<VulkanPipeline>();
		m_Pipeline->Create(entry);


	}
	void FontRenderer::Update(const std::vector<EntityID>& entity, FontComponent* component)
	{
		FontUBO ubo{};
		auto cmdBuffer = GraphicsManager::getInstance().getCommandBuffer();
		ubo.m_view = GraphicsManager::getInstance().GetCamera().GetViewMatrix();
		ubo.m_projection = Mat4::Perspective(GraphicsManager::getInstance().GetCamera().m_Fov * Mathf::Deg2Rad,
			GraphicsManager::getInstance().GetSwapchainRenderer().getAspectRatio(), 0.1f, 10.f);
		ubo.m_projection.m[1][1] *= -1;

		m_Pipeline->SetCommandBuffer(cmdBuffer);
		std::uint32_t frame = GraphicsManager::getInstance().GetSwapchainRenderer().getFrameIndex();
		m_Pipeline->UpdateUBO(&ubo, sizeof(FontUBO), 2, frame);
		for (size_t i = 0; i < entity.size(); ++i)
		{

			double CurX = 0;
			double CurY = 0;
			if (component->m_FontInfo.m_FontAtlasTexture != nullptr)
				m_Pipeline->UpdateDescriptor(component->m_FontInfo.m_FontAtlasTexture->m_VulkanTexture->getInfo(), VkDescriptorType::VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 3);
			std::int32_t instanceCnt = 0;
			if (component->m_FontInfo.m_AtlasLayout.m_Glyphs.empty())
				return;
			for (auto& character : component[i].m_UIText)
			{
				if (character == '\n')
				{
					CurX = 0;
					CurY -= component[i].m_FontInfo.m_AtlasLayout.m_Metrics.m_LineHeight;
					continue;
				}

				Glyph& glyph = component[i].m_FontInfo.m_AtlasLayout.m_Glyphs[character];
				double charWidth = glyph.m_PlaneBounds.m_Right - glyph.m_PlaneBounds.m_Left;
				double charHeight = glyph.m_PlaneBounds.m_Top - glyph.m_PlaneBounds.m_Bottom;


				double UV_left = glyph.m_AtlasBounds.m_Left / component[i].m_FontInfo.m_AtlasLayout.m_Atlas.m_Width;
				double UV_right = glyph.m_AtlasBounds.m_Right / component[i].m_FontInfo.m_AtlasLayout.m_Atlas.m_Width;
				double UV_bottom = 1.0 - (glyph.m_AtlasBounds.m_Top / component[i].m_FontInfo.m_AtlasLayout.m_Atlas.m_Height);
				double UV_top = 1.0 - (glyph.m_AtlasBounds.m_Bottom / component[i].m_FontInfo.m_AtlasLayout.m_Atlas.m_Height);

				Mat4 temp{ 1.0f, 0.f, 0.f, 0.f,
							0.f, 1.f, 0.f, 0.f,
							0.f, 0.f, 1.f, 0.f,
							0.f, 0.f, 0.f, 1.f };

				temp = temp.Translate(Vec3(CurX, CurY, 0.f));
				temp = temp.Scale(Vec3(charWidth, charHeight, 1.f));
				m_CharacterInstance[instanceCnt].m_model = temp;
				m_CharacterInstance[instanceCnt].m_StartUV = Vec2(float(UV_left), float(UV_bottom));
				m_CharacterInstance[instanceCnt].m_EndUV = Vec2(float(UV_right), float(UV_top));



				CurX += glyph.m_Advance;

				instanceCnt++;
			}
			m_Pipeline->UpdateUBO(m_CharacterInstance.data(), m_CharacterInstance.size() * sizeof(Instance), 1, frame);


			FontColors fontClr{};
			fontClr.bgColor = { 1.f, 0.f, 0.f, 1.f };
			fontClr.fgColor = { 1.f, 1.f, 1.f, 1.f };
			fontClr.pxRange = 2.f;
			m_Pipeline->UpdateUBO(&fontClr, sizeof(FontColors), 4, frame);


			m_Pipeline->BindPipeline();
			m_Pipeline->BindVertexBuffer(*m_VertexBuffer);
			m_Pipeline->BindIndexBuffer(*m_IndexBuffer);
			m_Pipeline->DrawInstancedIndexed(*m_VertexBuffer, *m_IndexBuffer, instanceCnt, frame);

		}

	}

	void FontRenderer::ShutDown()
	{
		m_IndexBuffer->DestroyBuffer();
		m_VertexBuffer->DestroyBuffer();
		m_Pipeline->ShutDown();
		m_pFrameBuffer = nullptr;
	}

	void FontRenderer::OnInit()
	{
	}

	void FontRenderer::OnUpdate(const float dt, const std::vector<EntityID>& entities, FontComponent* component)
	{
		//GraphicsManager::getInstance().GetFontRenderer().Update(entities, component);
	}

	void FontRenderer::AddFontTexture(VkDescriptorImageInfo& imageInfo)
	{
		/*GraphicsManager::getInstance().GetFontRenderer().m_Pipeline->UpdateDescriptor(imageInfo, VkDescriptorType::VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 3);*/
	}

}