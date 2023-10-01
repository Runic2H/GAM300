/*!*************************************************************************
****
\file Model.cpp
\author Ng Zuo Xian Amadeus
\par DP email: ng.z@digipen.edu
\par Course: CSD3400
\par Section: a
\date 22-9-2023
\brief  Function definitions of the Model Class
****************************************************************************
***/
#include "vulkanTools/Model.h"
#include "dds/tinyddsloader.h"
#include "vulkanTools/GraphicsResourceDefines.h"

#ifndef MODEL_DIR
#define MODEL_Dir "../assets/models/"
#endif // !MODEL_DIR

namespace TDS {

	//model class constructor
	Model::Model(VulkanInstance& Instance, const Model::Builder& Builder) : m_Instance(Instance) {
		createVertexBuffer(Builder.Vertices);
		createIndexBuffer(Builder.Indices);
	}

	//model class deconstructor
	Model::~Model() {}

	//creates model data from specified filepath
	std::unique_ptr<Model> Model::createModelFromFile(VulkanInstance& Instance, const std::string& FilePath) {
		Builder Build{};
		Build.LoadModel(MODEL_Dir + FilePath);
		return std::make_unique<Model>(Instance, Build);
	}

	//create vertexbuffer for model
	void Model::createVertexBuffer(const std::vector<Vertex>& Vertices) {
		m_VertexCount = static_cast<uint32_t>(Vertices.size());
		assert(m_VertexCount >= 3 && "Vertexcount must be at least 3");
		VkDeviceSize buffersize = sizeof(Vertices[0]) * m_VertexCount;
		uint32_t vertexsize = sizeof(Vertices[0]);

		Buffer stagingBuffer{ m_Instance, vertexsize, m_VertexCount, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, };
		stagingBuffer.map();
		stagingBuffer.WritetoBuffer((void*)Vertices.data());

		m_VertexBuffer = std::make_unique<Buffer>(m_Instance, vertexsize, m_VertexCount, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

		m_Instance.copyBuffer(stagingBuffer.getBuffer(), m_VertexBuffer->getBuffer(), buffersize);
	}

	//create indexbuffer for model
	void Model::createIndexBuffer(const std::vector<uint32_t>& Indices) {
		m_IndexCount = static_cast<uint32_t>(Indices.size());
		m_hasIndexBuffer = m_IndexCount > 0;

		if (!m_hasIndexBuffer) return;

		VkDeviceSize buffersize = sizeof(Indices[0]) * m_IndexCount;
		uint32_t indexsize = sizeof(Indices[0]);

		Buffer stagingBuffer{ m_Instance, indexsize, m_IndexCount, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, };
		stagingBuffer.map();
		stagingBuffer.WritetoBuffer((void*)Indices.data());

		m_IndexBuffer = std::make_unique<Buffer>(m_Instance, indexsize, m_IndexCount, VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
		m_Instance.copyBuffer(stagingBuffer.getBuffer(), m_IndexBuffer->getBuffer(), buffersize);
	}

	//draw the commandbuffer
	void Model::draw(VkCommandBuffer cmdbuffer) {
		if (m_hasIndexBuffer)
			vkCmdDrawIndexed(cmdbuffer, m_IndexCount, 1, 0, 0, 0);
		else
			vkCmdDraw(cmdbuffer, m_VertexCount, 1, 0, 0);
	}

	//binds the model to the commandbuffer
	void Model::bind(VkCommandBuffer cmdbuffer) {
		VkBuffer buffers[] = { m_VertexBuffer->getBuffer() };
		VkDeviceSize offset[] = { 0 };
		vkCmdBindVertexBuffers(cmdbuffer, 0, 1, buffers, offset);
		if (m_hasIndexBuffer)
			vkCmdBindIndexBuffer(cmdbuffer, m_IndexBuffer->getBuffer(), 0, VK_INDEX_TYPE_UINT32);
	}

	//set binding descriptions for the model
	std::vector<VkVertexInputBindingDescription> Model::Vertex::getBindingDescriptions() {
		std::vector<VkVertexInputBindingDescription> BindingDescription(1);
		BindingDescription[0].binding = 0;
		BindingDescription[0].stride = sizeof(Vertex);
		BindingDescription[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
		return BindingDescription;
	}

	//set attribute descriptions for the model
	std::vector<VkVertexInputAttributeDescription> Model::Vertex::getAttributeDescriptions() {
		std::vector< VkVertexInputAttributeDescription> attributedescription{};
		attributedescription.push_back({ 0,0,VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, Pos) });
		attributedescription.push_back({ 1,0,VK_FORMAT_R32G32B32_SFLOAT , offsetof(Vertex, Color) });
		attributedescription.push_back({ 2,0,VK_FORMAT_R32G32_SFLOAT, offsetof(Vertex, UV) });
		attributedescription.push_back({ 3,0,VK_FORMAT_R32G32B32A32_SFLOAT, offsetof(Vertex, Normals) });
		return attributedescription;
	}

	//load model from the serialized data created from geom compiler
	void Model::Builder::LoadModel(const std::string& filepath)
	{
		GeomCompiled output;
		DeserializeGeom(output, filepath);
		LoadGeomData(output);
	}

	//get data from geom
	void  Model::Builder::LoadGeomData(GeomCompiled& geom)
	{
		iColor color{};
		Vertices.resize(geom.m_Pos.size());
		Indices.resize(geom.m_Indices.size());
		std::copy(geom.m_Indices.begin(), geom.m_Indices.end(), Indices.data());
		for (size_t i = 0; i < geom.m_Pos.size(); ++i) {
			Vertices[i].Pos = geom.m_Pos[i];


			if (i < geom.m_Extra.size())
			{
				Vertices[i].UV = geom.m_Extra[i].m_UV;

				Vertices[i].Normals = Vec4(geom.m_Extra[i].m_Normal.x, geom.m_Extra[i].m_Normal.y, geom.m_Extra[i].m_Normal.z, 1.0f);
				//m_VertexData[i].m_fTanget = geom.m_Extra[i].m_Tanget;
				//m_VertexData[i].m_fBitangent = geom.m_Extra[i].m_Bitangent;
				color = iColor(geom.m_Extra[i].m_Colour);
				Vertices[i].Color = color.m_RGBA;

				//m_VertexData[i].m_Tangent = iColor(Vec4(geom.m_Extra[i].m_Tanget.x, geom.m_Extra[i].m_Tanget.y, geom.m_Extra[i].m_Tanget.z, 1.0f));
				//m_VertexData[i].m_Bitangent = iColor(Vec4(geom.m_Extra[i].m_Bitangent.x, geom.m_Extra[i].m_Bitangent.y, geom.m_Extra[i].m_Bitangent.z, 1.0f));
				//m_VertexData[i].m_Normal = iColor(Vec4(geom.m_Extra[i].m_Normal.x, geom.m_Extra[i].m_Normal.y, geom.m_Extra[i].m_Normal.z, 1.0f));
			}
		}
	}

	//deserialize the geom data
	void Model::DeserializeGeom(GeomCompiled& geomOut, std::string_view PathData)
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

		auto deserializeMesh = [](std::ifstream& in, GeomCompiled::Mesh& mesh)
			{
				in.read(reinterpret_cast<char*>(&mesh.m_Name), sizeof(mesh.m_Name));
			};

		auto deserializeSubMesh = [](std::ifstream& in, GeomCompiled::SubMesh& subMesh)
			{
				in.read(reinterpret_cast<char*>(&subMesh.m_nFaces), sizeof(subMesh.m_nFaces));
				in.read(reinterpret_cast<char*>(&subMesh.m_iIndices), sizeof(subMesh.m_iIndices));
				in.read(reinterpret_cast<char*>(&subMesh.m_iVertices), sizeof(subMesh.m_iVertices));
				in.read(reinterpret_cast<char*>(&subMesh.m_nVertices), sizeof(subMesh.m_nVertices));
				in.read(reinterpret_cast<char*>(&subMesh.m_iMaterial), sizeof(subMesh.m_iMaterial));
			};

		auto deserializeExtraVertices = [&](std::ifstream& in, GeomCompiled::ExtraVertices& extraVertices)
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

}