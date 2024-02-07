#pragma once


namespace TDS
{

	template <typename SERIALIZER_TYPE>
	class Serialization
	{
	public:
		Serialization() {}
		~Serialization() {}

		bool OpenFile(std::string_view path, bool is_read)
		{
			static_cast<SERIALIZER_TYPE*>(this)->OpenFile(path, is_read);
		}

		void Close()
		{
			static_cast<SERIALIZER_TYPE*>(this)->Close();
		}

		template <typename T>
		void Serialize(T& obj)
		{
			static_cast<SERIALIZER_TYPE*>(this)->Serialize(obj);
		}

		template <typename T>
		void Deserialize(T& obj)
		{
			static_cast<SERIALIZER_TYPE*>(this)->Deserialize(obj);
		}
		template<typename... Args>
		void Serialize(const std::tuple<Args...>& tuple) 
		{
			static_cast<SERIALIZER_TYPE*>(this)->Serialize(tuple);
		}

		template<typename... Args>
		std::tuple<Args...> Deserialize()
		{
			return static_cast<SERIALIZER_TYPE*>(this)->Deserialize();
		}
	};



}