/*!*************************************************************************
****
\file Model.h
\author Ng Zuo Xian Amadeus
\par DP email: ng.z@digipen.edu
\par Course: CSD3400
\par Section: a
\date 22-9-2023
\brief  Contains the Model Class and its member functions
****************************************************************************
***/
#ifndef TDS_VULKAN_MODEL
#define TDS_VULKAN_MODEL

#include "Buffer.h"
#include "vulkanInstance.h"
#include "MathCommon.h"
#include "Geom.h"
namespace TDS {
	class DLL_API Model {
	public:
		struct Vertex {
			Vec3 Pos;
			Vec3 Color;
			Vec4 Normals;
			Vec2 UV;

			//create binding and attribute descriptors
			static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
			static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();

			bool operator==(const Vertex& p)const {
				return (Pos == p.Pos && Color == p.Color && UV == p.UV);
			}
		};

		struct Builder {
			std::vector<Vertex> Vertices;
			std::vector<uint32_t> Indices;
			//create model
			void LoadModel(const std::string& filepath);
			//load data from the Deserialized geom
			void LoadGeomData(GeomCompiled& geom);
		};
		//Constructor and destructor
		Model(VulkanInstance& Instance, const Builder& build);
		~Model();

		//no copy constructor
		Model(const Model&) = delete;
		Model& operator=(const Model&) = delete;

		//after geom compiler
		static std::unique_ptr<Model> createModelFromFile(VulkanInstance& Instance, const std::string& FilePath);

		//binds model to the command buffer
		void bind(VkCommandBuffer cmdbuffer);
		//draws the model in the command buffer
		void draw(VkCommandBuffer cmdbuffer);

		//deserialize the data in the geom file
		static void DeserializeGeom(GeomCompiled& geomOut, std::string_view PathData);
	private:
		//create vertex and indexbuffer for the model
		void createVertexBuffer(const std::vector<Vertex>& Vertices);
		void createIndexBuffer(const std::vector<uint32_t>& Indices);

		VulkanInstance& m_Instance;

		std::unique_ptr<Buffer>		m_VertexBuffer;
		uint32_t					m_VertexCount;

		bool						m_hasIndexBuffer{ false };
		std::unique_ptr<Buffer>		m_IndexBuffer;
		uint32_t					m_IndexCount;


	};
}
#endif // !TDS_VULKAN_MODEL