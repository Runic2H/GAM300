/*!*************************************************************************
****
\file serialization.h
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 28-9-2023
\brief  This program declares the functions in the serializer class
****************************************************************************
***/

#ifndef SERIALIZATION
#define SERIALIZATION

#undef max
#undef min
#include <rttr/registration>
#include <rttr/registration_friend>
#include <rttr/type> 

#include "rapidJSON/rapidjson.h"
#include "rapidJSON/document.h"
#include "rapidJSON/stringbuffer.h"
#include "rapidJSON/prettywriter.h"
#include "dotnet/ImportExport.h"

namespace TDS
{
	class Serializer
	{
	public:
		/*!*************************************************************************
		Funtion for Deserializing to JSON file
		****************************************************************************/
		DLL_API bool DeserializeFromFile(const std::string& filePath);
		/*!*************************************************************************
		Funtion for Serializing to JSON file
		****************************************************************************/
		DLL_API bool SerializeToFile(const std::string& filePath);

		/*!*************************************************************************
		Json Serializer for calling Derived class Serialize function
		****************************************************************************/
		DLL_API virtual std::string Serialize() const;
		/*!*************************************************************************
		Json Deserializer for calling Derived class Deserialize function
		****************************************************************************/
		DLL_API virtual bool Deserialize(const std::string& stringbuffer);

		/*!*************************************************************************
		Virtual deserialize function for derived classes to overload
		****************************************************************************/
		DLL_API virtual bool Deserialize(const rapidjson::Value& obj, rapidjson::Document& doc) { return false; };
		/*!*************************************************************************
		Virtual serialize function for derived classes to overload
		****************************************************************************/
		DLL_API virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const { return false; };

		DLL_API virtual ~Serializer() = default;

	protected:
		/*!*************************************************************************
		Checks if Document can be Read
		****************************************************************************/
		bool InitDocument(const std::string& stringbuffer, rapidjson::Document& doc);
	};
}

#endif