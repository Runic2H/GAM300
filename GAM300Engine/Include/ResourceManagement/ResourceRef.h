#pragma once
#include "dotnet/ImportExport.h"
#include "Identifier/Identifier.h"
namespace TDS
{
	template <typename T>
	struct TypeLoader
	{
		static T* Create()
		{
			return new T();

		}
		static void Destroy(T* ptr)
		{
			delete ptr;
		};
	};

	struct Resource_Ref
	{
		UniqueID m_GUID;
		TypeIdentifier m_Identifier;
		virtual bool IsPointer() = 0;
		virtual void SetNullGUID() = 0;
	};


	struct UniversalReference : public Resource_Ref
	{
		void* m_Reference;

		virtual bool IsPointer() override
		{
			return (m_GUID.GetUniqueID() & 1) == 0;
		}
		virtual void SetNullGUID() override
		{
			m_GUID.setNull();
		}
	};
	template <typename Type>
	struct SingleTypeReference : public Resource_Ref
	{
		Type* m_Reference;

		virtual bool IsPointer() override
		{
			return (m_GUID.GetUniqueID() & 1) == 0;
		}
		virtual void SetNullGUID() override
		{
			m_GUID.setNull();
		}
	};
	struct GuidTypeIDKey
	{
		GuidTypeIDKey(UniqueID& guid, TypeIdentifier& identifier) :m_GUID(guid), m_typeIdentifier(identifier) {};
		~GuidTypeIDKey() {}
		UniqueID m_GUID;
		TypeIdentifier m_typeIdentifier;
		bool operator==(const GuidTypeIDKey& other) const noexcept
		{
			return m_GUID == other.m_GUID && m_typeIdentifier == other.m_typeIdentifier;
		}

	};

	struct CombineHash
	{
		std::size_t operator()(GuidTypeIDKey key) const
		{
			std::size_t hash1 = std::hash<std::uint64_t>{}(key.m_GUID.GetUniqueID());
			std::size_t hash2 = key.m_typeIdentifier.m_TypeHash;

			return hash1 ^ (hash2 << 1);
		}
	};

}