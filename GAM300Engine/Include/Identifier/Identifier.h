#pragma once
#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS
#include <hash_map>
#include <hash_set>
#include <unordered_set>
#include <unordered_map>
#include <regex>
#include <map>
#include <typeinfo>
#include "GUID.h"

namespace TDS
{
	template <typename T>
	std::string getTypeName()
	{
		std::string typeInfoName = typeid(T).name();
		std::regex re("(class|struct|enum|union) [^ ]+");
		std::smatch match;

		//Remove mangling
		if (std::regex_search(typeInfoName, match, re))
		{
			typeInfoName = match.str().substr(match.position(1) + match.length(1) + 1);
		}
		if (std::isdigit(typeInfoName[0]))
		{
			size_t i = 0;
			while (i < typeInfoName.length() && std::isdigit(typeInfoName[i]))
			{
				i++;
			}
			typeInfoName = typeInfoName.substr(i);
		}
		std::regex ns_re("(.+::)");
		typeInfoName = std::regex_replace(typeInfoName, ns_re, "");

		return typeInfoName;
	}

	struct TypeIdentifier
	{
		size_t m_TypeHash;
		size_t m_NameHash;
		std::string m_CustomName;
		std::string m_ClassType;

		template <typename Type>
		void CreateTypeIDByClass(Type& typeref)
		{
			std::string TypeName = getTypeName<decltype(typeref)>();
			m_TypeHash = std::hash<std::string>{}(TypeName);
		}
		template <typename Type>
		void GetTypeName()
		{
			std::string TypeName = getTypeName<Type>();
			m_TypeHash = std::hash<std::string>{}(TypeName);
		}
		void CreateTypeIDByName(std::string_view customName)
		{
			m_CustomName = customName;
			m_NameHash = std::hash<std::string>{}(m_CustomName);
		}
		bool operator==(const TypeIdentifier& other) const noexcept
		{
			return m_TypeHash == other.m_TypeHash;
		}

	};



}