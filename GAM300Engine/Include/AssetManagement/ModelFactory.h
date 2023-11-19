/*!*****************************************************************************
 * \file          ModelFactory.h
 * \author        Eugene Ho Shu Sheng
 * \par DP email: shushengeugene.ho@digipen.edu
 * \par Course:   CSD3400
 * \par Section:  A
 * \date          01/10/2023
 * \brief         This file contains the declaration of the ModelFactory class.
 *******************************************************************************/
#pragma once
#include "FactoryBase.h"
#include <string_view>
#include <vector>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <ecs/ecs.h>
#include "components/components.h"
#define MODEL_PATH "../assets/models/"
#define MAX_PRELOAD_MODELS 1000

namespace TDS
{
	/*!*************************************************************************
	 * template class ModelFactory
	 ***************************************************************************/
	template<>
	class AssetFactory<AssetModel>
	{
	public:

		std::array<const char*, 6> m_PrimitiveModels = { "capsule_bin.bin", "cube_bin.bin", "Quad1_bin.bin",
			"Quad2_bin.bin","sphere_bin.bin", "torus_bin.bin" };

		std::array<AssetModel, 8196> m_Models;
		std::unordered_map<std::string, std::uint32_t> m_ModelIndices; 
		std::unordered_map<std::string, std::uint32_t> m_InstanceCnt; 
		std::uint32_t m_CurrentIndex = 0;


		std::array<AssetModel, 8196>& GetModelArray()
		{
			return m_Models;
		}
		AssetModel* GetModel(std::string_view modelName, TypeReference<AssetModel>& model)
		{
			auto itr = m_ModelIndices.find(modelName.data());
			if (itr != m_ModelIndices.end())
			{
				--m_InstanceCnt[model.m_AssetName];
				model.m_AssetName = modelName;
				model.m_ResourcePtr = &m_Models[itr->second];
				++m_InstanceCnt[modelName.data()];
				return model.m_ResourcePtr;
			}
			return nullptr;
			TDS_WARN("Model doesnt exist!");
		}

		/*!*************************************************************************
		 * Deserialize the model from the file.
		 ***************************************************************************/
		static void DeserializeGeom(Geom& geomOut, std::string_view PathData)
		{
			std::ifstream inFile(PathData.data(), std::ios::binary);
			if (!inFile)
			{
				std::cerr << "ERROR: Could not open file for reading!\n";
				return;
			}

			auto deserializeVec3 = [](std::ifstream& in, Vec3& vec)
			{
				in.read(reinterpret_cast<char*>(&vec.x), sizeof(vec.x));
				in.read(reinterpret_cast<char*>(&vec.y), sizeof(vec.y));
				in.read(reinterpret_cast<char*>(&vec.z), sizeof(vec.z));
			};

			auto deserializeVec2 = [](std::ifstream& in, Vec2& vec)
			{
				in.read(reinterpret_cast<char*>(&vec.x), sizeof(vec.x));
				in.read(reinterpret_cast<char*>(&vec.y), sizeof(vec.y));
			};

			auto deserializeMesh = [](std::ifstream& in, Geom::Mesh& mesh)
			{
				in.read(reinterpret_cast<char*>(&mesh.m_Name), sizeof(mesh.m_Name));
			};

			auto deserializeSubMesh = [](std::ifstream& in, Geom::SubMesh& subMesh)
			{
				in.read(reinterpret_cast<char*>(&subMesh.m_nFaces), sizeof(subMesh.m_nFaces));
				in.read(reinterpret_cast<char*>(&subMesh.m_iIndices), sizeof(subMesh.m_iIndices));
				in.read(reinterpret_cast<char*>(&subMesh.m_iVertices), sizeof(subMesh.m_iVertices));
				in.read(reinterpret_cast<char*>(&subMesh.m_nVertices), sizeof(subMesh.m_nVertices));
				in.read(reinterpret_cast<char*>(&subMesh.m_iMaterial), sizeof(subMesh.m_iMaterial));
			};

			auto deserializeExtraVertices = [&](std::ifstream& in, Geom::ExtraVertices& extraVertices)
			{
				deserializeVec2(in, extraVertices.m_UV);
				deserializeVec3(in, extraVertices.m_Normal);
				deserializeVec3(in, extraVertices.m_Tanget);
				deserializeVec3(in, extraVertices.m_Bitangent);
				in.read(reinterpret_cast<char*>(&extraVertices.m_Colour), sizeof(extraVertices.m_Colour));
			};

			uint32_t meshSize;
			inFile.read(reinterpret_cast<char*>(&meshSize), sizeof(meshSize));
			geomOut.m_Mesh.resize(meshSize);
			for (auto& mesh : geomOut.m_Mesh)
			{
				deserializeMesh(inFile, mesh);
			}

			uint32_t subMeshSize;
			inFile.read(reinterpret_cast<char*>(&subMeshSize), sizeof(subMeshSize));
			geomOut.m_SubMesh.resize(subMeshSize);
			for (auto& subMesh : geomOut.m_SubMesh)
			{
				deserializeSubMesh(inFile, subMesh);
			}

			uint32_t posSize;
			inFile.read(reinterpret_cast<char*>(&posSize), sizeof(posSize));
			geomOut.m_Pos.resize(posSize);
			for (auto& pos : geomOut.m_Pos)
			{
				deserializeVec3(inFile, pos);
			}

			uint32_t extraSize;
			inFile.read(reinterpret_cast<char*>(&extraSize), sizeof(extraSize));
			geomOut.m_Extra.resize(extraSize);
			for (auto& extra : geomOut.m_Extra)
			{
				deserializeExtraVertices(inFile, extra);
			}

			uint32_t indicesSize;
			inFile.read(reinterpret_cast<char*>(&indicesSize), sizeof(indicesSize));
			geomOut.m_Indices.resize(indicesSize);
			inFile.read(reinterpret_cast<char*>(geomOut.m_Indices.data()), indicesSize * sizeof(uint32_t));

			inFile.close();
		}

		void PreloadDefaultPrimitives()
		{
			for (auto& primitive : m_PrimitiveModels)
			{
				Geom newGeom{};
				std::string Path = MODEL_PATH;
				Path += primitive;
				std::string primitiveName = std::filesystem::path(Path).filename().string();
				DeserializeGeom(newGeom, Path);
				m_Models[m_CurrentIndex].LoadGeomData(newGeom);
				m_ModelIndices[primitiveName] = m_CurrentIndex++;
				m_InstanceCnt[primitiveName] = 1;
				
			}
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
					Geom newGeom{};
					DeserializeGeom(newGeom, entry.path().string());
					std::string fileName = path.filename().string();
					
					auto& model = m_Models[m_CurrentIndex];
					if (newGeom.m_Mesh.size() == 1)
					{
						iColor color{};
						std::string meshName(newGeom.m_Mesh[0].m_Name.data(), strlen(newGeom.m_Mesh[0].m_Name.data()));
						auto& meshData = model.m_Meshes[meshName];
						meshData.m_VertexData.resize(newGeom.m_Pos.size());
						meshData.m_IndexData.resize(newGeom.m_Indices.size());
						std::copy(newGeom.m_Indices.begin(), newGeom.m_Indices.end(), meshData.m_IndexData.data());
						for (size_t i = 0; i < newGeom.m_Pos.size(); ++i)
						{
							meshData.m_VertexData[i].m_Pos = newGeom.m_Pos[i];
							if (i < newGeom.m_Extra.size())
							{
								meshData.m_VertexData[i].m_UV = newGeom.m_Extra[i].m_UV;
								meshData.m_VertexData[i].m_fNormal = Vec4(newGeom.m_Extra[i].m_Normal.x, newGeom.m_Extra[i].m_Normal.y, newGeom.m_Extra[i].m_Normal.z, 1.0f);
								meshData.m_VertexData[i].m_Color = { 255.f, 0.f, 0.f };
							}
						}
						model.CreateBoundingShapes();
						model.m_CurrMeshData = &model.m_Meshes[meshName];
					}
					else
					{
						for (size_t i = 0; i < newGeom.m_Mesh.size(); ++i)
						{
							std::string meshName(newGeom.m_Mesh[i].m_Name.data(), strlen(newGeom.m_Mesh[i].m_Name.data()));
							auto& submesh = newGeom.m_SubMesh[i];
							auto& meshData = model.m_Meshes[meshName];

							size_t vertexStart = submesh.m_iVertices;
							size_t vertexCount = submesh.m_nVertices;
							meshData.m_VertexData.resize(vertexCount);
							for (size_t j = 0; j < vertexCount; ++j)
							{
								size_t vertexIndex = vertexStart + j;
								if (vertexIndex < newGeom.m_Pos.size())
								{
									meshData.m_VertexData[j].m_Pos = newGeom.m_Pos[vertexIndex];
									meshData.m_VertexData[j].m_UV = newGeom.m_Extra[vertexIndex].m_UV;
									meshData.m_VertexData[j].m_fNormal = newGeom.m_Extra[vertexIndex].m_Normal;
									meshData.m_VertexData[j].m_Color = { 255.f, 0.f, 0.f };
								}
							}
							size_t indexStart = submesh.m_iIndices;
							size_t indexCount = submesh.m_nFaces * 3;
							meshData.m_IndexData.resize(indexCount);
							for (size_t j = 0; j < indexCount; ++j)
							{
								size_t index = indexStart + j;
								if (index < newGeom.m_Indices.size())
								{
									meshData.m_IndexData[j] = newGeom.m_Indices[index];
								}
							}
							meshData.CreateBoundingShapes();
						}
					}
					m_ModelIndices[fileName.data()] = m_CurrentIndex++;
					m_InstanceCnt[fileName.data()] = 1;
					++numPreLoadedModels;


				}
			}
		}

		//Even if the model has child meshes it should still be treated as one mesh
		void LoadModel(std::string_view path, TypeReference<AssetModel>& assetModel)
		{
			std::filesystem::path FilePath(path);
			std::string fileName = FilePath.filename().string();

			auto itr = m_ModelIndices.find(fileName);


			if (itr != m_ModelIndices.end())
			{
				--m_InstanceCnt[assetModel.m_AssetName];
				assetModel.m_AssetName = fileName;
				++m_InstanceCnt[fileName];
				assetModel.m_ResourcePtr = &m_Models[itr->second];

				return;
			}
			assetModel.m_AssetName = fileName;
			std::uint32_t& newIndex = m_CurrentIndex;
			Geom geom{};

			DeserializeGeom(geom, path);
			
			if (geom.m_Mesh.size() == 1)
			{
				auto& model = m_Models[newIndex];
				iColor color{};
	
				std::string meshName(geom.m_Mesh[0].m_Name.data(), strlen(geom.m_Mesh[0].m_Name.data()));
				auto& meshData = model.m_Meshes[meshName];
				meshData.m_VertexData.resize(geom.m_Pos.size());
				meshData.m_IndexData.resize(geom.m_Indices.size());
				std::copy(geom.m_Indices.begin(), geom.m_Indices.end(), meshData.m_IndexData.data());
				for (size_t i = 0; i < geom.m_Pos.size(); ++i)
				{
					meshData.m_VertexData[i].m_Pos = geom.m_Pos[i];
					if (i < geom.m_Extra.size())
					{
						meshData.m_VertexData[i].m_UV = geom.m_Extra[i].m_UV;
						meshData.m_VertexData[i].m_fNormal = Vec4(geom.m_Extra[i].m_Normal.x, geom.m_Extra[i].m_Normal.y, geom.m_Extra[i].m_Normal.z, 1.0f);
						meshData.m_VertexData[i].m_Color = { 255.f, 0.f, 0.f };
					}
				}
				model.CreateBoundingShapes();
				model.m_CurrMeshData = &model.m_Meshes[meshName];
			}
			else
			{
				auto& model = m_Models[newIndex];
				for (size_t i = 0; i < geom.m_Mesh.size(); ++i)
				{
					std::string meshName(geom.m_Mesh[i].m_Name.data(), strlen(geom.m_Mesh[i].m_Name.data()));
					auto& submesh = geom.m_SubMesh[i];
					auto& meshData = model.m_Meshes[meshName];

					size_t vertexStart = submesh.m_iVertices;
					size_t vertexCount = submesh.m_nVertices;
					meshData.m_VertexData.resize(vertexCount);
					for (size_t j = 0; j < vertexCount; ++j)
					{
						size_t vertexIndex = vertexStart + j;
						if (vertexIndex < geom.m_Pos.size())
						{
							meshData.m_VertexData[j].m_Pos = geom.m_Pos[vertexIndex];
							meshData.m_VertexData[j].m_UV = geom.m_Extra[vertexIndex].m_UV;
							meshData.m_VertexData[j].m_fNormal = geom.m_Extra[vertexIndex].m_Normal;
							meshData.m_VertexData[j].m_Color = { 255.f, 0.f, 0.f };
						}
					}
					size_t indexStart = submesh.m_iIndices;
					size_t indexCount = submesh.m_nFaces * 3; 
					meshData.m_IndexData.resize(indexCount);
					for (size_t j = 0; j < indexCount; ++j)
					{
						size_t index = indexStart + j;
						if (index < geom.m_Indices.size())
						{
							meshData.m_IndexData[j] = geom.m_Indices[index];
						}
					}
					meshData.CreateBoundingShapes();
				}
			}
			assetModel.m_ResourcePtr = &m_Models[newIndex];
			m_ModelIndices[fileName] = newIndex++;
			m_InstanceCnt[fileName] = 1;
		}

		void Load(std::string_view path, TypeReference<AssetModel>& model)
		{
			std::filesystem::path FilePath(path);
			std::string fileName = FilePath.filename().string();
		
			auto itr = m_ModelIndices.find(fileName);

			if (itr != m_ModelIndices.end())
			{
				--m_InstanceCnt[model.m_AssetName];
				model.m_AssetName = fileName;
				TDS_INFO("Model {} is already loaded!", model.m_AssetName);
				++m_InstanceCnt[fileName];
				model.m_ResourcePtr = &m_Models[itr->second];
				return;
			}

			//its a new model
			model.m_AssetName = fileName;
			std::uint32_t& newIndex = m_CurrentIndex;
			Geom geom{};
			
			DeserializeGeom(geom, path);
			m_Models[newIndex].LoadGeomData(geom);
			model.m_ResourcePtr = &m_Models[newIndex];
			m_ModelIndices[fileName] = newIndex++;
			m_InstanceCnt[fileName] = 1;
		}

		void DestroyAllModels()
		{
			for (auto& model : m_Models)
			{
				model.Destroy();
			}
			m_ModelIndices.clear();
		}

	};



}