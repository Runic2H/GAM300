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

			static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
			static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();

			bool operator==(const Vertex& p)const {
				return (Pos == p.Pos && Color == p.Color && UV == p.UV);
			}
		};

		struct Builder {
			std::vector<Vertex> Vertices;
			std::vector<uint32_t> Indices;
			void LoadModel(const std::string& filepath);
			void LoadGeomData(GeomCompiled& geom);
		};

		Model(VulkanInstance& Instance, const Builder& build);
		~Model();

		Model(const Model&) = delete;
		Model& operator=(const Model&) = delete;

		//after geom compiler
		static std::unique_ptr<Model> createModelFromFile(VulkanInstance& Instance, const std::string& FilePath);

		void bind(VkCommandBuffer cmdbuffer);
		void draw(VkCommandBuffer cmdbuffer);

		static void DeserializeGeom(GeomCompiled& geomOut, std::string_view PathData);
	private:
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