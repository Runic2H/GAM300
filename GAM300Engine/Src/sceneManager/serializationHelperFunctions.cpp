/*!
@file    serializationHelperFunctions.cpp
@author  p.jiankai@digipen.edu(50%), ruoyan.go@digipen.edu(50%)
@date    10/9/2022

This file includes the serialisation helper function definitions.

*//*__________________________________________________________________________*/

#include <cstdio>
#include <string>
#include <vector>
#include <array>
#include <iostream>
#include <fstream>

#include "sceneManager\serialization.h"
#include "sceneManager\sceneManager.h"

namespace TDS
{
    using namespace rapidjson;
    using namespace rttr;

    bool write_basic_type(const type& t, const variant& var, PrettyWriter<StringBuffer>& writer)
    {
        if (t.is_arithmetic())
        {
            if (t == type::get<bool>())
                writer.Bool(var.to_bool());
            else if (t == type::get<char>())
                writer.Bool(var.to_bool());
            else if (t == type::get<int8_t>())
                writer.Int(var.to_int8());
            else if (t == type::get<int16_t>())
                writer.Int(var.to_int16());
            else if (t == type::get<int32_t>())
                writer.Int(var.to_int32());
            else if (t == type::get<int64_t>())
                writer.Int64(var.to_int64());
            else if (t == type::get<uint8_t>())
                writer.Uint(var.to_uint8());
            else if (t == type::get<uint16_t>())
                writer.Uint(var.to_uint16());
            else if (t == type::get<uint32_t>())
                writer.Uint(var.to_uint32());
            else if (t == type::get<uint64_t>())
                writer.Uint64(var.to_uint64());
            else if (t == type::get<float>())
                writer.Double(var.to_double());
            else if (t == type::get<double>())
                writer.Double(var.to_double());
            return true;
        }
        else if (t.is_enumeration())
        {
            bool ok = false;
            auto result = var.to_string(&ok);
            if (ok)
            {
                writer.String(var.to_string().c_str());
            }
            else
            {
                ok = false;
                auto value = var.to_uint64(&ok);
                if (ok)
                    writer.Uint64(value);
                else
                    writer.Null();
            }

            return true;
        }
        else if (t == type::get<std::string>())
        {
            writer.String(var.to_string().c_str());
            return true;
        }
        return false;
    }

    void write_array(const variant_sequential_view& view, PrettyWriter<StringBuffer>& writer)
    {
        writer.StartArray();
        for (const auto& item : view)
        {
            if (item.is_sequential_container())
            {
                write_array(item.create_sequential_view(), writer);
            }
            else
            {
                variant wrapped_var = item.extract_wrapped_value();
                type value_type = wrapped_var.get_type();
                if (value_type.is_arithmetic() || value_type == type::get<std::string>() || value_type.is_enumeration())
                {
                    write_basic_type(value_type, wrapped_var, writer);
                }
                else // object
                {
                    ToJsonRecur(wrapped_var, writer);
                }
            }
        }
        writer.EndArray();
    }

    void write_associative_container(const variant_associative_view& view, PrettyWriter<StringBuffer>& writer)
    {
        static const string_view key_name("key");
        static const string_view value_name("value");

        writer.StartArray();

        if (view.is_key_only_type()) {
            for (auto& item : view) {
                writeVariant(item.first, writer);
            }
        }
        else
        {
            for (auto& item : view)
            {
                writer.String(key_name.data(), static_cast<rapidjson::SizeType>(key_name.length()), false);
                writeVariant(item.first, writer);
                writer.String(value_name.data(), static_cast<rapidjson::SizeType>(value_name.length()), false);
                writeVariant(item.second, writer);

            }
        }

        writer.EndArray();
    }

    bool writeVariant(const variant& var, PrettyWriter<StringBuffer>& writer)
    {
        // Copy of the variant object
        variant theVar = var;

        // Type of the variant object
        type varType = theVar.get_type();

        // If the type is a wrapper, get the wrapped type and rewrite the variant to the wrapped value
        if (varType.is_wrapper())
        {
            varType = varType.get_wrapped_type();
            theVar = theVar.extract_wrapped_value();
        }

        // If the type is a basic type (int, float, double, etc)
        if (write_basic_type(varType, theVar, writer));

        // If the type is an array or vector
        else if (var.is_sequential_container())
        {
            write_array(var.create_sequential_view(), writer);
        }

        // If the type is a map
        else if (var.is_associative_container())
        {
            write_associative_container(var.create_associative_view(), writer);
        }

        // If it is none of the above
        else
        {
            // Getting the properties of the type
            auto child_prop = varType.get_properties();

            // If there are properties, call toJsonRecurrsive
            if (!child_prop.empty())
            {
                ToJsonRecur(var, writer);
            }
            else
            {
                assert("Unknown RTTR serilization edge case that we haven't discovered");
                return false;
            }
        }
        return true;

    }

    void ToJsonRecur(const instance& obj, PrettyWriter<StringBuffer>& writer)
    {
        writer.StartObject();

        // Making sure obj2 is a copy of obj that is:
        // 1. not a pointer, const, reference (using get.raw.type()),
        // 2. not a wrapper type eg. shared_pointer, unique_pointer, etc.(using is_wrapper())
        // 3. if obj is a wrapper, take the wrapped instance, eg from shared_ptr<int> to int (using get_wrapped_instance())
        instance obj2 = obj.get_type().get_raw_type().is_wrapper() ? obj.get_wrapped_instance() : obj;

        // Getting the type of instance (most derived, means getting child type), then getting the properties in the type
        auto prop_list = obj2.get_derived_type().get_properties();

        // For each property in obj2's type
        for (auto prop : prop_list)
        {
            // If the property has NO_SERIALIZE as the metadata (from registration, .metadata), skip the property
            if (prop.get_metadata("NO_SERIALIZE"))
                continue;

            // Retrieving value from property
            variant prop_value = prop.get_value(obj2);

            // Value is not retrieved
            if (!prop_value)
                continue;

            // Retrieving name of property
            const auto name = prop.get_name();

            // Serializing name first
            writer.String(name.data(), static_cast<rapidjson::SizeType>(name.length()), false);

            // Serializing value (using writeVariant()), returns a bool to confirm if written into file
            if (!writeVariant(prop_value, writer))
            {
                std::cerr << "Failed to serialize" << name << std::endl;
            }
        }

        writer.EndObject();
    }

    //----------------------------------------------------------------------------------------- READING STARTS HERE 

    variant extract_basic_type(Value& jvalue)
    {
        switch (jvalue.GetType())
        {
        case kStringType:
        {
            return std::string(jvalue.GetString());
            break;
        }
        case kNullType:
        {
            break;
        }
        case kFalseType:
        case kTrueType:
        {
            return jvalue.GetBool();
            break;
        }
        case kNumberType:
        {
            if (jvalue.IsInt())
                return jvalue.GetInt();
            else if (jvalue.IsDouble())
                return jvalue.GetDouble();
            else if (jvalue.IsUint())
                return jvalue.GetUint();
            else if (jvalue.IsInt64())
                return jvalue.GetInt64();
            else if (jvalue.IsUint64())
                return jvalue.GetUint64();
            break;
        }
        // not a basic type
        case kObjectType:
        case kArrayType: return variant();
        }
        return variant();
    }

    void write_array_recursively(variant_sequential_view& view, Value& json_array_value)
    {
        view.set_size(json_array_value.Size());

        const type array_value_type = view.get_rank_type(1);


        for (SizeType i = 0; i < json_array_value.Size(); ++i)
        {
            auto& json_index_value = json_array_value[i];
            if (json_index_value.IsArray()) {

                auto sub_array_view = view.get_value(i).create_sequential_view();
                write_array_recursively(sub_array_view, json_index_value);
            }

            else if (json_index_value.IsObject())
            {
                variant var_tmp = view.get_value(i);
                variant wrapped_var = var_tmp.extract_wrapped_value();
                //---------------------------------------------------------some ghetto shit happening
                // for reference
                /*
                Instance
                    Holds a reference to the given object.
                    Think of it as a std::any<T&>
                    Variant
                    Return value for properties and methods
                    Content is copied over to new instance of content
                    Think of it as a std::any
                    */
                instance instancedWrapped = wrapped_var;
                fromJsonRecur(instancedWrapped, json_index_value);
                view.set_value(i, wrapped_var);
            }

            else
            {
                variant extracted_value = extract_basic_type(json_index_value);
                if (extracted_value.convert(array_value_type))
                    view.set_value(i, extracted_value);
            }
        }

    }

    variant extract_value(Value::MemberIterator& itr, const type& t)
    {
        auto& json_value = itr->value;
        variant extracted_value = extract_basic_type(json_value);
        const bool can_convert = extracted_value.convert(t);
        if (!can_convert) {
            //not a basic type 
            if (json_value.IsObject()) {
                constructor ctor = t.get_constructor();
                for (auto& item : t.get_constructors()) {
                    if (item.get_instantiated_type() == t) {
                        ctor = item;
                    }
                }
                extracted_value = ctor.invoke();
                instance instancedVal = extracted_value;
                fromJsonRecur(instancedVal, json_value);
            }
        }
        return extracted_value;
    }

    void write_associative_view_recursively(variant_associative_view& view, Value& json_array_value)
    {
        int counter = 0;
        for (SizeType i = 0; i < json_array_value.Size(); ++i)
        {
            auto& json_index_value = json_array_value[i];
            if (json_index_value.IsObject())
            {
                Value::MemberIterator key_itr = json_array_value.FindMember("key");
                Value::MemberIterator value_itr = json_array_value.FindMember("value");

                //just a check
                if (key_itr != json_array_value.MemberEnd() && value_itr != json_array_value.MemberEnd())
                {
                    key_itr[0] = key_itr[counter * 2];
                    value_itr[0] = value_itr[counter * 2];
                    auto key_var = extract_value(key_itr, view.get_key_type());
                    auto value_var = extract_value(value_itr, view.get_value_type());

                    //just another check
                    if (key_var && value_var)
                    {
                        view.insert(key_var, value_var);
                        //view.insert(key_var, value_var);
                    }
                    ++counter;
                }
            }
            else
            {   //only key 
                variant extracted_value = extract_basic_type(json_index_value);
                if (extracted_value && extracted_value.convert(view.get_key_type()))
                {
                    view.insert(extracted_value);
                }
            }
        }
    }

    void fromJsonRecur(instance& obj, Value& jsonObj)
    {
        instance obj2 = obj.get_type().get_raw_type().is_wrapper() ? obj.get_wrapped_instance() : obj;
        const auto prop_list = obj2.get_derived_type().get_properties();

        for (auto prop : prop_list)
        {
            Value::MemberIterator theItr = jsonObj.FindMember(prop.get_name().data());

            if (theItr == jsonObj.MemberEnd())
            {
                continue;
            }

            const type valT = prop.get_type();
            auto& jsonVal = theItr->value;

            switch (jsonVal.GetType())
            {
            case kArrayType:
            {
                variant var = prop.get_value(obj2);
                if (valT.is_associative_container())
                {
                    auto theView = var.create_associative_view();
                    write_associative_view_recursively(theView, jsonVal);
                }
                else if (valT.is_sequential_container())
                {
                    auto theView = var.create_sequential_view();
                    write_array_recursively(theView, jsonVal);
                }

                prop.set_value(obj2, var);
                break;
            }
            case kObjectType:
            {
                variant var = prop.get_value(obj2);
                instance instancedVar = var;
                fromJsonRecur(instancedVar, jsonVal);
                prop.set_value(obj2, var);
                break;
            }
            default:
            {
                variant extracted_value = extract_basic_type(jsonVal);
                if (extracted_value.convert(valT)) // CONVERTING WORKS ONLY WITH const type
                    prop.set_value(obj, extracted_value);
            }
            }
        }
    }
}