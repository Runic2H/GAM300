#pragma once
#include "CompilerSettings.h"
#include "GeomStructures.h"
namespace TDS
{
	/*!*************************************************************************
 * Raw input mesh that is received
 ***************************************************************************/
	struct InputMesh
	{
		std::string m_MeshName;
		std::string m_Name;
		std::vector<RawVertex> m_RawVertices;
		std::vector<std::uint32_t> m_InputIndices;
		std::int32_t m_iMaterialInstance;
	};
	/*!*************************************************************************
	 * Optimized mesh given to the renderer
	 ***************************************************************************/
	struct OptimizedMesh
	{
		std::string m_MeshName;
		std::string m_Name;
		std::vector<Vec3> m_Pos;
		std::vector< GeomCompiled::ExtraVertices> m_ExtraVertices;
		std::vector<std::uint32_t> m_Indices;
		std::int32_t m_iMaterialInstance;
	};
	class GeomCompiler
	{
	private:
		using INPUT_NODES = std::vector<const aiNode*>;
		std::shared_ptr<FinalGeom> m_Final;
		std::shared_ptr<GeomCompiled> output;
		const aiScene* m_Scene;
		std::vector<INPUT_NODES> m_MeshNodes;
		std::vector<InputMesh> m_InputMeshes;
		Descriptor m_CurrDesc;
	public:
		/*!*************************************************************************
		 * Contructor & Destructor for GeomCompiler
		 ***************************************************************************/
		static std::shared_ptr<GeomCompiler> m_Instance;
		GeomCompiler();
		~GeomCompiler();
		/*!*************************************************************************
		 * Main function that load the mesh and start compiling
		 ***************************************************************************/
		void Init(std::string_view descSettings);
		bool LoadDescriptor();
		void LoadAndCompile();
		void LoadModel(std::string_view path);
		/*!*************************************************************************
		 * Helper functions
		 ***************************************************************************/
		void ImportData(std::vector<InputMesh>& InputNodes);
		void MergeData(std::vector<InputMesh>& InputNodes);
		void CreateFinalGeom(const std::vector<OptimizedMesh>& Nodes);
		void CreateOptimizeForm(std::vector<InputMesh>& InputNodes, std::vector<OptimizedMesh>& outPut);
		void Optimize(std::vector<InputMesh>& InputNodes);
		void ClearAllData();

		/*!*************************************************************************
		 * Coverting all the meshes into geometry before outputting into a binary
		 * file
		 ***************************************************************************/
		void ProcessNode(aiNode* Node);
		void ProcessMesh(const aiMesh& AssimpMesh, const aiMatrix4x4& Transform, InputMesh& MeshPart, int iTexCordinates, int iColors);
		void Apply(const aiNode& Node, std::vector<InputMesh>& Nodes);
		void ConvertToGeom();
		void OutputGeom(std::string_view outPath);

		inline static std::shared_ptr<GeomCompiler> GetInstance()
		{
			if (m_Instance == 0)
				m_Instance = std::make_shared<GeomCompiler>();
			return m_Instance;
		}

		inline Descriptor& GetDescriptor()
		{
			return m_CurrDesc;
		}
	};
}