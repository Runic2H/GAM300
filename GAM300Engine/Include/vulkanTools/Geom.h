#ifndef TDS_GEOM
#define TDS_GEOM

#include <array>
#include <vector>
#include "MathCommon.h"
namespace TDS
{
	struct GeomCompiled
	{
		struct Mesh
		{
			std::array<char, 64> m_Name;
		};

		struct SubMesh
		{
			std::uint32_t m_nFaces;
			std::uint32_t m_iIndices;
			std::uint32_t m_iVertices;
			std::uint32_t m_nVertices;
			std::uint16_t m_iMaterial;
		};

		struct ExtraVertices
		{
			Vec2 m_UV;
			Vec3 m_Normal;
			Vec3 m_Tanget;
			Vec3 m_Bitangent;
			std::uint32_t m_Colour{};
		};
		std::vector<Vec3> m_Pos;
		std::vector<Mesh> m_Mesh;
		std::vector<SubMesh> m_SubMesh;
		std::vector<ExtraVertices> m_Extra;
		std::vector<std::uint32_t> m_Indices;
	};
}

#endif //!TDS_GEOM