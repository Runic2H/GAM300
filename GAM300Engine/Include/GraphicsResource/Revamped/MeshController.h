#pragma once
#include <pch.h>
#include "Geometry/AABB.h"
#include "dotnet/ImportExport.h"
namespace TDS
{
	class VMABuffer;

	struct MeshBuffer
	{
		std::shared_ptr<VMABuffer>							m_VertexBuffer = nullptr;
		std::shared_ptr<VMABuffer>							m_IndexBuffer = nullptr;
	};

	struct Modelpack;

	struct MeshNode
	{
		bool												m_FirstRender;
		std::string											m_MeshName;
	};

	struct SceneNode
	{
		std::string											m_NodeName = "";
		std::map<std::string, MeshNode>						m_MeshList;
		Vec3												m_SceneTranslation;
		Vec3												m_SceneRotation;
		Vec3												m_SceneScale;
	};


	class MeshController
	{
	private:
		Modelpack*											m_RefToModelPack = nullptr;
		std::map<std::string, SceneNode>					m_RootNodes;
		std::vector<MeshBuffer>								m_MeshData;
		std::unordered_map<std::string, std::uint32_t>		m_MeshIndexMap;

	public:

		bool												m_Loaded = false;

		MeshController() = default;
		~MeshController() = default;

		DLL_API bool			LoadMeshData(Modelpack& model);

		DLL_API void			Destroy();

		DLL_API void			BuildMeshTree();

		DLL_API void			SetModelPack(Modelpack* modelpack);

		DLL_API Modelpack*		GetModelPack();

		DLL_API MeshBuffer*		GetMeshData(std::string_view meshName);

		DLL_API std::map<std::string, SceneNode>& GetRoots();


	};



}