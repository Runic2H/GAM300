#include "pch.h"
#include "GraphicsResource/Revamped/MeshController.h"
#include "GraphicsResource/Revamped/ModelPack.h"
#include "vulkanTools/VMATypes/VMABuffer.h"
#include "Rendering/GraphicsManager.h"
namespace TDS
{
#define _TEMP
    bool MeshController::LoadMeshData(Modelpack& model)
    {

        m_RefToModelPack = &model;

#ifdef _TEMP
        std::map<std::string, int> duplicates;
#endif

        for (size_t i = 0; i < model.m_ModelHandle.m_Mesh.size(); ++i)
        {
            auto& Mesh = model.m_ModelHandle.m_Mesh[i];
            auto& SubMesh = model.m_ModelHandle.m_SubMesh[i];

            size_t start = SubMesh.m_iVertices;
            size_t end = start + SubMesh.m_nVertices;

            std::vector<TDSModel::Vertex> vertexData;
            vertexData.insert(vertexData.end(), model.m_ModelHandle.m_ModelVertex.begin() + start, model.m_ModelHandle.m_ModelVertex.begin() + end);

            size_t indexStart = SubMesh.m_iIndices;
            size_t indexEnd = indexStart + (SubMesh.m_nFaces * 3);
            std::vector<std::uint32_t> indexData;

            indexData.insert(indexData.end(),
                model.m_ModelHandle.m_Indices.begin() + indexStart,
                model.m_ModelHandle.m_Indices.begin() + indexEnd);


            auto itr = m_MeshIndexMap.find(Mesh.m_Name);

#ifndef _TEMP
            if (itr == m_MeshIndexMap.end())
            {

                m_MeshIndexMap[Mesh.m_Name] = m_MeshData.size();

                auto& MeshData = m_MeshData.emplace_back();

                MeshData.m_VertexBuffer = std::make_shared<VMABuffer>();
                MeshData.m_VertexBuffer->MappedStaging(vertexData.size() * sizeof(TDSModel::Vertex), VkBufferUsageFlagBits::VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, GraphicsManager::getInstance().getVkInstance(), vertexData.data());
                MeshData.m_VertexBuffer->SetDataCnt(vertexData.size());

                MeshData.m_IndexBuffer = std::make_shared<VMABuffer>();
                MeshData.m_IndexBuffer->MappedStaging(indexData.size() * sizeof(std::uint32_t), VkBufferUsageFlagBits::VK_BUFFER_USAGE_INDEX_BUFFER_BIT, GraphicsManager::getInstance().getVkInstance(), indexData.data());
                MeshData.m_IndexBuffer->SetDataCnt(indexData.size());
            }
#endif // !_TEMP
            
            //If have duplicates
            if (itr != m_MeshIndexMap.end())
            {
                Mesh.m_Name += "__";
                Mesh.m_Name += std::to_string(++duplicates[itr->first]);

            }

            m_MeshIndexMap[Mesh.m_Name] = m_MeshData.size();

            auto& MeshData = m_MeshData.emplace_back();

            MeshData.m_VertexBuffer = std::make_shared<VMABuffer>();
            MeshData.m_VertexBuffer->MappedStaging(vertexData.size() * sizeof(TDSModel::Vertex), VkBufferUsageFlagBits::VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, GraphicsManager::getInstance().getVkInstance(), vertexData.data());
            MeshData.m_VertexBuffer->SetDataCnt(vertexData.size());

            MeshData.m_IndexBuffer = std::make_shared<VMABuffer>();
            MeshData.m_IndexBuffer->MappedStaging(indexData.size() * sizeof(std::uint32_t), VkBufferUsageFlagBits::VK_BUFFER_USAGE_INDEX_BUFFER_BIT, GraphicsManager::getInstance().getVkInstance(), indexData.data());
            MeshData.m_IndexBuffer->SetDataCnt(indexData.size());
            
            
           
        }
        m_Loaded = true;
        return m_Loaded;
    }
    void MeshController::Destroy()
    {
        vkQueueWaitIdle(GraphicsManager::getInstance().getVkInstance().getGraphicsQueue());

        for (auto& modeldata : m_MeshData)
        {
            if (modeldata.m_VertexBuffer && modeldata.m_IndexBuffer)
            {
                modeldata.m_VertexBuffer->DestroyBuffer();
                modeldata.m_IndexBuffer->DestroyBuffer();
                modeldata.m_VertexBuffer = nullptr;
                modeldata.m_IndexBuffer = nullptr;
            }

        }
        m_RefToModelPack = nullptr;
        m_RootNodes.clear();
        m_MeshData.clear();
        m_MeshIndexMap.clear();
        m_Loaded = false;
       
    }
    void MeshController::BuildMeshTree()
    {
        auto& modelRef = m_RefToModelPack->m_ModelHandle;

        if (modelRef.m_Mesh.size() == 1 && modelRef.m_SubMesh.size() == 1)
        {
            TDS_INFO("This model {} is a single mesh! I wont build a mesh tree for this", m_RefToModelPack->m_ModelName.c_str());
            return;
        }

        std::uint32_t i = 0;
        for (auto mesh : modelRef.m_Mesh)
        {
            auto& submesh = modelRef.m_SubMesh[i++];

            m_RootNodes[mesh.m_NodeName].m_MeshList[mesh.m_Name] = (MeshNode(true, mesh.m_Name));
            m_RootNodes[mesh.m_NodeName].m_SceneTranslation = submesh.m_ScenePos;
            m_RootNodes[mesh.m_NodeName].m_SceneRotation = submesh.m_SceneRotate;
            m_RootNodes[mesh.m_NodeName].m_SceneScale = submesh.m_SceneScale;
        }
    }

    void MeshController::SetModelPack(Modelpack* modelpack)
    {
        m_RefToModelPack = modelpack;
    }

    Modelpack* MeshController::GetModelPack()
    {
        return m_RefToModelPack;
    }

    MeshBuffer* MeshController::GetMeshData(std::string_view meshName)
    {
        auto IndexItr = m_MeshIndexMap.find(meshName.data());

        if (IndexItr == m_MeshIndexMap.end()) return nullptr;
       
           

        return &m_MeshData[IndexItr->second];
    }

    std::map<std::string, SceneNode>& MeshController::GetRoots()
    {
        return m_RootNodes;
    }




}

