#pragma once
#include "GeomStruct.h"
namespace TDS
{
	template <typename T>
	void SerializeGeom(T& obj, std::ofstream& out)
	{
		out.write(reinterpret_cast<char*>(&obj), sizeof(T));
	}

	template <>
	void SerializeGeom<std::string>(std::string& obj, std::ofstream& out)
	{
		std::size_t size = obj.size();
		out.write(reinterpret_cast<char*>(&size), sizeof(std::size_t));
		out.write(obj.c_str(), size);
	}

	template <>
	void SerializeGeom<Vec2>(Vec2& obj, std::ofstream& out)
	{
		out.write(reinterpret_cast<char*>(&obj.x), sizeof(obj.x));
		out.write(reinterpret_cast<char*>(&obj.y), sizeof(obj.y));
	}

	template <>
	void SerializeGeom<Vec3>(Vec3& obj, std::ofstream& out)
	{
		out.write(reinterpret_cast<char*>(&obj.x), sizeof(obj.x));
		out.write(reinterpret_cast<char*>(&obj.y), sizeof(obj.y));
		out.write(reinterpret_cast<char*>(&obj.z), sizeof(obj.z));
	}

	template<>
	void SerializeGeom<Vec4>(Vec4& obj, std::ofstream& out)
	{
		out.write(reinterpret_cast<char*>(&obj.x), sizeof(obj.x));
		out.write(reinterpret_cast<char*>(&obj.y), sizeof(obj.y));
		out.write(reinterpret_cast<char*>(&obj.z), sizeof(obj.z));
		out.write(reinterpret_cast<char*>(&obj.w), sizeof(obj.w));
	}

	template<>
	void SerializeGeom<Quat>(Quat& obj, std::ofstream& out)
	{
		out.write(reinterpret_cast<char*>(&obj.x), sizeof(obj.x));
		out.write(reinterpret_cast<char*>(&obj.y), sizeof(obj.y));
		out.write(reinterpret_cast<char*>(&obj.z), sizeof(obj.z));
		out.write(reinterpret_cast<char*>(&obj.w), sizeof(obj.w));
	}

	template <>
	void SerializeGeom<Mat4>(Mat4& obj, std::ofstream& out)
	{
		for (int i = 0; i < 4; ++i)
		{
			out.write(reinterpret_cast<char*>(&obj.m[i][0]), sizeof(obj.m[i][0]));
			out.write(reinterpret_cast<char*>(&obj.m[i][1]), sizeof(obj.m[i][1]));
			out.write(reinterpret_cast<char*>(&obj.m[i][2]), sizeof(obj.m[i][2]));
			out.write(reinterpret_cast<char*>(&obj.m[i][3]), sizeof(obj.m[i][3]));
		}
	}

	template <>
	void SerializeGeom<Mat3>(Mat3& obj, std::ofstream& out)
	{
		for (int i = 0; i < 3; ++i)
		{
			out.write(reinterpret_cast<char*>(&obj.m[i][0]), sizeof(obj.m[i][0]));
			out.write(reinterpret_cast<char*>(&obj.m[i][1]), sizeof(obj.m[i][1]));
			out.write(reinterpret_cast<char*>(&obj.m[i][2]), sizeof(obj.m[i][2]));
		}
	}

	template <>
	void SerializeGeom<Mat2>(Mat2& obj, std::ofstream& out)
	{
		for (int i = 0; i < 2; ++i)
		{
			out.write(reinterpret_cast<char*>(&obj.m[i][0]), sizeof(obj.m[i][0]));
			out.write(reinterpret_cast<char*>(&obj.m[i][1]), sizeof(obj.m[i][1]));
		}
	}

	template <>
	void SerializeGeom<AABB>(AABB& obj, std::ofstream& out)
	{
		Vec3 min, max;
		SerializeGeom(min, out);
		SerializeGeom(max, out);
		obj.SetMinMax(min, max);
	}

	template <>
	void SerializeGeom<TDSModel::Lod>(TDSModel::Lod& obj, std::ofstream& out)
	{
		SerializeGeom(obj.m_iSubmesh, out);
		SerializeGeom(obj.m_nSubmesh, out);
	}

	template <>
	void SerializeGeom<TDSModel::Mesh>(TDSModel::Mesh& obj, std::ofstream& out)
	{
		SerializeGeom(obj.m_Name, out);
		SerializeGeom(obj.m_nLODs, out);
		SerializeGeom(obj.m_iLOD, out);
		SerializeGeom(obj.m_NodeName, out);
		SerializeGeom(obj.m_ParentNode, out);
	}

	template <>
	void SerializeGeom<TDSModel::SubMesh>(TDSModel::SubMesh& obj, std::ofstream& out)
	{
		/*SerializeGeom(obj, out);*/
		SerializeGeom(obj.m_nFaces, out);
		SerializeGeom(obj.m_iIndices, out);
		SerializeGeom(obj.m_nIndices, out);
		SerializeGeom(obj.m_iVertices, out);
		SerializeGeom(obj.m_nVertices, out);
		SerializeGeom(obj.m_iMaterial, out);
	}

	template <>
	void SerializeGeom<TDSModel::BoneWeights>(TDSModel::BoneWeights& obj, std::ofstream& out)
	{
		SerializeGeom(obj.m_BoneID, out);
		SerializeGeom(obj.m_Weights, out);
	}

	template <>
	void SerializeGeom<TDSModel::Vertex>(TDSModel::Vertex& obj, std::ofstream& out)
	{
		SerializeGeom(obj.m_Position, out);
		SerializeGeom(obj.m_Bitangent, out);
		SerializeGeom(obj.m_Tangent, out);
		SerializeGeom(obj.m_Normal, out);
		SerializeGeom(obj.m_UV, out);
		SerializeGeom(obj.m_Color, out);
		/*SerializeGeom(obj.m_WeightPerVertex, out);*/
	}

	//Do an overload for std::vector
	template <typename T>
	void SerializeGeom(std::vector<T>& obj, std::ofstream& out)
	{
		std::uint32_t size = obj.size();
		out.write(reinterpret_cast<char*>(&size), sizeof(std::uint32_t));
		for (auto& elem : obj)
		{
			SerializeGeom(elem, out);
		}
	}

	//Do overload for array
	template <typename T, std::size_t N>
	void SerializeGeom(std::array<T, N>& obj, std::ofstream& out)
	{
		std::uint32_t size = obj.size();
		out.write(reinterpret_cast<char*>(&size), sizeof(std::uint32_t));
		for (auto& elem : obj)
		{
			SerializeGeom(elem, out);
		}
	}

	template <>
	void SerializeGeom<TDSModel>(TDSModel& obj, std::ofstream& out)
	{
		SerializeGeom(obj.m_Mesh, out);
		SerializeGeom(obj.m_SubMesh, out);
		SerializeGeom(obj.m_LODs, out);
		SerializeGeom(obj.m_ModelVertex, out);
		SerializeGeom(obj.m_Indices, out);
	}

	template <typename T>
	void DeserializeGeom(T& obj, std::ifstream& in)
	{
		in.read(reinterpret_cast<char*>(&obj), sizeof(T));
	}

	template <>
	void DeserializeGeom<std::string>(std::string& obj, std::ifstream& in)
	{
		std::uint32_t size;
		in.read(reinterpret_cast<char*>(&size), sizeof(std::uint32_t));
		obj.resize(size);
		in.read(&obj[0], size);
	}

	template <>
	void DeserializeGeom<Vec2>(Vec2& obj, std::ifstream& in)
	{
		in.read(reinterpret_cast<char*>(&obj.x), sizeof(obj.x));
		in.read(reinterpret_cast<char*>(&obj.y), sizeof(obj.y));
	}

	template <>
	void DeserializeGeom<Vec3>(Vec3& obj, std::ifstream& in)
	{
		in.read(reinterpret_cast<char*>(&obj.x), sizeof(obj.x));
		in.read(reinterpret_cast<char*>(&obj.y), sizeof(obj.y));
		in.read(reinterpret_cast<char*>(&obj.z), sizeof(obj.z));
	}

	template<>
	void DeserializeGeom<Vec4>(Vec4& obj, std::ifstream& in)
	{
		in.read(reinterpret_cast<char*>(&obj.x), sizeof(obj.x));
		in.read(reinterpret_cast<char*>(&obj.y), sizeof(obj.y));
		in.read(reinterpret_cast<char*>(&obj.z), sizeof(obj.z));
		in.read(reinterpret_cast<char*>(&obj.w), sizeof(obj.w));
	}

	template<>
	void DeserializeGeom<Quat>(Quat& obj, std::ifstream& in)
	{
		in.read(reinterpret_cast<char*>(&obj.x), sizeof(obj.x));
		in.read(reinterpret_cast<char*>(&obj.y), sizeof(obj.y));
		in.read(reinterpret_cast<char*>(&obj.z), sizeof(obj.z));
		in.read(reinterpret_cast<char*>(&obj.w), sizeof(obj.w));
	}

	template <>
	void DeserializeGeom<Mat4>(Mat4& obj, std::ifstream& in)
	{
		for (int i = 0; i < 4; ++i)
		{
			in.read(reinterpret_cast<char*>(&obj.m[i][0]), sizeof(obj.m[i][0]));
			in.read(reinterpret_cast<char*>(&obj.m[i][1]), sizeof(obj.m[i][1]));
			in.read(reinterpret_cast<char*>(&obj.m[i][2]), sizeof(obj.m[i][2]));
			in.read(reinterpret_cast<char*>(&obj.m[i][3]), sizeof(obj.m[i][3]));
		}
	}

	template <>
	void DeserializeGeom<Mat3>(Mat3& obj, std::ifstream& in)
	{
		for (int i = 0; i < 3; ++i)
		{
			in.read(reinterpret_cast<char*>(&obj.m[i][0]), sizeof(obj.m[i][0]));
			in.read(reinterpret_cast<char*>(&obj.m[i][1]), sizeof(obj.m[i][1]));
			in.read(reinterpret_cast<char*>(&obj.m[i][2]), sizeof(obj.m[i][2]));
		}
	}

	template <>
	void DeserializeGeom<Mat2>(Mat2& obj, std::ifstream& in)
	{
		for (int i = 0; i < 2; ++i)
		{
			in.read(reinterpret_cast<char*>(&obj.m[i][0]), sizeof(obj.m[i][0]));
			in.read(reinterpret_cast<char*>(&obj.m[i][1]), sizeof(obj.m[i][1]));
		}
	}

	template <>
	void DeserializeGeom<AABB>(AABB& obj, std::ifstream& in)
	{
		Vec3 min, max;
		DeserializeGeom(min, in);
		DeserializeGeom(max, in);
		obj.SetMinMax(min, max);
	}

	template <>
	void DeserializeGeom<TDSModel::Lod>(TDSModel::Lod& obj, std::ifstream& in)
	{
		DeserializeGeom(obj.m_iSubmesh, in);
		DeserializeGeom(obj.m_nSubmesh, in);
	}

	template <>
	void DeserializeGeom<TDSModel::Mesh>(TDSModel::Mesh& obj, std::ifstream& in)
	{
		DeserializeGeom(obj.m_Name, in);
		DeserializeGeom(obj.m_nLODs, in);
		DeserializeGeom(obj.m_iLOD, in);
		DeserializeGeom(obj.m_NodeName, in);
		DeserializeGeom(obj.m_ParentNode, in);
	}

	template <>
	void DeserializeGeom<TDSModel::SubMesh>(TDSModel::SubMesh& obj, std::ifstream& in)
	{
		//DeserializeGeom(obj.m_AABB, in);
		DeserializeGeom(obj.m_nFaces, in);
		DeserializeGeom(obj.m_iIndices, in);
		DeserializeGeom(obj.m_nIndices, in);
		DeserializeGeom(obj.m_iVertices, in);
		DeserializeGeom(obj.m_nVertices, in);
		DeserializeGeom(obj.m_iMaterial, in);
	}

	template <>
	void DeserializeGeom<TDSModel::BoneWeights>(TDSModel::BoneWeights& obj, std::ifstream& in)
	{
		DeserializeGeom(obj.m_BoneID, in);
		DeserializeGeom(obj.m_Weights, in);
	}

	template <>
	void DeserializeGeom<TDSModel::Vertex>(TDSModel::Vertex& obj, std::ifstream& in)
	{
		DeserializeGeom(obj.m_Position, in);
		DeserializeGeom(obj.m_Bitangent, in);
		DeserializeGeom(obj.m_Tangent, in);
		DeserializeGeom(obj.m_Normal, in);
		DeserializeGeom(obj.m_UV, in);
		DeserializeGeom(obj.m_Color, in);
		/*DeserializeGeom(obj.m_WeightPerVertex, in);*/
	}

	template <typename T>
	void DeserializeGeom(std::vector<T>& obj, std::ifstream& in)
	{
		std::uint32_t size;
		in.read(reinterpret_cast<char*>(&size), sizeof(std::uint32_t));
		obj.resize(size);
		for (auto& elem : obj)
		{
			DeserializeGeom(elem, in);
		}
	}

	template <typename T, std::size_t N>
	void DeserializeGeom(std::array<T, N>& obj, std::ifstream& in)
	{
		std::uint32_t size;
		in.read(reinterpret_cast<char*>(&size), sizeof(std::uint32_t));
		obj.resize(size);
		for (auto& elem : obj)
		{
			DeserializeGeom(elem, in);
		}
	}

	template <>
	void DeserializeGeom<TDSModel>(TDSModel& obj, std::ifstream& in)
	{
		DeserializeGeom(obj.m_Mesh, in);
		DeserializeGeom(obj.m_SubMesh, in);
		DeserializeGeom(obj.m_LODs, in);
		DeserializeGeom(obj.m_ModelVertex, in);
		DeserializeGeom(obj.m_Indices, in);
	}
}