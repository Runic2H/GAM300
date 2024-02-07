#pragma once
#include "Serialization/Serialization.h"
#include "FastReflection.h"
#include "Identifier/TypeInformation.h"
#include "dotnet/ImportExport.h"
#include "Logger/Logger.h"
#include "GraphicsResource/GeomStruct.h"
namespace TDS
{

	class BinarySerializer : public Serialization<BinarySerializer>
	{
	private:
		std::fstream fileStream;

	public:
		template <typename T>
		void SerializeData(const T& data)
		{
			fileStream.write(reinterpret_cast<const char*>(&data), sizeof(T));
			if (!fileStream)
				TDS_CRITICAL("Failed to write {}", std::string(getTypeName<T>()).c_str());
		}



		template <typename T>
			requires std::is_arithmetic_v<T> || std::is_enum_v<T>
		void SerializeData(const T & data)
		{
			fileStream.write(reinterpret_cast<const char*>(&data), sizeof(T));
			if (!fileStream)
				TDS_CRITICAL("Failed to write {}", std::string(getTypeName<T>()).c_str());
		}

		template <typename T>
			requires Is_Container<T>
		void SerializeData(const T& data)
		{
			size_t size = data.size();
			SerializeData(size);
			for (const auto& ref : data)
			{
				SerializeData(ref);
			}
		}

		template <typename T>
			requires Is_Map_Like_Container<T>
		void SerializeData(const T& data)
		{
			size_t size = data.size();
			SerializeData(size);

			for (const auto& [key, value] : data)
			{
				SerializeData(key);
				SerializeData(value);
			}
		}

		template <typename T, std::size_t N>
			requires Is_Std_Array<T, N>
		void SerializeData(const T& data)
		{
			size_t size = data.size();
			SerializeData(size);
			for (const auto& item : data)
				SerializeData(item);
		}

		template <typename T>
			requires Is_String<T>
		void SerializeData(const T& data)
		{
			size_t length = data.length();
			SerializeData(length);
			fileStream.write(data.c_str(), length);
			if (!fileStream)
				TDS_CRITICAL("Failed to write {}", std::string(getTypeName<T>()).c_str());
		}

		template<typename T>
		void serializeMember(const T& member)
		{
			//if constexpr (std::is_arithmetic_v<T> || std::is_enum_v<T> || TDS::Is_String<T>) {
			SerializeData(member);
			/*}
			else {
				serializeFields(member);
			}*/
		}

		template<typename T>
		void serializeFields(const T& object)
		{
			visit_members(object, [this](auto&&... fields) {
				(serializeMember(std::forward<decltype(fields)>(fields)), ...);
				});
		}



		template<>
		void serializeMember(const Vec2& vec)
		{
			SerializeData(vec.x);
			SerializeData(vec.y);
		}

		template<>
		void serializeMember(const Vec3& vec)
		{
			SerializeData(vec.x);
			SerializeData(vec.y);
			SerializeData(vec.z);
		}

		template<>
		void serializeMember(const Vec4& vec)
		{
			SerializeData(vec.x);
			SerializeData(vec.y);
			SerializeData(vec.z);
			SerializeData(vec.w);
		}
		template<>
		void serializeMember(const AABB& aabb)
		{
			serializeMember(aabb.getMin());
			serializeMember(aabb.getMax());
		}

		template<>
		void serializeMember(const Mat4& mat)
		{
			for (int i = 0; i < 4; ++i)
			{
				for (int j = 0; j < 4; ++j)
				{
					SerializeData(mat.m[i][j]);
				}
			}
		}

		template <>
		void serializeMember(const Mat3& mat)
		{
			for (int i = 0; i < 3; ++i)
			{
				for (int j = 0; j < 3; ++j)
				{
					SerializeData(mat.m[i][j]);
				}
			}
		}

		template <>
		void serializeMember(const Mat2& mat)
		{
			for (int i = 0; i < 2; ++i)
			{
				for (int j = 0; j < 2; ++j)
				{
					SerializeData(mat.m[i][j]);
				}
			}
		}

		template <>
		void serializeMember(const TDSModel::BoneWeights& boneWeights)
		{
			SerializeData(boneWeights.m_BoneID);
			SerializeData(boneWeights.m_Weights);
		}


		template<>
		void serializeMember(const Quat& quat)
		{
			SerializeData(quat.x);
			SerializeData(quat.y);
			SerializeData(quat.z);
			SerializeData(quat.w);
		}

		template<typename T>
		void serializeTupleElement(const T& element)
		{
			SerializeData(element);
		}

		// Serialize tuple
		template<typename Tuple, std::size_t... Is>
		void serializeTuple(const Tuple& t, std::index_sequence<Is...>) 
		{
			(serializeTupleElement(std::get<Is>(t)), ...);
		}

	public:
		template <typename T>
			requires std::is_arithmetic_v<T> || std::is_enum_v<T>
		T DeserializeData() {
			T data;
			fileStream.read(reinterpret_cast<char*>(&data), sizeof(T));
			return data;
		}

		template <typename T>
			requires Is_Container<T>
		T DeserializeData()
		{
			size_t size = DeserializeData<size_t>();
			T container;
			for (size_t i = 0; i < size; ++i) {
				typename T::value_type element{};
				deserializeMember(element);
				container.insert(container.end(), element);
			}
			return container;
		}

		template <typename T>
			requires Is_Map_Like_Container<T>
		T DeserializeData()
		{
			size_t size = DeserializeData<size_t>();
			T map;
			for (size_t i = 0; i < size; ++i)
			{
				typename T::key_type key{};
				typename T::mapped_type value{};
				deserializeMember(key);
				deserializeMember(value);
				map.insert({ key, value });
			}
			return map;
		}

		template <typename T>
			requires Is_String<T>
		T DeserializeData()
		{
			size_t length = DeserializeData<size_t>();
			T str;
			str.resize(length);
			fileStream.read(&str[0], length);
			return str;
		}

		template <typename T, std::size_t N>
			requires Is_Std_Array<T, N>
		T DeserializeData()
		{
			T array;
			for (auto& item : array)
			{
				deserializeMember(item);
			}
			return array;
		}

		template<typename T>
		void deserializeMember(T& member)
		{
			/*if constexpr (std::is_arithmetic_v<T> || std::is_enum_v<T> || TDS::Is_String<T>)
			{*/
			member = DeserializeData<T>();
			/*}
			else
			{
				deserializeFields(member);
			}*/
		}

		template<>
		void deserializeMember(Vec2& vec)
		{
			vec.x = DeserializeData<float>();
			vec.y = DeserializeData<float>();
		}

		template<>
		void deserializeMember(Vec3& vec)
		{
			vec.x = DeserializeData<float>();
			vec.y = DeserializeData<float>();
			vec.z = DeserializeData<float>();
		}

		template<>
		void deserializeMember(Vec4& vec)
		{
			vec.x = DeserializeData<float>();
			vec.y = DeserializeData<float>();
			vec.z = DeserializeData<float>();
			vec.w = DeserializeData<float>();
		}

		template<>
		void deserializeMember(AABB& aabb)
		{
			Vec3 min{};
			Vec3 max{};
			deserializeMember(min);
			deserializeMember(max);
			aabb.SetMinMax(min, max);
		}

		template<>
		void deserializeMember(Mat4& mat)
		{
			for (int i = 0; i < 4; ++i)
			{
				for (int j = 0; j < 4; ++j)
				{
					mat.m[i][j] = DeserializeData<float>();
				}
			}
		}

		template <>
		void deserializeMember(Mat3& mat)
		{
			for (int i = 0; i < 3; ++i)
			{
				for (int j = 0; j < 3; ++j)
				{
					mat.m[i][j] = DeserializeData<float>();
				}
			}
		}

		template <>
		void deserializeMember(Mat2& mat)
		{
			for (int i = 0; i < 2; ++i)
			{
				for (int j = 0; j < 2; ++j)
				{
					mat.m[i][j] = DeserializeData<float>();
				}
			}
		}

		template<>
		void deserializeMember(Quat& quat)
		{
			quat.x = DeserializeData<float>();
			quat.y = DeserializeData<float>();
			quat.z = DeserializeData<float>();
			quat.w = DeserializeData<float>();
		}

		template <>
		void deserializeMember(TDSModel::BoneWeights& boneWeights)
		{
			deserializeMember(boneWeights.m_BoneID);
			deserializeMember(boneWeights.m_Weights);
		}


		template<typename T>
		void deserializeFields(T& object)
		{
			visit_members(object, [this](auto&&... fields)
				{
					(deserializeMember(std::forward<decltype(fields)>(fields)), ...);
				});
		}

		template<typename T>
		T deserializeTupleElement()
		{
			return DeserializeData<T>();
		}

		// Deserialize tuple
		template<typename Tuple, std::size_t... Is>
		Tuple deserializeTuple(std::index_sequence<Is...>) 
		{
			return std::make_tuple(deserializeTupleElement<std::tuple_element_t<Is, Tuple>>()...);
		}

	public:
		BinarySerializer();
		~BinarySerializer();

		DLL_API bool OpenFile(std::string_view path, bool is_read = false);

		DLL_API void Close();

		template <typename T>
		void Serialize(T& obj)
		{
			serializeFields(obj);
			//serializeMember(obj);
		}


		template <typename T>
		void Deserialize(T& obj)
		{
			deserializeFields(obj);
			//deserializeMember(obj);
		}

		template<typename... Args>
		void Serialize(const std::tuple<Args...>& tuple)
		{
			serializeTuple(tuple, std::index_sequence_for<Args...>{});
		}

		template<typename... Args>
		std::tuple<Args...> Deserialize() 
		{
			return deserializeTuple<std::tuple<Args...>>(std::index_sequence_for<Args...>{});
		}



	};



}