#include "imguiHelper/ImguiCompilerDescriptor.h"
#include "Tools/CompilerFormats.h"
namespace TDS
{
	CompilerDescriptors::CompilerDescriptors()
	{
		flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiDockNodeFlags_AutoHideTabBar;
		panelTitle = "Compiler Descriptors";
		windowPadding = ImVec2(0.f, 0.f);


		m_CompilerDescriptors[DESC_GEOMETRY] = new GeomDescDisplay();
		m_CompilerDescriptors[DESC_TEXTURE] = new TextureDescDisplay();

	}
	void CompilerDescriptors::init()
	{
	}
	void CompilerDescriptors::update()
	{
		static DESCRIPTOR_TYPE m_CurrDescType = DESC_GEOMETRY;

		if (ImGui::BeginCombo("Descriptor Type", m_CurrDescType == DESC_GEOMETRY ? "Geometry" : "Texture"))
		{
			if (ImGui::Selectable("Geometry", m_CurrDescType == DESC_GEOMETRY))
				m_CurrDescType = DESC_GEOMETRY;
			if (ImGui::Selectable("Texture", m_CurrDescType == DESC_TEXTURE))
				m_CurrDescType = DESC_TEXTURE;

			ImGui::EndCombo();
		}
		//DisplaySettings(m_CurrDescType);
	}
	void CompilerDescriptors::DisplaySettings(DESCRIPTOR_TYPE descType)
	{
		if (descType == DESC_GEOMETRY)
		{
			if (ImGui::TreeNode("Geometry Descriptor"))
			{
				auto geomDesc = static_cast<GeomDescDisplay*>(m_CompilerDescriptors[descType]);
				ImGui::SliderFloat3("Scale", geomDesc->m_GeomDecriptor.m_Descriptor.m_L2W.m_Scale, 0.0f, 10.0f);
				ImGui::SliderFloat3("Rotate", geomDesc->m_GeomDecriptor.m_Descriptor.m_L2W.m_Rotate, -180.0f, 180.0f);
				ImGui::SliderFloat3("Translate", geomDesc->m_GeomDecriptor.m_Descriptor.m_L2W.m_Translate, -100.0f, 100.0f);
				ImGui::Checkbox("Create LOD", &geomDesc->m_GeomDecriptor.m_LodOptions.m_CreateLOD);
				ImGui::InputInt("Max LODs", &geomDesc->m_GeomDecriptor.m_LodOptions.m_Max_num_lods);
				ImGui::SliderFloat("Reduction Factor", &geomDesc->m_GeomDecriptor.m_LodOptions.ReductionFactor, 0.0f, 1.0f);
				ImGui::TreePop();
			}
			
		}
		else if (descType == DESC_TEXTURE)
		{
			if (ImGui::TreeNode("Texture Descriptor"))
			{
				auto texDesc = static_cast<TextureDescDisplay*>(m_CompilerDescriptors[descType]);
			
				static int formatIndex = 0;

				if (ImGui::Combo("Format", &formatIndex, TDS::strTexFormats, IM_ARRAYSIZE(TDS::strTexFormats)))
					texDesc->m_TextureDescriptor.m_Descriptor.m_Format = TDS::strTexFormats[formatIndex];
				

				ImGui::Text("Selected Format: %s", TDS::strTexFormats[formatIndex]);
				
				ImGui::TreePop();
			}
		}

	}
}