#include "imguiHelper/ImguiAssetBrowser.h"
#include "Tools/FontLoader.h"
#include "Tools/FileExtensions.h"
#include "Tools/TextureCompressor.h"
#include "Tools/DDSConverter.h"
#include "Tools/GeomCompiler.h"
#include "imguiHelper/ImguiHierarchy.h"
#include "AssetManagement/AssetManager.h"
#include "vulkanTools/vulkanInstance.h"
#include "vulkanTools/VulkanTexture.h"
#include <string>


#define ASSET_PATH "../../assets"
namespace TDS
{
	bool lookUp = false;

	//for icon loading
	Texture fileIcon{}, folderIcon{};
	VkDescriptorSet file_DescSet{}, folder_DescSet{};
	//int file_image_count = 0, folder_image_count = 0;

	aiVector3D ExtractEulerAngles(const aiMatrix4x4& mat) 
	{
		aiVector3D euler{};


		float sy = sqrt(mat.a1 * mat.a1 + mat.b1 * mat.b1);

		bool singular = sy < 1e-6;

		if (!singular) 
		{
			euler.x = atan2(mat.c2, mat.c3); 
			euler.y = atan2(-mat.c1, sy);    
			euler.z = atan2(mat.b1, mat.a1); 
		}
		else 
		{

			euler.x = atan2(-mat.b3, mat.b2); 
			euler.y = atan2(-mat.c1, sy);     
			euler.z = 0;                     
		}

		return euler;
	}
	void ExtractTranslation(const aiMatrix4x4& mat, aiVector3D& translation) 
	{
		translation.x = mat.a4;
		translation.y = mat.b4;
		translation.z = mat.c4;
	}

	void ExtractScale(const aiMatrix4x4& mat, aiVector3D& scale)
	{
		scale.x = sqrt(mat.a1 * mat.a1 + mat.b1 * mat.b1 + mat.c1 * mat.c1);
		scale.y = sqrt(mat.a2 * mat.a2 + mat.b2 * mat.b2 + mat.c2 * mat.c2);
		scale.z = sqrt(mat.a3 * mat.a3 + mat.b3 * mat.b3 + mat.c3 * mat.c3);
	}
	void CreateNewEntityWithSubMesh(EntityID ParentEntity, aiMatrix4x4& aiTransform, TypeReference<AssetModel>& model, std::string_view MeshName)
	{
		std::shared_ptr<Hierarchy> panel = static_pointer_cast<Hierarchy>(LevelEditorManager::GetInstance()->panels[HIERARCHY]);
		Entity newEntity;
		EntityID newEntityID = newEntity.getID();

		//newEntity.add<NameTag>();
		//newEntity.add<Transform>();
		//newEntity.add<GraphicsComponent>();

		addComponentByName("Name Tag", newEntityID);
		addComponentByName("Graphics Component", newEntityID);
		addComponentByName("Transform", newEntityID);
		
		IComponent* nameTag = getComponentByName("Name Tag", newEntityID);
		IComponent* GraphicComponent = getComponentByName("Graphics Component", newEntityID);
		IComponent* TransformComp = getComponentByName("Transform", newEntityID);

		GraphicsComponent* graphComp = reinterpret_cast<GraphicsComponent*>(GraphicComponent);
		graphComp->m_ModelName = model.m_AssetName;
		graphComp->m_MeshName = MeshName;
		graphComp->m_AssetReference = model;
		NameTag* NameTagComp = reinterpret_cast<NameTag*>(nameTag);
		Transform* transformComp = reinterpret_cast<Transform*>(TransformComp);
		NameTagComp->SetHierarchyParent(0);
		NameTagComp->SetHierarchyIndex(panel->hierarchyList.size());
		NameTagComp->SetName(MeshName.data());
		aiVector3D scale{};
		
		aiVector3D Translate{};

		ExtractScale(aiTransform, scale);
		aiVector3D EulerRotate = ExtractEulerAngles(aiTransform);
		ExtractTranslation(aiTransform, Translate);

		transformComp->SetPosition(Vec3(Translate.x, Translate.y, Translate.z));
		transformComp->SetRotation(Vec3(EulerRotate.x, EulerRotate.y, EulerRotate.z));
		transformComp->SetScale(Vec3(scale.x, scale.y, scale.z));

		panel->hierarchyList.emplace_back(newEntityID);

		panel->makingChildHierarchy(newEntityID, ParentEntity);
	}
	void DivideSubmesh(EntityID entity, TypeReference<AssetModel>& model)
	{
		for (auto& childMeshes : model.m_ResourcePtr->m_Meshes)
		{
			aiMatrix4x4& originalModelTransform = GeomCompiler::GetInstance()->m_CurrTransforms[childMeshes.first];

			CreateNewEntityWithSubMesh(entity, originalModelTransform, model, childMeshes.first);
		}
		
	}

	

	AssetBrowser::AssetBrowser()
	{
		//selected = 0;
		//selectedFolder = -1;
		//renameCheck = false;

		flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse;
		panelTitle = "Asset Browser";
		windowPadding = ImVec2(0.f, 0.f);
		m_curr_path = std::filesystem::path(ASSET_PATH);

		//insertEntities();
	}

	void AssetBrowser::getFileNameFromPath(const char* full_path, std::string* path, std::string* file, std::string* fileWithExtension, std::string* extension) const
	{
		if (full_path != nullptr)
		{
			std::string nwFullPath = full_path;
			std::string& full_path_ = nwFullPath;
			//bool toLower;
			for (std::string::iterator charIterator = full_path_.begin(); charIterator != full_path_.end(); ++charIterator)
			{
				if (*charIterator == '\\')
					*charIterator = '/';
				/*else
					if (toLower) {
						*charIterator = tolower(*charIterator);
					}*/
			}
			size_t posSlash = nwFullPath.find_last_of("\\/");
			size_t posDot = nwFullPath.find_last_of(".");

			if (path != nullptr)
			{
				if (posSlash < nwFullPath.length())
					*path = nwFullPath.substr(0, posSlash + 1);
				else
					path->clear();
			}
			if (fileWithExtension != nullptr) {
				if (posSlash < nwFullPath.length()) {
					*fileWithExtension = nwFullPath.substr(posSlash + 1);
				}
				else
					*fileWithExtension = nwFullPath;
			}

			if (file != nullptr)
			{
				nwFullPath = nwFullPath.substr(0, posDot);
				posSlash = nwFullPath.find_last_of("\\/");
				*file = nwFullPath.substr(posSlash + 1);

			}

			if (extension != nullptr)
			{
				if (posDot < nwFullPath.length())
					*extension = nwFullPath.substr(posDot);
				else
					extension->clear();
			}
		}
	}

	static const std::filesystem::path s_AssetDirectory = "../../assets";
	static const std::filesystem::path s_ModelDirectory = "../../assets/models";
	static const std::filesystem::path s_TextureDirectory = "../../assets/textures";
	static const std::filesystem::path s_FontDirectory = "../../assets/Fonts";
	void AssetBrowser::update()
	{
		if (m_curr_path != std::filesystem::path(s_AssetDirectory))
		{
			if (ImGui::Button("<-")) //will only show if u went into a folder in the current directory above
			{
				m_curr_path = m_curr_path.parent_path();
			}
		}
		if (m_curr_path == std::filesystem::path(s_ModelDirectory))
		{
			ImGui::SameLine();
			ImGui::Checkbox("Show .bin files", &show_bin);
			ImGui::SameLine();
			ImGui::Checkbox("Show .fbx files", &show_fbx);
		}
		if (m_curr_path == std::filesystem::path(s_TextureDirectory))
		{
			ImGui::SameLine();
			ImGui::Checkbox("Show .dds files", &show_dds);
			ImGui::SameLine();
			ImGui::Checkbox("Show .png files", &show_png);
		}
		float cellSize = thumbnail_size + padding;

		float panelWidth = ImGui::GetContentRegionAvail().x;
		int columnCount = (int)(panelWidth / cellSize);
		ImGui::Columns(std::max(columnCount, 1), 0, false);

		//load texture info ONCE
		
		if (loadonce == true)
		{
			fileIcon.LoadTexture("../../assets/icons/icon.dds"); //can only take dds files for now
			file_DescSet = ImGui_ImplVulkan_AddTexture(fileIcon.m_VulkanTexture->getInfo().sampler, fileIcon.m_VulkanTexture->getInfo().imageView, fileIcon.m_VulkanTexture->getInfo().imageLayout);

			folderIcon.LoadTexture("../../assets/icons/folder.dds"); //can only take dds files for now
			folder_DescSet = ImGui_ImplVulkan_AddTexture(folderIcon.m_VulkanTexture->getInfo().sampler, folderIcon.m_VulkanTexture->getInfo().imageView, folderIcon.m_VulkanTexture->getInfo().imageLayout);

			loadonce = false;
		}

		

		for (auto& directory_entry : std::filesystem::directory_iterator(m_curr_path))
		{
			path1 = directory_entry.path().string();
			auto relative_path = std::filesystem::relative(directory_entry.path(), s_AssetDirectory);

			//ImGui::Button(path1.c_str(), { thumbnail_size, thumbnail_size });
			//shorten the path name

			std::string filename;
			getFileNameFromPath(path1.c_str(), nullptr, nullptr, &filename, nullptr);
			if (m_curr_path == std::filesystem::path(s_ModelDirectory))
			{
				if (directory_entry.is_directory()) //draw folder icon
				{
					ImGui::ImageButton(reinterpret_cast<void*>(folder_DescSet), ImVec2{ thumbnail_size, thumbnail_size }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
					//folder_image_count++;
				}
				if (!show_bin && !show_fbx) { continue; }
				else if (show_bin && !show_fbx)
				{
					if (!strstr(filename.c_str(), ".bin")) //if its not bin, continue
					{
						continue;
					}
				}
				else if (show_fbx && !show_bin)
				{
					if (!strstr(filename.c_str(), ".fbx")) //if its not bin, continue
					{
						continue;
					}
				}

			}
			if (m_curr_path == std::filesystem::path(s_TextureDirectory))
			{
				if (directory_entry.is_directory()) //draw folder icon
				{
					ImGui::ImageButton(reinterpret_cast<void*>(folder_DescSet), ImVec2{ thumbnail_size, thumbnail_size }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
					//folder_image_count++;
				}
				if (!show_dds && !show_png) { continue; }
				else if (show_dds && !show_png)
				{
					if (!strstr(filename.c_str(), ".dds")) //if its not dds, continue
					{
						continue;
					}
				}
				else if (show_png && !show_dds)
				{
					if (!strstr(filename.c_str(), ".png")) //if its not png, continue
					{
						continue;
					}
				}

			}
			ImGui::PushID(filename.c_str()); //store the current id in each button that is created in each iteration of files
			
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
			

			if (directory_entry.is_directory()) //draw folder icon
			{
				ImGui::ImageButton(reinterpret_cast<void*>(folder_DescSet), ImVec2{ thumbnail_size, thumbnail_size }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
				//folder_image_count++;
			}
			else //draw file icon
			{
				
				//then render button
				ImGui::ImageButton(reinterpret_cast<void*>(file_DescSet), ImVec2{ thumbnail_size, thumbnail_size }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
				//do drag drop ONLY on files, not folder
				if (ImGui::BeginDragDropSource())
				{
					std::filesystem::path relativePath(path1);
					const wchar_t* itemPath = relativePath.c_str();
					ImGui::Text(filename.c_str()); //need to get info from image
					ImGui::SetDragDropPayload("CONTENT_BROWSER_ITEM", itemPath, (wcslen(itemPath) + 1) * sizeof(wchar_t));
					ImGui::EndDragDropSource();
				}
				//file_image_count++;

				//ImGui::Button(filename.c_str(), { thumbnail_size, thumbnail_size });

			}
			ImGui::PopStyleColor();

			if (ImGui::IsItemClicked(0))
			{
				
				//if it has a "." in it, it is a file, do not add to path
				//only directories/folders can be added to path

				//if it is a folder, open it and update the asset broswer curr dir
				if (!strstr(filename.c_str(), ".")) 
				{
					m_curr_path += "/" + filename;
				

					//attempt at drag drop
					selectedpath = path1;
					

				}
				//use the rest of the checks below to handle what happens when u press different kinds of file extensions

				//if .jpg/.PNG, load 2d texture...
				if (strstr(filename.c_str(), ".jpg") || strstr(filename.c_str(), ".png") || strstr(filename.c_str(), ".dds"))
				{
					lookUp = false;



					std::shared_ptr<Hierarchy> panel = static_pointer_cast<Hierarchy>(LevelEditorManager::GetInstance()->panels[HIERARCHY]);

					EntityID currEntity = panel->getSelectedEntity();
					IComponent* Graph = getComponentByName("Graphics Component", panel->getSelectedEntity());
					if (Graph == nullptr)
						Graph = addComponentByName("Graphics Component", panel->getSelectedEntity());
					

					std::string OutPath = ASSET_PATH;
					OutPath += "/textures/";
					OutPath += filename.c_str();
					std::string inPath = OutPath;
					if (strstr(filename.c_str(), ".jpg"))
						OutPath = RemoveFileExtension(OutPath, ".jpg");
					else if (strstr(filename.c_str(), ".png"))
						OutPath = RemoveFileExtension(OutPath, ".png");


					if (strstr(filename.c_str(), ".dds"))
						lookUp = true;
					else
						OutPath += ".dds";


					if (lookUp == false)
						TextureCompressor::GetInstance().Run(inPath, OutPath);

					GraphicsComponent* graphComp = reinterpret_cast<GraphicsComponent*>(Graph);
					if (graphComp)
						AssetManager::GetInstance()->GetTextureFactory().Load(OutPath, graphComp->GetTexture());


				}
				if (strstr(filename.c_str(), ".obj") || strstr(filename.c_str(), ".fbx") || strstr(filename.c_str(), ".gltf") || strstr(filename.c_str(), ".bin"))
				{
					lookUp = false;
					std::string& OutPath = GeomCompiler::GetInstance()->OutPath;
					OutPath = "../../assets/models/";
					OutPath += filename.c_str();
					if (strstr(filename.c_str(), ".fbx"))
						OutPath = RemoveFileExtension(OutPath, ".fbx");
					else if (strstr(filename.c_str(), ".gltf"))
						OutPath = RemoveFileExtension(OutPath, ".gltf");
					else if (strstr(filename.c_str(), ".obj"))
						OutPath = RemoveFileExtension(OutPath, ".obj");
					else if (strstr(filename.c_str(), ".bin"))
					{
						lookUp = true;
						/*OutPath = std::filesystem::path(OutPath).filename().string();*/
					}

					std::shared_ptr<Hierarchy> panel = static_pointer_cast<Hierarchy>(LevelEditorManager::GetInstance()->panels[HIERARCHY]);

					EntityID currEntity = panel->getSelectedEntity();
					if (currEntity < 1)
						return;
					IComponent* Graph = getComponentByName("Graphics Component", panel->getSelectedEntity());
					if (Graph == nullptr)
						Graph = addComponentByName("Graphics Component", panel->getSelectedEntity());
					GraphicsComponent* graphComp = reinterpret_cast<GraphicsComponent*>(Graph);

					if (lookUp == false)
					{
						GeomDescriptor m_GeomDescriptor{};
						m_GeomDescriptor.m_Descriptor.m_FilePath = std::filesystem::path(filename).filename().string();
						GeomCompiler::GetInstance()->InitDesc(m_GeomDescriptor);
						std::string OutputFile = GeomCompiler::GetInstance()->LoadModel();

						AssetManager::GetInstance()->GetModelFactory().LoadModel(OutputFile, graphComp->GetAsset());

					}
					else
					{
						AssetManager::GetInstance()->GetModelFactory().LoadModel(OutPath, graphComp->GetAsset());

					}
					if (graphComp->m_AssetReference.m_ResourcePtr->m_Meshes.size() > 1)
						DivideSubmesh(currEntity, graphComp->m_AssetReference);
					
					


				}
				//if .json, load scene...
				if (strstr(filename.c_str(), ".ttf"))
				{
					std::string selectedTextureDir = m_curr_path.string();
					selectedTextureDir += "/";
					selectedTextureDir += filename;
					std::string inputPath = selectedTextureDir;
					std::string outPath = m_curr_path.string();
					selectedTextureDir = RemoveFileExtension(selectedTextureDir, ".ttf");

					std::string FileName = std::filesystem::path(selectedTextureDir).filename().string();

					outPath += ("/OutFont_" + FileName);
					if (!std::filesystem::exists(outPath))
					{
						if (!std::filesystem::create_directory(outPath))
							TDS_ERROR("Failed to create directory");
					}
					std::string folderName = outPath;
					outPath += "/" + FileName;
					LoaderDescriptor FontDescriptor{};
					FontDescriptor.OutPath = outPath;
					FontDescriptor.m_InputPath = inputPath;

					if (FontLoader::RunFontLoader(FontDescriptor))
					{
						std::shared_ptr<Hierarchy> panel = static_pointer_cast<Hierarchy>(LevelEditorManager::GetInstance()->panels[HIERARCHY]);

						IComponent* font = getComponentByName("UI Sprite", panel->getSelectedEntity());
						if (font != nullptr)
						{
							UISprite* spriteComp = reinterpret_cast<UISprite*>(font);
							AssetManager::GetInstance()->GetFontFactory().Load(folderName, spriteComp->GetFontReference());
						}
					}
					

				}


				if (strstr(filename.c_str(), ".json"))
				{

				}

				if (strstr(filename.c_str(), ".json"))
				{

				}

				//if .wav, play audio...
				if (strstr(filename.c_str(), ".wav"))
				{

				}


			}
			ImGui::TextWrapped(filename.c_str()); //currently using this to display full file name
			
			/*if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceExtern))
			{
				ImGui::SetDragDropPayload("path", path1.c_str(), 1);
				ImGui::Text(path1.c_str());
				if (!ImGui::IsMouseDown(0))
				{
					ImGui::EndDragDropSource();

				}
			}

			if (ImGui::BeginDragDropTarget())
			{
				ImGui::EndDragDropTarget();
			}*/
			ImGui::NextColumn();
			ImGui::PopID(); //store new id for next button
		}


		ImGui::Columns(1);
		//ImGui::SliderFloat("Thumbnail Size", &thumbnail_size, 16, 512);
		//ImGui::SliderFloat("Padding", &padding, 0, 32);
	}
	void AssetBrowser::destroyIcons()
	{
		fileIcon.m_VulkanTexture->Destroy(); //temp, to prevent mem leak
		folderIcon.m_VulkanTexture->Destroy(); //temp, to prevent mem leak
		
		/* when breakpoint, these 2 lines below free nothing
		
		fileIcon.Destroy();
		folderIcon.Destroy();*/

		//seems like the while loops dont cause multiple textures to be freed 
		//while (file_image_count)
		//{
		//	fileIcon.m_VulkanTexture->Destroy(); //temp, to prevent mem leak
		//	//fileIcon.Destroy();
		//	file_image_count--;

		//}
		//while (folder_image_count)
		//{
		//	folderIcon.m_VulkanTexture->Destroy(); //temp, to prevent mem leak
		//	//folderIcon.Destroy();
		//	folder_image_count--;

		//}
	}
}