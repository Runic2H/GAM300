#pragma once
#include "Identifier/TypeInformation.h"
namespace TDS
{

	/*
	I am trying to avoid doing this because I might as well use RTTR... Type traits should only be for general complex types and not SPECIFIC custom types
	*/



	DEFINE_CONCEPT_TRAIT(Is_Vec2)
	{
		REQUIRE_MEMBER_CONVERTIBLE(x, float)
			REQUIRE_MEMBER_CONVERTIBLE(y, float)
			REQUIRE_MEMBER_TYPE(magnitude(), float)
		{
			T::back()
		} -> std::same_as<T>;
	};


	DEFINE_CONCEPT_TRAIT(Is_Vec3)
	{
		REQUIRE_MEMBER_CONVERTIBLE(x, float)
			REQUIRE_MEMBER_CONVERTIBLE(y, float)
			REQUIRE_MEMBER_CONVERTIBLE(z, float)
		{
			a.magnitude()
		} -> std::same_as<float>;
		{ T::back() } -> std::same_as<T>;

	};

	DEFINE_CONCEPT_TRAITS(Is_AABB, const Vec3& v, float radius)
	{
		{ a.m_min } -> Is_Vec3;
		{ a.m_max } -> Is_Vec3;

		{ T() } -> std::same_as<T>;
		{ T(v, radius) } -> std::same_as<T>;
		{ T(v, v) } -> std::same_as<T>;

		{ a.setNull() } -> std::same_as<void>;
		{ a.isNull() } -> std::same_as<bool>;
		{ a.extend(radius) } -> std::same_as<void>;
		{ a.extend(v) } -> std::same_as<void>;
		{ a.translate(v) } -> std::same_as<void>;
		{ a.getCenter() } -> Is_Vec3;
	};

	template <typename T>
	inline constexpr bool is_directly_serializable = std::is_arithmetic_v<T> || std::is_same_v<T, std::string>;
}