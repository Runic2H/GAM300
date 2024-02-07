#pragma once
#include <Identifier/TypeInformation.h>
namespace TDS
{
	class HashID
	{
	private:
		std::uint64_t m_Val;

		constexpr void Combine(std::uint64_t other)
		{
			m_Val ^= other + 0x9e3779b9 + (m_Val << 6) + (m_Val >> 2);
		}

	public:
		constexpr HashID() : HashID(0)
		{}

		constexpr HashID(std::uint64_t val) : m_Val(val)
		{}

		constexpr HashID(const HashID& other) = default;
		constexpr HashID& operator= (const HashID& other) = default;

		constexpr HashID(HashID&& other) noexcept = default;
		constexpr HashID& operator=(HashID&& other) noexcept = default;

		constexpr inline bool operator==(const HashID& other) const
		{
			return (m_Val == other.m_Val);
		}

		constexpr inline bool operator!=(const HashID& other) const
		{
			return (m_Val != other.m_Val);
		}

		constexpr inline std::uint64_t Value() const
		{
			return m_Val;
		}


		template<class T>
		void Add(const T& value)
		{
			if constexpr (std::is_same_v<T, HashID> || std::is_base_of_v<HashID, T>)
				Combine(value.Value());
			else if constexpr (HashGettorExist<T>)
				Combine(value.GetHash().Value());
			else if constexpr (std::is_fundamental_v<T> || std::is_pointer_v<T> || std::is_enum_v<T>)
			{
				static_assert(sizeof(T) <= sizeof(uintmax_t));
				uintmax_t value_raw;
				if constexpr (sizeof(uintmax_t) > sizeof(T))
				{
					std::memset(&value_raw, 0, sizeof(uintmax_t));
				}
				std::memcpy(&value_raw, &value, sizeof(T));
				Combine(value_raw);
			}


		}


		template <typename T>
		static inline HashID GetHash(const T& val)
		{
			HashID hashcode{};
			hashcode.Add(val);
			return hashcode;
		}

		static constexpr inline HashID GetHash(const char* val)
		{
			HashID hashcode{};

			for (; *val; ++val)
				hashcode.Combine(*val);

			return hashcode;

		}


	};


}