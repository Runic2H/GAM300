/*!*************************************************************************
****
\file iComponent.h
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 28-9-2023
\brief  This program declares the functions in the iComponent abstract class
****************************************************************************
***/

#ifndef ICOMPONENTS
#define ICOMPONENTS

//#include "../GAM300Editor/Include/imguiHelper/ImguiHelper.h"
#include <string>

#include "sceneManager/serialization.h"

// Macro to define a serialized field
//#define SerializeField(type, name)					\
//private:											\
//    type name##_;									\
//public:												\
//    property type name {							\
//        type get() { return name##_; }				\
//        void set(type value) { name##_ = value; }	\
//    }												\
//RTTR_REGISTRATION									\
//{													\
//	rttr::registration::class_<type>(#type)			\
//		.property(name, &type::TYPE)				\
//}


namespace TDS
{
	class IComponent : public Serializer
	{
	public:
		/*!*************************************************************************
		Destructor of the abstract IComponent class
		****************************************************************************/
		DLL_API virtual ~IComponent() = default;

		RTTR_ENABLE();
	};
}

#endif