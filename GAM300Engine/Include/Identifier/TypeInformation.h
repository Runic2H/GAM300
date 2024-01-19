#pragma once
#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS
#include <hash_map>
#include <hash_set>
#include <unordered_set>
#include <unordered_map>
#include <regex>
#include <map>
#include <typeinfo>
#include <type_traits>

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

	template <typename T>
	std::string getTypeNameViaInput(T input)
	{
		std::string typeInfoName = typeid(decltype(input)).name();
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


	template<typename T>
	concept Is_String = std::is_same_v<T, std::string> ||
		std::is_same_v<T, std::wstring> ||
		std::is_same_v<T, const char*> ||
		std::is_same_v<T, char*> ||
		std::is_same_v<T, const wchar_t*> ||
		std::is_same_v<T, wchar_t*>;

	template <typename T>
	concept Is_Container = !Is_String<T> && requires(T a) {
		typename T::value_type;
		typename T::iterator;
		typename T::const_iterator;
		{ a.begin() } -> std::same_as<decltype(a.begin())>;
		{ a.end() } -> std::same_as<decltype(a.end())>;
		{ a.size() } -> std::same_as<std::size_t>;
		{ a.empty() } -> std::same_as<bool>;
		{ a.clear() };
	};

	template <typename T, std::size_t N>
	concept Is_Std_Array = std::is_same_v<T, std::array<typename T::value_type, N>>
		&& requires(T a) {
			{ a.fill(typename T::value_type{}) };
			{ a.max_size() } -> std::same_as<std::size_t>;
	};



	template <typename T>
	concept Is_Builtin_Array = std::is_array_v<T>;

	
	template<typename T>
	concept Is_Associative_Container = requires(T a)
	{
		typename T::key_type; 
		{ a.find(typename T::key_type{}) } -> std::same_as<typename T::iterator>;
	};

	template<typename T>
	concept Is_Map_Like_Container = Is_Associative_Container<T> && requires(T a)
	{
		typename T::mapped_type;
	};


	template <typename T, typename = void>
	constexpr bool HashGettorExist = false;

	template <typename T>
	constexpr bool HashGettorExist<T, std::void_t<decltype(std::declval<T>().GetHash())>> = true;

	//Create custom typetraits Macros

#define DEFINE_CONCEPT_TRAIT(trait_name) \
    template <typename T> \
    concept trait_name = requires(T a)

#define DEFINE_CONCEPT_TRAITS(trait_name, ...)\
	template <typename T>\
	concept trait_name = requires(T a, __VA_ARGS__)


#define REQUIRE_MEMBER_TYPE(member, type) \
    { a.member } -> std::same_as<type>;


#define REQUIRE_MEMBER_CONVERTIBLE(member, type) \
    { a.member } -> std::convertible_to<type>;






}