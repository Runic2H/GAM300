#pragma once
#include "GraphicsResource/Revamped/ModelPack.h"
#include "AssetManagement/FactoryBase.h"
#include "GraphicsResource/Revamped/MeshController.h"
#define MODEL_PATH "../assets/models/"
#define MAX_PRELOAD_MODELS 1000
namespace TDS
{
	
	
	template <>
	class AssetFactory<MeshController>
	{
		static constexpr int MAX_MODELS = 8196;

		private:

			std::array<const char*, 6>										m_PrimitiveModels = { "capsule_bin.bin", "cube_bin.bin", "Quad1_bin.bin",
				"Quad2_bin.bin","sphere_bin.bin", "torus_bin.bin" };

			std::array<Modelpack, MAX_MODELS>								m_Models;
			std::array<MeshController, MAX_MODELS>							m_MeshControllers;
			std::unordered_map<std::string, std::uint32_t>					m_ModelIndices;
			std::unordered_map<std::string, std::uint32_t>					m_ReferenceCnt;
			std::uint32_t													m_CurrentIndex = 0;
			
		public:
			std::array<Modelpack, MAX_MODELS>& GetModelPacks()
			{
				return m_Models;
			}

			std::array<MeshController, MAX_MODELS>& GetMeshControllers()
			{
				return m_MeshControllers;
			}

			void LoadModel(std::string_view path)
			{
				std::filesystem::path FilePath(path);
				std::string fileName = FilePath.filename().string();

				auto itr = m_ModelIndices.find(fileName);
				if (itr != m_ModelIndices.end())
				{

					int instance = m_ReferenceCnt[fileName];
					int index = itr->second;
					if (instance == 0)
					{
						auto& CurrModel = m_Models[m_ModelIndices[fileName]];
						auto& CurrController = m_MeshControllers[m_ModelIndices[fileName]];
						
						CurrModel.Cleanup();
						CurrController.Destroy();

						CurrModel.LoadModelPack(path);
						CurrController.LoadMeshData(CurrModel);
					
						CurrController.BuildMeshTree();

					}
					else
					{
						TDS_INFO("This model is being used by {} entities, load failure", instance);
						return;
					}


				}
				else
				{
					auto& CurrModel = m_Models[m_CurrentIndex];
					auto& CurrController = m_MeshControllers[m_CurrentIndex];

					CurrModel.Cleanup();
					CurrController.Destroy();

					CurrModel.LoadModelPack(path);
					CurrController.LoadMeshData(CurrModel);
					CurrController.BuildMeshTree();

					m_ModelIndices[fileName] = m_CurrentIndex;
					m_ReferenceCnt[fileName]++;

					m_CurrentIndex++;
	
				}
			}

			void PreloadDefaultPrimitives()
			{
				for (auto& primitive : m_PrimitiveModels)
				{;
					std::string Path = MODEL_PATH;
					Path += primitive;
					std::string primitiveName = std::filesystem::path(Path).filename().string();
					LoadModel(Path);

				}
			}

			MeshController* GetMeshController(std::string_view modelName, TypeReference<MeshController>& model)
			{
				auto itr = m_ModelIndices.find(modelName.data());
				if (itr != m_ModelIndices.end())
				{
					if (model.m_AssetName.empty() == false)
						--m_ReferenceCnt[model.m_AssetName];

					model.m_AssetName = modelName;
					model.m_ResourcePtr = &m_MeshControllers[itr->second];
					++m_ReferenceCnt[modelName.data()];
					return model.m_ResourcePtr;
				}
				return nullptr;
				TDS_WARN("Model doesnt exist!");
			}
			void Load(std::string_view path, TypeReference<MeshController>& modelRef)
			{
				std::filesystem::path FilePath(path);
				std::string fileName = FilePath.filename().string();
				if (modelRef.m_ResourcePtr)
					UnloadReference(modelRef);
				
				if (GetMeshController(fileName, modelRef) == nullptr)
					LoadModel(path);
				
				modelRef.m_ResourcePtr = GetMeshController(fileName, modelRef);
			}
			void Preload()
			{
				std::filesystem::path dir = MODEL_PATH;

				if (!std::filesystem::exists(dir) || !std::filesystem::is_directory(dir))
				{
					std::cout << "Invalid directory" << std::endl;
					return;
				}
				std::uint32_t numPreLoadedModels = 0;
				for (const auto& entry : std::filesystem::directory_iterator(dir))
				{
					if (numPreLoadedModels >= MAX_PRELOAD_MODELS)
						break;


					const std::filesystem::path& path = entry.path();

					if (path.extension() == ".bin")
					{
						std::string pathInString = entry.path().string();
						LoadModel(pathInString);
						++numPreLoadedModels;
					}
				}
			}
			void UnloadReference(TypeReference<MeshController>& modelRef)
			{
				
				modelRef.m_ResourcePtr = nullptr;

				--m_ReferenceCnt[modelRef.m_AssetName];

				if (m_ReferenceCnt[modelRef.m_AssetName] == 0)
				{
					m_MeshControllers[m_ModelIndices[modelRef.m_AssetName]].Destroy();
					m_Models[m_ModelIndices[modelRef.m_AssetName]].Cleanup();
				}
				modelRef.m_AssetName = "";

			}
			void DestroyAllMesh()
			{
				for (auto& model : m_MeshControllers)
				{
					model.Destroy();
				}
				m_ModelIndices.clear();
			}


	};
}