#include "GraphicsResource/Revamped/ModelPack.h"
#include "Logger/Logger.h"
#include "GraphicsResource/GeomSerializer.h"
namespace TDS
{
	Modelpack::Modelpack()
	{
	}
	Modelpack::Modelpack(std::string_view Path)
	{
		if (!LoadModelPack(Path))
			TDS_ERROR("Failed to load {} ", Path.data());

	}
	Modelpack::~Modelpack()
	{
	}
	bool Modelpack::LoadModelPack(std::string_view path)
	{
		m_ModelHandle.Deserialize(path);
		return true;
		/*std::ifstream inFile(path.data(), std::ios::binary);
		if (!inFile)
		{
			return false;
		}

		DeserializeGeom(m_ModelHandle, inFile);

		inFile.close();*/
	}
	void Modelpack::Cleanup()
	{
		m_ModelHandle.m_Indices.clear();
		m_ModelHandle.m_LODs.clear();
		m_ModelHandle.m_Mesh.clear();
		m_ModelHandle.m_ModelVertex.clear();
		m_ModelHandle.m_SubMesh.clear();
	}
}