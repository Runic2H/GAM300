#pragma once
namespace TDS
{

	struct GlobalCast
	{
		template <typename T>
		operator T();
	};

	template <typename T, typename... Args>
	consteval auto member_count() {
		static_assert(std::is_aggregate_v<std::remove_cvref_t<T>>);
		if constexpr (requires { T{ {Args{}...}, { GlobalCast{} } }; } == false) {
			return sizeof...(Args);
		}
		else {
			return member_count<T, Args..., GlobalCast>();
		}
	}

	template <typename T, typename Visitor>
	decltype(auto) visit_members(T&& object, Visitor&& visitor) 
	{
		constexpr auto Count = member_count<std::remove_cvref_t<T>>() + 1;
		if constexpr (Count == 0) 
		{
			return visitor();
		}
		else if constexpr (Count == 1)
		{
			auto&& [a1] = object;
			return visitor(std::forward<decltype(a1)>(a1));
		}
		else if constexpr (Count == 2)
		{
			auto&& [a1, a2] = object;
			return visitor(std::forward<decltype(a1)>(a1), std::forward<decltype(a2)>(a2));
		}
		else if constexpr (Count == 3) 
		{
			auto&& [a1, a2, a3] = object;
			return visitor(std::forward<decltype(a1)>(a1), std::forward<decltype(a2)>(a2), std::forward<decltype(a3)>(a3));
		}
		else if constexpr (Count == 4) 
		{
			auto&& [a1, a2, a3, a4] = object;
			return visitor(std::forward<decltype(a1)>(a1), std::forward<decltype(a2)>(a2), std::forward<decltype(a3)>(a3), std::forward<decltype(a4)>(a4));
		}
		else if constexpr (Count == 5)
		{
			auto&& [a1, a2, a3, a4, a5] = object;
			return visitor(std::forward<decltype(a1)>(a1), std::forward<decltype(a2)>(a2), std::forward<decltype(a3)>(a3), std::forward<decltype(a4)>(a4), std::forward<decltype(a5)>(a5));
		}
		else if constexpr (Count == 6) 
		{
			auto&& [a1, a2, a3, a4, a5, a6] = object;
			return visitor(std::forward<decltype(a1)>(a1), std::forward<decltype(a2)>(a2), std::forward<decltype(a3)>(a3), std::forward<decltype(a4)>(a4), std::forward<decltype(a5)>(a5), std::forward<decltype(a6)>(a6));
		}
		else if constexpr (Count == 7) 
		{
			auto&& [a1, a2, a3, a4, a5, a6, a7] = object;
			return visitor(std::forward<decltype(a1)>(a1), std::forward<decltype(a2)>(a2), std::forward<decltype(a3)>(a3), std::forward<decltype(a4)>(a4), std::forward<decltype(a5)>(a5), std::forward<decltype(a6)>(a6), std::forward<decltype(a7)>(a7));
		}
		else if constexpr (Count == 8) 
		{
			auto&& [a1, a2, a3, a4, a5, a6, a7, a8] = object;
			return visitor(std::forward<decltype(a1)>(a1), std::forward<decltype(a2)>(a2), std::forward<decltype(a3)>(a3), std::forward<decltype(a4)>(a4), std::forward<decltype(a5)>(a5), std::forward<decltype(a6)>(a6), std::forward<decltype(a7)>(a7), std::forward<decltype(a8)>(a8));
		}
		else if constexpr (Count == 9) 
		{
			auto&& [a1, a2, a3, a4, a5, a6, a7, a8, a9] = object;
			return visitor(std::forward<decltype(a1)>(a1), std::forward<decltype(a2)>(a2), std::forward<decltype(a3)>(a3), std::forward<decltype(a4)>(a4), std::forward<decltype(a5)>(a5), std::forward<decltype(a6)>(a6), std::forward<decltype(a7)>(a7), std::forward<decltype(a8)>(a8), std::forward<decltype(a9)>(a9));
		}
		else if constexpr (Count == 10)
		{
			auto&& [a1, a2, a3, a4, a5, a6, a7, a8, a9, a10] = object;
			return visitor(std::forward<decltype(a1)>(a1), std::forward<decltype(a2)>(a2), std::forward<decltype(a3)>(a3), std::forward<decltype(a4)>(a4), std::forward<decltype(a5)>(a5), std::forward<decltype(a6)>(a6), std::forward<decltype(a7)>(a7), std::forward<decltype(a8)>(a8), std::forward<decltype(a9)>(a9), std::forward<decltype(a10)>(a10));
		}
		else if constexpr (Count == 11) 
		{
			auto&& [a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11] = object;
			return visitor(std::forward<decltype(a1)>(a1), std::forward<decltype(a2)>(a2), std::forward<decltype(a3)>(a3), std::forward<decltype(a4)>(a4), std::forward<decltype(a5)>(a5), std::forward<decltype(a6)>(a6), std::forward<decltype(a7)>(a7), std::forward<decltype(a8)>(a8), std::forward<decltype(a9)>(a9), std::forward<decltype(a10)>(a10), std::forward<decltype(a11)>(a11));
		}
		else if constexpr (Count == 12) 
		{
			auto&& [a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12] = object;
			return visitor(std::forward<decltype(a1)>(a1), std::forward<decltype(a2)>(a2), std::forward<decltype(a3)>(a3), std::forward<decltype(a4)>(a4), std::forward<decltype(a5)>(a5), std::forward<decltype(a6)>(a6), std::forward<decltype(a7)>(a7), std::forward<decltype(a8)>(a8), std::forward<decltype(a9)>(a9), std::forward<decltype(a10)>(a10), std::forward<decltype(a11)>(a11), std::forward<decltype(a12)>(a12));
		}
		else if constexpr (Count == 13)
		{
			auto&& [a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13] = object;
			return visitor(std::forward<decltype(a1)>(a1), std::forward<decltype(a2)>(a2), std::forward<decltype(a3)>(a3), std::forward<decltype(a4)>(a4), std::forward<decltype(a5)>(a5), std::forward<decltype(a6)>(a6), std::forward<decltype(a7)>(a7), std::forward<decltype(a8)>(a8), std::forward<decltype(a9)>(a9), std::forward<decltype(a10)>(a10), std::forward<decltype(a11)>(a11), std::forward<decltype(a12)>(a12), std::forward<decltype(a13)>(a13));
		}
		else if constexpr (Count == 14)
		{
			auto&& [a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14] = object;
			return visitor(std::forward<decltype(a1)>(a1), std::forward<decltype(a2)>(a2), std::forward<decltype(a3)>(a3), std::forward<decltype(a4)>(a4), std::forward<decltype(a5)>(a5), std::forward<decltype(a6)>(a6), std::forward<decltype(a7)>(a7), std::forward<decltype(a8)>(a8), std::forward<decltype(a9)>(a9), std::forward<decltype(a10)>(a10), std::forward<decltype(a11)>(a11), std::forward<decltype(a12)>(a12), std::forward<decltype(a13)>(a13), std::forward<decltype(a14)>(a14));
		}
		else if constexpr (Count == 15) 
		{
			auto&& [a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15] = object;
			return visitor(std::forward<decltype(a1)>(a1), std::forward<decltype(a2)>(a2),
				std::forward<decltype(a3)>(a3), std::forward<decltype(a4)>(a4),
				std::forward<decltype(a5)>(a5), std::forward<decltype(a6)>(a6),
				std::forward<decltype(a7)>(a7), std::forward<decltype(a8)>(a8),
				std::forward<decltype(a9)>(a9), std::forward<decltype(a10)>(a10),
				std::forward<decltype(a11)>(a11), std::forward<decltype(a12)>(a12),
				std::forward<decltype(a13)>(a13), std::forward<decltype(a14)>(a14),
				std::forward<decltype(a15)>(a15));
		}
		

		
	}





	template <typename T>
	struct AggregateType;

	#define CREATE_AGGREGATE(TYPE_NAME)\
		template <>\
		struct AggregateType<TYPE_NAME>

	#define DEFINE_AGGREGATE_MEMBER(TYPE, NAME) TYPE NAME;

	#define GET_AGGREGATE_TYPE(TYPE, NAME) AggregateType<TYPE>


//	template <typename T>
//	struct RecordedFields
//	{
//		static consteval auto GetFields()
//		{
//			return std::make_tuple(
//				std::make_tuple(
//					"", ""
//				)
//			);
//		}
//	};
//
//
//
//#define BEGIN_RECORDING_FIELDS(NAME_TYPE)\
//	template <>\
//	struct RecordedFields<NAME_TYPE>\
//	{\
//		using Type = NAME_TYPE;\
//		static consteval auto GetFields() \
//		{\
//			return std::make_tuple(
//
//#define RECORD_FIELDS(DATA) std::make_tuple(#DATA, &Type::DATA)
//
//#define STOP_RECORDING_FIELDS\
//			);\
//		}\
//	};


	template <typename T>
	struct RecordedFields
	{
		static consteval auto GetFields()
		{
			return std::make_tuple("");
		
		}
	};


#define CREATE_RECORDED_FIELDS(TYPE_NAME)\
	template <>\
	struct RecordedFields<TYPE_NAME>\
	{\
		static consteval auto GetFields()\
		{

#define RECORD_FIELDS(...)\
			return std::make_tuple(__VA_ARGS__);\
		}\
	}
		
			
	
	
	





}