/*!*****************************************************************************
 * \file          GeomCompiler.cpp
 * \author        Eugene Ho Shu Sheng
 * \par DP email: shushengeugene.ho@digipen.edu
 * \par Course:   CSD3400
 * \par Section:  A
 * \date          01/10/2023
 * \brief		  This file contains the implementation of the GeomCompiler class.
 *******************************************************************************/
#include "Tools/GeomCompiler.h"
#include "meshoptimizer-master/src/meshoptimizer.h"
#include "GraphicsResource/GeomStruct.h"



std::shared_ptr<TDS::GeomCompiler> TDS::GeomCompiler::m_Instance{};
TDS::GeomCompiler::GeomCompiler()
{
	this->m_Final = std::make_shared<FinalGeom>();
	this->output = std::make_shared<GeomCompiled>();
}

TDS::GeomCompiler::~GeomCompiler()
{
}


void TDS::GeomCompiler::LoadAndCompile()
{
	ImportData(m_InputMeshes);
	MergeData(m_InputMeshes);
	GenerateLOD(m_InputMeshes);
	Optimize(m_InputMeshes);
	std::vector<OptimizedMesh> optiseMesh;
	CreateOptimizeForm(m_InputMeshes, optiseMesh);
	CreateFinalGeom(optiseMesh);
	ConvertToGeom();
}

std::string TDS::GeomCompiler::LoadModel()
{
	ClearAllData();
	LoadDescriptor();
	return OutputGeom(OutPath);

}

void TDS::GeomCompiler::ImportData(std::vector<InputMesh>& InputNodes)
{
	aiMatrix4x4 identityMatrix; 
	Apply(*m_Scene->mRootNode, InputNodes, identityMatrix);
}

void TDS::GeomCompiler::MergeData(std::vector<InputMesh>& InputNodes)
{
	if (m_CurrDesc.m_Descriptor.MergeMesh)
	{
		for (size_t i = 0; i < InputNodes.size(); ++i)
		{
			if (InputNodes[i].m_RawVertices.size() == 0 || InputNodes[i].m_InputIndices.size() == 0)
			{
				InputNodes.erase(InputNodes.begin() + i);
				--i;
			}
		}
		for (size_t i = 0; i < InputNodes.size(); ++i)
		{
			for (size_t j = i + 1; j < InputNodes.size(); ++j)
			{

				if (InputNodes[i].m_Name == InputNodes[j].m_Name &&
					InputNodes[i].m_iMaterialInstance == InputNodes[j].m_iMaterialInstance &&
					InputNodes[i].m_RawVertices.size() == InputNodes[j].m_RawVertices.size() &&
					InputNodes[i].m_InputIndices == InputNodes[j].m_InputIndices)
				{
					InputNodes.erase(InputNodes.begin() + j);
					--j;
				}
			}
		}
	}
	std::map<std::string, int> existingNames;
	for (size_t i = 0; i < InputNodes.size(); ++i)
	{
		std::string name = InputNodes[i].m_Name;
		if (existingNames.find(InputNodes[i].m_Name) != existingNames.end())
		{
			++existingNames[InputNodes[i].m_Name];
			InputNodes[i].m_Name = name + ("__" + std::to_string(existingNames[InputNodes[i].m_Name]));
		}
		else
		{
			existingNames[InputNodes[i].m_Name] = 0;
		}
		if (m_CurrTransforms.find(InputNodes[i].m_Name) != m_CurrTransforms.end())
		{
			m_CurrTransforms[InputNodes[i].m_Name] = InputNodes[i].m_CurrTransform;
		}
		else
		{
			m_CurrTransforms[InputNodes[i].m_Name] = InputNodes[i].m_CurrTransform;
		}
	}

	//for (size_t i = 0; i < InputNodes.size(); ++i)
	//{
	//	for (size_t j = i + 1; j < InputNodes.size(); ++j)
	//	{
	//		if (InputNodes[i].m_iMaterialInstance == InputNodes[j].m_iMaterialInstance &&
	//			InputNodes[i].m_Name == InputNodes[j].m_Name)
	//		{
	//			const int  iBaseVertex = static_cast<int>(InputNodes[i].m_RawVertices.size());
	//			const auto iBaseIndex = InputNodes[i].m_InputIndices.size();
	//			InputNodes[i].m_RawVertices.insert(InputNodes[i].m_RawVertices.end(), InputNodes[j].m_RawVertices.begin(), InputNodes[j].m_RawVertices.end());
	//			InputNodes[i].m_InputIndices.insert(InputNodes[i].m_InputIndices.end(), InputNodes[j].m_InputIndices.begin(), InputNodes[j].m_InputIndices.end());
	//			InputNodes[i].m_Name = InputNodes[j].m_Name;
	//			InputNodes[i].m_iMaterialInstance = InputNodes[j].m_iMaterialInstance;

	//			for (size_t index = iBaseIndex; index < InputNodes[i].m_InputIndices.size(); ++index)
	//			{
	//				InputNodes[i].m_InputIndices[index] += iBaseIndex;
	//			}
	//			InputNodes.erase(InputNodes.begin() + j);
	//			--j;
	//		}

	//	}
	//}
}

void TDS::GeomCompiler::CreateFinalGeom(const std::vector<OptimizedMesh>& Nodes)
{
	for (size_t i = 0; i < Nodes.size(); ++i)
	{
		size_t FinalMeshIndex = UINT64_MAX;
		for (size_t j = 0; j < m_Final->m_Meshes.size(); ++j)
		{
			if (m_Final->m_Meshes[j].m_Name == Nodes[i].m_Name)
			{
				FinalMeshIndex = j;
				break;
			}
		}

		if (FinalMeshIndex == UINT64_MAX)
		{
			FinalMeshIndex = m_Final->m_Meshes.size();
			m_Final->m_Meshes.emplace_back();
			m_Final->m_Meshes.back().m_Name = Nodes[i].m_Name;
		}

		m_Final->m_Meshes[(std::int32_t)FinalMeshIndex].m_SubMeshes.emplace_back();
		m_Final->m_Meshes[(std::int32_t)FinalMeshIndex].m_SubMeshes.back().m_Pos = Nodes[i].m_Pos;
		m_Final->m_Meshes[(std::int32_t)FinalMeshIndex].m_SubMeshes.back().m_Extra = Nodes[i].m_ExtraVertices;
		m_Final->m_Meshes[(std::int32_t)FinalMeshIndex].m_SubMeshes.back().m_Indices = Nodes[i].m_Indices;
		m_Final->m_Meshes[(std::int32_t)FinalMeshIndex].m_SubMeshes.back().m_iMaterial = Nodes[i].m_iMaterialInstance;

	}
}

void TDS::GeomCompiler::CreateOptimizeForm(std::vector<InputMesh>& InputNodes, std::vector<OptimizedMesh>& output)
{
	std::vector<OptimizedMesh> compressed(InputNodes.size());
	for (size_t i = 0; i < InputNodes.size(); ++i)
	{
		std::vector<Vec3> VPos;
		std::vector<GeomCompiled::ExtraVertices> ExtraVert;

		for (auto& vertice : InputNodes[i].m_RawVertices)
		{
			GeomCompiled::ExtraVertices vertexExtra{};
			vertexExtra.m_UV = vertice.m_UV;
			vertexExtra.m_Bitangent = vertice.m_fBitangent;
			vertexExtra.m_Normal = vertice.m_fNormal;
			vertexExtra.m_Tanget = vertice.m_fTanget;
			vertexExtra.m_Colour = vertice.m_Color.m_Value;
			ExtraVert.push_back(vertexExtra);
			VPos.push_back(vertice.m_Pos);

		}
		compressed[i].m_Pos = VPos;
		compressed[i].m_ExtraVertices = ExtraVert;
		compressed[i].m_Indices = InputNodes[i].m_InputIndices;
		compressed[i].m_Name = InputNodes[i].m_Name;
		compressed[i].m_MeshName = InputNodes[i].m_MeshName;



	}
	output = compressed;
}

void TDS::GeomCompiler::Optimize(std::vector<InputMesh>& InputNodes)
{
	std::vector<InputMesh> out;

	for (auto& mesh : InputNodes)
	{
		size_t indxCnt = mesh.m_InputIndices.size();
		std::vector<std::uint32_t> remappedIndices(indxCnt);



		// Ensure the size of RawVertices is correct
		size_t vertexCount = mesh.m_RawVertices.size();

		// Check if indices are within bounds of vertices
		for (size_t i = 0; i < indxCnt; ++i) {
			if (mesh.m_InputIndices[i] >= vertexCount) {
				// Handle or log index out-of-bounds error
				// For debugging purposes, you can print the problematic index
				std::cout << "Index out of bounds: " << mesh.m_InputIndices[i] << std::endl;
				// You might want to consider how to handle this situation
				// For example, skipping this mesh or correcting the indices
			}
		}
		size_t VtxCnt = meshopt_generateVertexRemap(&remappedIndices[0], mesh.m_InputIndices.data(), indxCnt, mesh.m_RawVertices.data(), mesh.m_RawVertices.size(), sizeof(RawVertex));

		InputMesh compressedSubMesh{};
		compressedSubMesh.m_InputIndices.resize(mesh.m_InputIndices.size());
		compressedSubMesh.m_RawVertices.resize(VtxCnt);
		compressedSubMesh.m_iMaterialInstance = mesh.m_iMaterialInstance;
		compressedSubMesh.m_Name = mesh.m_Name;
		meshopt_remapIndexBuffer(compressedSubMesh.m_InputIndices.data(), mesh.m_InputIndices.data(), mesh.m_InputIndices.size(), &remappedIndices[0]);
		meshopt_remapVertexBuffer(compressedSubMesh.m_RawVertices.data(), mesh.m_RawVertices.data(), mesh.m_InputIndices.size(), sizeof(RawVertex), &remappedIndices[0]);
		meshopt_optimizeVertexCache(compressedSubMesh.m_InputIndices.data(), compressedSubMesh.m_InputIndices.data(), compressedSubMesh.m_InputIndices.size(), VtxCnt);
		meshopt_optimizeOverdraw(compressedSubMesh.m_InputIndices.data(), compressedSubMesh.m_InputIndices.data(), indxCnt, &compressedSubMesh.m_RawVertices[0].m_Pos.x, VtxCnt, sizeof(RawVertex), 1.05f);
		compressedSubMesh.m_RawVertices.resize(meshopt_optimizeVertexFetch(compressedSubMesh.m_RawVertices.data(), compressedSubMesh.m_InputIndices.data(), indxCnt, compressedSubMesh.m_RawVertices.data(), VtxCnt, sizeof(RawVertex)));
		for (auto& Lod : mesh.m_GeneratedLODS)
		{
			meshopt_optimizeVertexCache(Lod.m_Indices.data(), Lod.m_Indices.data(), Lod.m_Indices.size(), mesh.m_RawVertices.size());
			meshopt_optimizeOverdraw(Lod.m_Indices.data(), Lod.m_Indices.data(), Lod.m_Indices.size(), &mesh.m_RawVertices[0].m_Pos.x, mesh.m_RawVertices.size(), sizeof(RawVertex), 1.05f);
		}
		out.push_back(compressedSubMesh);
	}
	InputNodes = out;
}

void TDS::GeomCompiler::GenerateLOD(std::vector<InputMesh>& InputNodes)
{
	if (m_CurrDesc.m_LodOptions.m_CreateLOD)
	{
		for (auto& Mesh : InputNodes)
		{
			for (size_t i = 1; i < m_CurrDesc.m_LodOptions.m_Max_num_lods; ++i)
			{
				const float threshold = std::powf(m_CurrDesc.m_LodOptions.ReductionFactor, float(i));
				const size_t targetIndexCount = size_t(Mesh.m_InputIndices.size() * threshold) / 3 * 3;
				const float target_error = 1e-2f;
				const auto& S = (Mesh.m_GeneratedLODS.size()) ? Mesh.m_GeneratedLODS.back().m_Indices : Mesh.m_InputIndices;

				if (S.size() < targetIndexCount)
					break;

				auto& newLOD = Mesh.m_GeneratedLODS.emplace_back();
				newLOD.m_Indices.resize(S.size());
				newLOD.m_Indices.resize(meshopt_simplify(newLOD.m_Indices.data(), S.data(), S.size(), &Mesh.m_RawVertices[0].m_Pos.x, Mesh.m_RawVertices.size(), sizeof(RawVertex), targetIndexCount, target_error));


			}
		}
	}
}

void TDS::GeomCompiler::ClearAllData()
{
	m_MeshNodes.clear();
	m_InputMeshes.clear();
	m_Final->m_Filename.clear();
	m_Final->m_Meshes.clear();
	output->m_Extra.clear();
	output->m_Indices.clear();
	output->m_Mesh.clear();
	output->m_Pos.clear();
	output->m_SubMesh.clear();
	m_CurrTransforms.clear();
}

void TDS::GeomCompiler::ProcessNode(aiNode* Node)
{
	for (std::uint32_t i = 0; i < Node->mNumMeshes; ++i)
	{
		aiMesh* pMesh = m_Scene->mMeshes[Node->mMeshes[i]];

		m_MeshNodes[Node->mMeshes[i]].push_back(Node);
		m_Test.emplace_back();
	}

	for (std::uint32_t i = 0; i < Node->mNumChildren; ++i)
	{
		ProcessNode(Node->mChildren[i]);
	}
}

void TDS::GeomCompiler::ProcessMesh(const aiMesh& AssimpMesh, const aiMatrix4x4& Transform, InputMesh& MeshPart, int iTexCordinates, int iColors)
{
	aiQuaternion presentRotation{};
	aiVector3D p{};
	Transform.DecomposeNoScaling(presentRotation, p);



	MeshPart.m_Name = AssimpMesh.mName.C_Str();
	MeshPart.m_iMaterialInstance = AssimpMesh.mMaterialIndex;
	MeshPart.m_RawVertices.resize(AssimpMesh.mNumVertices);
	MeshPart.m_CurrTransform = Transform;
	//std::string name = MeshPart.m_Name;
	//if (m_ExistedName.find(name) != m_ExistedName.end())
	//{
	//	m_ExistedName[name]++;
	//	name = name + "_" + std::to_string(m_ExistedName[name]);
	//	
	//}
	//else
	//{
	//	m_ExistedName[name] = 0;
	//}
	//m_CurrTransforms[name] = Transform;
	for (auto i = 0u; i < AssimpMesh.mNumVertices; ++i)
	{
		RawVertex& Vertex = MeshPart.m_RawVertices[i];

		auto L = /*Transform **/ AssimpMesh.mVertices[i];

		Vertex.m_Pos = Vec3(static_cast<float>(L.x), static_cast<float>(L.y), static_cast<float>(L.z));
		if (iTexCordinates == -1)
		{
			Vertex.m_UV = Vec2(0.f, 0.f);
		}
		else
		{
			Vertex.m_UV = Vec2(static_cast<float>(AssimpMesh.mTextureCoords[iTexCordinates][i].x)
				, static_cast<float>(AssimpMesh.mTextureCoords[iTexCordinates][i].y));
		}

		if (iColors == -1)
		{
			Vec4 RGBA(255.f, 0.f, 0.f, 1.f);

			Vertex.m_Color.m_RGBA = RGBA;
		}
		else
		{
			Vec4 RGBA(static_cast<float>(AssimpMesh.mColors[iColors][i].r)
				, static_cast<float>(AssimpMesh.mColors[iColors][i].g)
				, static_cast<float>(AssimpMesh.mColors[iColors][i].b)
				, static_cast<float>(AssimpMesh.mColors[iColors][i].a)
			);

			Vertex.m_Color = iColor(RGBA);
		}

		if (AssimpMesh.HasTangentsAndBitangents())
		{
			const auto T = presentRotation.Rotate(AssimpMesh.mTangents[i]);
			const auto B = presentRotation.Rotate(AssimpMesh.mBitangents[i]);
			const auto N = presentRotation.Rotate(AssimpMesh.mNormals[i]);

			Vertex.m_fNormal = Vec3(N.x, N.y, N.z);
			Vertex.m_fTanget = Vec3(T.x, T.y, T.z);
			Vertex.m_fBitangent = Vec3(B.x, B.y, B.z);

			Vertex.m_fNormal.Normalize();
			Vertex.m_fTanget.Normalize();
			Vertex.m_fBitangent.Normalize();

			Vertex.m_Tangent.m_RGBA.x = static_cast<std::uint8_t>(static_cast<std::int8_t>(Vertex.m_fTanget.x < 0 ? std::max(-128, static_cast<int>(Vertex.m_fTanget.x * 128)) : std::min(127, static_cast<int>(Vertex.m_fTanget.x * 127))));
			Vertex.m_Tangent.m_RGBA.y = static_cast<std::uint8_t>(static_cast<std::int8_t>(Vertex.m_fTanget.y < 0 ? std::max(-128, static_cast<int>(Vertex.m_fTanget.y * 128)) : std::min(127, static_cast<int>(Vertex.m_fTanget.y * 127))));
			Vertex.m_Tangent.m_RGBA.z = static_cast<std::uint8_t>(static_cast<std::int8_t>(Vertex.m_fTanget.z < 0 ? std::max(-128, static_cast<int>(Vertex.m_fTanget.z * 128)) : std::min(127, static_cast<int>(Vertex.m_fTanget.z * 127))));
			Vertex.m_Tangent.m_RGBA.w = 0;

			Vertex.m_Normal.m_RGBA.x = static_cast<std::uint8_t>(static_cast<std::int8_t>(Vertex.m_fNormal.x < 0 ? std::max(-128, static_cast<int>(Vertex.m_fNormal.x * 128)) : std::min(127, static_cast<int>(Vertex.m_fNormal.x * 127))));
			Vertex.m_Normal.m_RGBA.y = static_cast<std::uint8_t>(static_cast<std::int8_t>(Vertex.m_fNormal.y < 0 ? std::max(-128, static_cast<int>(Vertex.m_fNormal.y * 128)) : std::min(127, static_cast<int>(Vertex.m_fNormal.y * 127))));
			Vertex.m_Normal.m_RGBA.z = static_cast<std::uint8_t>(static_cast<std::int8_t>(Vertex.m_fNormal.z < 0 ? std::max(-128, static_cast<int>(Vertex.m_fNormal.z * 128)) : std::min(127, static_cast<int>(Vertex.m_fNormal.z * 127))));
			Vec3 crossResult = Vec3::Cross(Vertex.m_fTanget, Vertex.m_fNormal);
			float dotRes = Vec3::Dot(crossResult, Vertex.m_fBitangent);

			Vertex.m_Normal.m_RGBA.w = static_cast<std::uint8_t>(static_cast<std::int8_t>(dotRes) > 0 ? 127 : -128);
		}
		else
		{
			Vertex.m_Tangent.m_RGBA.x = 0xff;
			Vertex.m_Tangent.m_RGBA.y = 0;
			Vertex.m_Tangent.m_RGBA.z = 0;
			Vertex.m_Tangent.m_RGBA.w = 0;

			const auto N = presentRotation.Rotate(AssimpMesh.mNormals[i]);

			Vertex.m_fNormal = Vec3{ N.x, N.y, N.z };

			Vertex.m_fTanget = Vec3(1.f, 0.f, 0.f);
			Vertex.m_fBitangent = Vec3(1.f, 0.f, 0.f);

			Vertex.m_fNormal.Normalize();

			Vertex.m_Normal.m_RGBA.x = static_cast<std::uint8_t>(static_cast<std::int8_t>(Vertex.m_fNormal.x < 0 ? std::max(-128, static_cast<int>(Vertex.m_fNormal.x * 128)) : std::min(127, static_cast<int>(Vertex.m_fNormal.x * 127))));
			Vertex.m_Normal.m_RGBA.y = static_cast<std::uint8_t>(static_cast<std::int8_t>(Vertex.m_fNormal.y < 0 ? std::max(-128, static_cast<int>(Vertex.m_fNormal.y * 128)) : std::min(127, static_cast<int>(Vertex.m_fNormal.y * 127))));
			Vertex.m_Normal.m_RGBA.z = static_cast<std::uint8_t>(static_cast<std::int8_t>(Vertex.m_fNormal.z < 0 ? std::max(-128, static_cast<int>(Vertex.m_fNormal.z * 128)) : std::min(127, static_cast<int>(Vertex.m_fNormal.z * 127))));
			Vertex.m_Normal.m_RGBA.w = 127;
			
		}
	}
	for (std::uint32_t k = 0; k < AssimpMesh.mNumFaces; ++k)
	{
		for (std::uint32_t j = 0; j < AssimpMesh.mFaces[k].mNumIndices; ++j)
		{
			MeshPart.m_InputIndices.push_back(AssimpMesh.mFaces[k].mIndices[j]);
		}
	}
}

void TDS::GeomCompiler::Apply(const aiNode& Node, std::vector<InputMesh>& Nodes, const aiMatrix4x4& ParentTransform)
{
	aiVector3D scaling((ai_real)m_CurrDesc.m_Descriptor.m_L2W.m_Scale[0], (ai_real)m_CurrDesc.m_Descriptor.m_L2W.m_Scale[1], (ai_real)m_CurrDesc.m_Descriptor.m_L2W.m_Scale[2]);
	aiMatrix4x4 descriptorMatrix{};
	descriptorMatrix.Scaling(scaling, descriptorMatrix);
	descriptorMatrix.RotationX((ai_real)m_CurrDesc.m_Descriptor.m_L2W.m_Rotate[0], descriptorMatrix);
	descriptorMatrix.RotationY((ai_real)m_CurrDesc.m_Descriptor.m_L2W.m_Rotate[1], descriptorMatrix);
	descriptorMatrix.RotationZ((ai_real)m_CurrDesc.m_Descriptor.m_L2W.m_Rotate[2], descriptorMatrix);
	aiVector3D translation((ai_real)m_CurrDesc.m_Descriptor.m_L2W.m_Translate[0], (ai_real)m_CurrDesc.m_Descriptor.m_L2W.m_Translate[1], (ai_real)m_CurrDesc.m_Descriptor.m_L2W.m_Translate[2]);
	descriptorMatrix.Translation(translation, descriptorMatrix);

	aiMatrix4x4 Transform = ParentTransform * descriptorMatrix * Node.mTransformation;
	size_t Base = Nodes.size();
	Nodes.resize(Base + m_Scene->mNumMeshes);


	for (std::uint32_t i = 0; i < Node.mNumMeshes; ++i)
	{
		if (!m_Scene->mMeshes[Node.mMeshes[i]]->HasPositions())
		{
			std::cout << "WARNING : Mesh : " << m_Scene->mMeshes[Node.mMeshes[i]]->mName.C_Str() << " doesnt have position" << std::endl;
			std::cout << "Skiping...";
			continue;
		}
		if (!m_Scene->mMeshes[Node.mMeshes[i]]->HasFaces())
		{
			std::cout << "WARNING : Mesh : " << m_Scene->mMeshes[Node.mMeshes[i]]->mName.C_Str() << " doesnt have a face" << std::endl;
			std::cout << "Skiping...";
			continue;
		}
		if (!m_Scene->mMeshes[Node.mMeshes[i]]->HasNormals())
		{
			std::cout << "WARNING : Mesh : " << m_Scene->mMeshes[Node.mMeshes[i]]->mName.C_Str() << " doesnt have a normal" << std::endl;
			std::cout << "Skiping...";
			continue;
		}
		if (!m_Scene->mMeshes[Node.mMeshes[i]]->HasTangentsAndBitangents())
		{
			std::cout << "WARNING : Mesh : " << m_Scene->mMeshes[Node.mMeshes[i]]->mName.C_Str() << " doesnt have tangents" << std::endl;
			std::cout << "Skiping...";
			continue;
		}
		if (!m_Scene->mMeshes[Node.mMeshes[i]]->GetNumUVChannels() == 0)
		{
			std::cout << "WARNING : Mesh : " << m_Scene->mMeshes[Node.mMeshes[i]]->mName.C_Str() << " doesnt have UV coordinates" << std::endl;
		}
		else if (!m_Scene->mMeshes[Node.mMeshes[i]]->GetNumUVChannels() > 1)
		{
			std::cout << "WARNING : Mesh : " << m_Scene->mMeshes[Node.mMeshes[i]]->mName.C_Str() << " have more than 1 UV coordinates" << std::endl;
		}
		std::int32_t textureIndex = { -1 };
		for (std::uint32_t j = 0; j < m_Scene->mMeshes[Node.mMeshes[i]]->GetNumUVChannels(); ++j)
		{
			if (m_Scene->mMeshes[Node.mMeshes[i]]->HasTextureCoords(j))
			{
				textureIndex = j;
			}
		}
		std::int32_t colorIndex = { -1 };
		for (std::uint32_t j = 0; j < m_Scene->mMeshes[Node.mMeshes[i]]->GetNumColorChannels(); ++j)
		{
			if (m_Scene->mMeshes[Node.mMeshes[i]]->HasVertexColors(j))
			{
				colorIndex = j;
			}
		}

		ProcessMesh(*m_Scene->mMeshes[Node.mMeshes[i]], Transform, Nodes[Base++], textureIndex, colorIndex);


	}

	if (Base != Nodes.size())
	{
		Nodes.erase(Nodes.begin() + Base, Nodes.end());
	}

	for (std::uint32_t i = 0; i < Node.mNumChildren; ++i)
	{
		Apply(*Node.mChildren[i], Nodes, Transform);
	}


}

void TDS::GeomCompiler::ConvertToGeom()
{
	for (const auto& inputMesh : m_Final->m_Meshes)
	{
		GeomCompiled::Mesh outputMesh;
		strcpy_s(outputMesh.m_Name.data(), outputMesh.m_Name.size(), inputMesh.m_Name.c_str());
		if (inputMesh.m_Name.length() < 64)
			std::copy(inputMesh.m_Name.begin(), inputMesh.m_Name.end(), outputMesh.m_Name.begin());

		else
			std::copy(inputMesh.m_Name.begin(), inputMesh.m_Name.begin() + 64, outputMesh.m_Name.begin());

		output->m_Mesh.push_back(outputMesh);

		for (const auto& inputSubMesh : inputMesh.m_SubMeshes)
		{
			GeomCompiled::SubMesh outputSubMesh;
			outputSubMesh.m_nFaces = inputSubMesh.m_Indices.size() / 3;
			outputSubMesh.m_iIndices = output->m_Indices.size();
			outputSubMesh.m_iVertices = output->m_Pos.size();
			outputSubMesh.m_nVertices = inputSubMesh.m_Pos.size();
			outputSubMesh.m_iMaterial = static_cast<std::uint16_t>(inputSubMesh.m_iMaterial);
			output->m_Pos.insert(output->m_Pos.end(), inputSubMesh.m_Pos.begin(), inputSubMesh.m_Pos.end());
			output->m_Indices.insert(output->m_Indices.end(), inputSubMesh.m_Indices.begin(), inputSubMesh.m_Indices.end());

			output->m_Extra.insert(output->m_Extra.end(), inputSubMesh.m_Extra.begin(), inputSubMesh.m_Extra.end());

			output->m_SubMesh.push_back(outputSubMesh);

		}

	}

}



std::string TDS::GeomCompiler::OutputGeom(std::string_view outPath)
{
	std::string out = OutPath;
	out += "_Bin";
	out += ".bin";
	std::ofstream outFile(out, std::ios::binary);
	if (!outFile)
	{
		std::cerr << "ERROR : Could not open file for writing!\n";
		return out;
	}

	const std::size_t bufferSize = 1024 * 1024;
	std::vector<char> buffer(bufferSize);
	outFile.rdbuf()->pubsetbuf(buffer.data(), bufferSize);

	auto serializeVec3 = [](std::ofstream& out, const Vec3& vec) {
		out.write(reinterpret_cast<const char*>(&vec.x), sizeof(vec.x));
		out.write(reinterpret_cast<const char*>(&vec.y), sizeof(vec.y));
		out.write(reinterpret_cast<const char*>(&vec.z), sizeof(vec.z));
	};

	auto serializeVec2 = [](std::ofstream& out, const Vec2& vec)
	{
		out.write(reinterpret_cast<const char*>(&vec.x), sizeof(vec.x));
		out.write(reinterpret_cast<const char*>(&vec.y), sizeof(vec.y));
	};

	auto serializeMesh = [](std::ofstream& out, const GeomCompiled::Mesh& mesh) {
		out.write(reinterpret_cast<const char*>(&mesh.m_Name), sizeof(mesh.m_Name));
	};

	auto serializeSubMesh = [](std::ofstream& out, const GeomCompiled::SubMesh& subMesh) {
		out.write(reinterpret_cast<const char*>(&subMesh.m_nFaces), sizeof(subMesh.m_nFaces));
		out.write(reinterpret_cast<const char*>(&subMesh.m_iIndices), sizeof(subMesh.m_iIndices));
		out.write(reinterpret_cast<const char*>(&subMesh.m_iVertices), sizeof(subMesh.m_iVertices));
		out.write(reinterpret_cast<const char*>(&subMesh.m_nVertices), sizeof(subMesh.m_nVertices));
		out.write(reinterpret_cast<const char*>(&subMesh.m_iMaterial), sizeof(subMesh.m_iMaterial));
	};

	auto serializeExtraVertices = [&](std::ofstream& out, const GeomCompiled::ExtraVertices& extraVertices) {
		serializeVec2(out, extraVertices.m_UV);
		serializeVec3(out, extraVertices.m_Normal);
		serializeVec3(out, extraVertices.m_Tanget);
		serializeVec3(out, extraVertices.m_Bitangent);
		out.write(reinterpret_cast<const char*>(&extraVertices.m_Colour), sizeof(extraVertices.m_Colour));
	};




	uint32_t meshSize = output->m_Mesh.size();
	outFile.write(reinterpret_cast<const char*>(&meshSize), sizeof(meshSize));
	for (const auto& mesh : output->m_Mesh)
	{
		serializeMesh(outFile, mesh);
	}

	uint32_t subMeshSize = output->m_SubMesh.size();
	outFile.write(reinterpret_cast<const char*>(&subMeshSize), sizeof(subMeshSize));
	for (const auto& subMesh : output->m_SubMesh)
	{
		serializeSubMesh(outFile, subMesh);
	}

	uint32_t posSize = output->m_Pos.size();
	outFile.write(reinterpret_cast<const char*>(&posSize), sizeof(posSize));
	for (const auto& pos : output->m_Pos)
	{
		serializeVec3(outFile, pos);
	}

	uint32_t extraSize = output->m_Extra.size();
	outFile.write(reinterpret_cast<const char*>(&extraSize), sizeof(extraSize));
	for (const auto& extra : output->m_Extra)
	{
		serializeExtraVertices(outFile, extra);
	}

	uint32_t indicesSize = output->m_Indices.size();
	outFile.write(reinterpret_cast<const char*>(&indicesSize), sizeof(indicesSize));
	outFile.write(reinterpret_cast<const char*>(output->m_Indices.data()), indicesSize * sizeof(uint32_t));

	outFile.close();
	return out;
}





void TDS::GeomCompiler::Init(std::string_view descSettings)
{
	m_CurrDesc.Serialize(descSettings, true);
}

void TDS::GeomCompiler::InitDesc(GeomDescriptor desc)
{
	m_CurrDesc = desc;
}

bool TDS::GeomCompiler::LoadDescriptor()
{
	std::cout << "Importing Model : " << m_CurrDesc.m_Descriptor.m_FilePath.c_str() << "...\n";
	Assimp::Importer importer{};
	importer.SetPropertyBool(AI_CONFIG_PP_PTV_NORMALIZE, true);
	std::uint32_t AssimpFlag = 
		aiProcess_Triangulate
		| aiProcess_LimitBoneWeights   
		| aiProcess_GenUVCoords
		//| aiProcess_PreTransformVertices
		| aiProcess_TransformUVCoords          
		| aiProcess_FindInstances             
		| aiProcess_GenSmoothNormals
		| aiProcess_ForceGenNormals
		| aiProcess_CalcTangentSpace
		| aiProcess_RemoveRedundantMaterials
		| aiProcess_FindInvalidData           
		| aiProcess_FlipUVs
		;
	std::string filePath = "../assets/models/" + m_CurrDesc.m_Descriptor.m_FilePath;
	m_Scene = importer.ReadFile(filePath, AssimpFlag);

	if (!m_Scene)
		return false;

	m_MeshNodes.resize(m_Scene->mNumMeshes);

	ProcessNode(m_Scene->mRootNode);




	for (std::uint32_t i = 0u; i < m_Scene->mNumMeshes; ++i)
	{
		const aiMesh& AssimpMesh = *m_Scene->mMeshes[i];
		const auto& InputNodes = m_MeshNodes[i];

		if (m_MeshNodes[i].size() == 0u)
		{
			std::cout << "ERROR: Mesh has no reference to the AiScene" << std::endl;
			return false;
		}

		if (AssimpMesh.HasBones())
		{
			if (m_MeshNodes[i].size() > 1)
			{
				std::cout << "ERROR: Multiple reference of bones are not supported." << std::endl;
				return false;
			}
		}

	}

	LoadAndCompile();
}
